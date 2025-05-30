/*************************************************************************
** CMap.cpp                                                             **
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

#include <sstream>
#include "algorithm.hpp"
#include "CMap.hpp"
#include "CMapManager.hpp"
#include "FileFinder.hpp"
#include "Unicode.hpp"

using namespace std;


const char* CMap::path () const {
	return FileFinder::instance().lookup(name(), "cmap", false);
}


const FontEncoding* CMap::findCompatibleBaseFontMap (const PhysicalFont *font, CharMapID &charmapID) const {
	return CMapManager::instance().findCompatibleBaseFontMap(font, this, charmapID);
}

//////////////////////////////////////////////////////////////////////

void SegmentedCMap::addCIDRange (uint32_t first, uint32_t last, uint32_t cid) {
	if (uint32_t cp = Unicode::fromSurrogate(first))  // is 'first' a surrogate?
		first = cp;
	if (uint32_t cp = Unicode::fromSurrogate(last))   // is 'last' a surrogate?
		last = cp;
	_cidranges.addRange(first, last, cid);
}


void SegmentedCMap::addBFRange (uint32_t first, uint32_t last, uint32_t chrcode) {
	if (uint32_t cp = Unicode::fromSurrogate(chrcode))  // is 'chrcode' a surrogate?
		chrcode = cp;
	_bfranges.addRange(first, last, chrcode);
}


/** Returns the RO (Registry-Ordering) string of the CMap. */
string SegmentedCMap::getROString() const {
	if (_registry.empty() || _ordering.empty())
		return "";
	return _registry + "-" + _ordering;
}


bool SegmentedCMap::mapsToUnicode () const {
	vector<string> encstrings = {"UTF8", "UTF16", "UCS2", "UCS4", "UCS32"};
	return algo::any_of(encstrings, [&](const string& s) {
		auto pos = _filename.find(s);
		return (pos != string::npos && (pos == 0 || _filename[pos-1] == '-'));
	});
}


/** Returns the CID for a given character code. */
uint32_t SegmentedCMap::cid (uint32_t c) const {
	if (_cidranges.valueExists(c))
		return _cidranges.valueAt(c);
	if (_basemap)
		return _basemap->cid(c);
	return 0;
}


/** Returns the character code of a base font for a given CID. */
uint32_t SegmentedCMap::bfcode (uint32_t cid) const {
	if (_bfranges.valueExists(cid))
		return _bfranges.valueAt(cid);
	if (_basemap)
		return _basemap->bfcode(cid);
	return 0;
}


void SegmentedCMap::write (ostream &os) const {
	_cidranges.write(os);
}
