/*************************************************************************
** MetafontWrapper.cpp                                                  **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2025 Martin Gieseking <martin.gieseking@uos.de>   **
**                                                                      **
** This program is free software; you can redistribute it and/or        **
** modify it under the terms of the GNU General Public License as       **
** published by the Free Software Foundation; either version 3 of       **
** the License, or (at your option) any later version.                  **
**                                                                      **
** This program is distributed in the hope that it will be useful, but  **
** WITHOUT ANY WARRANTY; without even the implied warranty of           **
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the         **
** GNU General Public License for more details.                         **
**                                                                      **
** You should have received a copy of the GNU General Public License    **
** along with this program; if not, see <http://www.gnu.org/licenses/>. **
*************************************************************************/

#include <cctype>
#include <fstream>
#include <sstream>
#include "FileSystem.hpp"
#include "FileFinder.hpp"
#include "Message.hpp"
#include "MetafontWrapper.hpp"
#include "Process.hpp"
#include "XMLString.hpp"

using namespace std;


MetafontWrapper::MetafontWrapper (string fname, string dir)
	: _fontname(std::move(fname)), _dir(std::move(dir))
{
	// ensure that folder paths ends with slash
	if (_dir.empty())
		_dir = "./";
	else if (_dir != "/" && _dir.back() != '/')
		_dir += '/';
}


/** Calls Metafont and evaluates the logfile. If a gf file was successfully
 *  generated the dpi value is stripped from the filename
 *  (e.g. cmr10.600gf => cmr10.gf). This makes life easier...
 *  @param[in] mode Metafont mode, e.g. "ljfour"
 *  @param[in] mag magnification factor
 *  @return true on success */
bool MetafontWrapper::call (const string &mode, double mag) const {
	if (!FileFinder::instance().lookup(_fontname+".mf"))
		return false;     // mf file not available => no need to call the "slow" Metafont
	FileSystem::remove(_fontname+".gf");

	string mfName = "mf";  // file name of Metafont executable
#ifndef MIKTEX
	if (const char *mfnowinPath = FileFinder::instance().lookupExecutable("mf-nowin", true))
		mfName = mfnowinPath;
	else
#endif
		if (const char *mfPath = FileFinder::instance().lookupExecutable(mfName, true))
			mfName = mfPath;
#ifdef _WIN32
		else {
			Message::estream(true) << "can't run Metafont (mf.exe and mf-nowin.exe not found)\n";
			return false;
		}
#endif
	ostringstream oss;
	oss << "\"\\mode=" << mode  << ";"  // set MF mode, e.g. 'proof', 'ljfour' or 'localfont'
		"mode_setup;"                    // initialize MF variables
		"mag:=" << mag << ";"            // set magnification factor
		"show pixels_per_inch*mag;"      // print character resolution to stdout
		"batchmode;"                     // don't halt on errors and don't print informational messages
		"input " << _fontname << "\"";   // load font description
	Message::mstream(false, Message::MC_STATE) << "\nrunning Metafont for " << _fontname << '\n';
	Process mf_process(std::move(mfName), oss.str());
	string mf_messages;
	mf_process.run(_dir, &mf_messages);

	int resolution = getResolution(mf_messages);

	// compose expected name of GF file (see Metafont Book, p. 324)
	string gfname = _dir + _fontname + ".";
	if (resolution > 0)
		gfname += XMLString(resolution);
	gfname += "gf";
	FileSystem::rename(gfname, _dir+_fontname+".gf");  // remove resolution value from filename
	return FileSystem::exists(_dir+_fontname+".gf");
}


/** Returns the resolution applied to a GF file generated by Metafont. Since the resolution
 *  is part of the filename suffix, we need this value in order to address the file.
 *  @param[in] mfMessage output written to stdout by Metafont
 *  @return the resolution (>0 on success, 0 otherwise) */
int MetafontWrapper::getResolution (const string &mfMessage) const {
	int res = 0;
	char buf[256];
	if (!mfMessage.empty()) {
		// try get resolution value written to stdout by above MF command
		istringstream iss(mfMessage);
		while (iss) {
			iss.getline(buf, sizeof(buf));
			string line = buf;
			if (line.substr(0, 3) == ">> ") {
				res = stoi(line.substr(3));
				break;
			}
		}
	}
	// couldn't read resolution from stdout, try to get it from log file
	if (res == 0) {
		ifstream ifs(_dir+_fontname+".log");
		while (ifs) {
			ifs.getline(buf, sizeof(buf));
			string line = buf;
			if (line.substr(0, 18) == "Output written on ") {
				line = line.substr(18);
				auto pos = line.find(' ');
				if (pos != string::npos)
					line.resize(pos);
				pos = line.rfind('.');
				if (pos != string::npos && line.substr(line.length()-2) == "gf") {
					line.pop_back();
					line.pop_back();
					try {
						res = stoi(line.substr(pos+1));
					}
					catch (...) {
					}
				}
			}
		}
	}
	return res;
}


/** Calls Metafont if output files (tfm and gf) don't already exist.
 *  @param[in] mode Metafont mode to be used (e.g. 'ljfour')
 *  @param[in] mag magnification factor
 *  @return true on success */
bool MetafontWrapper::make (const string &mode, double mag) const {
	ifstream tfm(_dir+_fontname+".tfm");
	ifstream gf(_dir+_fontname+".gf");
	if (gf && tfm) // @@ distinguish between gf and tfm
		return true;
	return call(mode, mag);
}


bool MetafontWrapper::success () const {
	ifstream tfm(_dir+_fontname+".tfm");
	ifstream gf(_dir+_fontname+".gf");
	return tfm && gf;
}
