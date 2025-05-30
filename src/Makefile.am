## This file is part of dvisvgm
## Copyright (C) 2005-2025 Martin Gieseking <martin.gieseking@uos.de>
##
## Process this file with automake.

bin_PROGRAMS     = dvisvgm
noinst_LTLIBRARIES = libdvisvgm.la
SUBDIRS = fonts optimizer ttf

dvisvgm_SOURCES = \
	CommandLine.hpp \
	dvisvgm.cpp

include ../libs/defs.am

dvisvgm_LDADD = \
	$(noinst_LTLIBRARIES) \
	../libs/clipper/libclipper.a \
	../libs/md5/libmd5.a \
	$(POTRACE_LIBS) \
	$(XXHASH_LIBS)

if ENABLE_WOFF
SUBDIRS += ttf

dvisvgm_LDADD += \
	$(WOFF2_LIBS) \
	$(BROTLI_LIBS)
endif ENABLE_WOFF

if TEXLIVE_BUILD
dvisvgm_LDADD += \
	$(KPATHSEA_LIBS) \
	$(FREETYPE2_LIBS) \
	$(ZLIB_LIBS) \
	$(LIBGS_LIBS)
else
dvisvgm_LDADD += \
	$(FREETYPE_LIBS) \
	$(ZLIB_LIBS)
endif !TEXLIVE_BUILD

dvisvgm_DEPENDENCIES = $(noinst_LTLIBRARIES)

if TEXLIVE_BUILD
dvisvgm_DEPENDENCIES += $(KPATHSEA_DEPEND) $(ZLIB_DEPEND) $(FREETYPE2_DEPEND)
dvisvgm_DEPENDENCIES += $(POTRACE_DEPEND)
endif

libdvisvgm_la_SOURCES = \
	AGLTable.hpp \
	algorithm.hpp \
	BasicDVIReader.hpp           BasicDVIReader.cpp \
	Bezier.hpp                   Bezier.cpp \
	BgColorSpecialHandler.hpp    BgColorSpecialHandler.cpp \
	Bitmap.hpp                   Bitmap.cpp \
	BoundingBox.hpp              BoundingBox.cpp \
	Calculator.hpp               Calculator.cpp \
	Character.hpp \
	CharMapID.hpp                CharMapID.cpp \
	CLCommandLine.hpp            CLCommandLine.cpp \
	CMap.hpp                     CMap.cpp \
	CMapManager.hpp              CMapManager.cpp \
	CMapReader.hpp               CMapReader.cpp \
	CLOption.hpp \
	Color.hpp                    Color.cpp \
	ColorSpecialHandler.hpp      ColorSpecialHandler.cpp \
	CommandLine.hpp \
	Directory.hpp                Directory.cpp \
	DVIActions.hpp \
	DLLoader.hpp                 DLLoader.cpp \
	DVIReader.hpp                DVIReader.cpp \
	DvisvgmSpecialHandler.hpp    DvisvgmSpecialHandler.cpp \
	DVIToSVG.hpp                 DVIToSVG.cpp \
	DVIToSVGActions.hpp          DVIToSVGActions.cpp \
	EllipticalArc.hpp            EllipticalArc.cpp \
	EmSpecialHandler.hpp         EmSpecialHandler.cpp \
	EncFile.hpp                  EncFile.cpp \
	EPSFile.hpp                  EPSFile.cpp \
	EPSToSVG.hpp \
	FileFinder.hpp               FileFinder.cpp \
	FilePath.hpp                 FilePath.cpp \
	FileSystem.hpp               FileSystem.cpp \
	FixWord.hpp \
	Font.hpp                     Font.cpp \
	FontCache.hpp                FontCache.cpp \
	FontEncoding.hpp             FontEncoding.cpp \
	FontEngine.hpp               FontEngine.cpp \
	FontManager.hpp              FontManager.cpp \
	FontMap.hpp                  FontMap.cpp \
	FontMetrics.hpp              FontMetrics.cpp \
	FontStyle.hpp \
	FontWriter.hpp               FontWriter.cpp \
	GFGlyphTracer.hpp            GFGlyphTracer.cpp \
	GFReader.hpp                 GFReader.cpp \
	GFTracer.hpp                 GFTracer.cpp \
	Ghostscript.hpp              Ghostscript.cpp \
	Glyph.hpp \
	GlyphTracerMessages.hpp \
	GraphicsPath.hpp \
	GraphicsPathParser.hpp \
	HashFunction.hpp             HashFunction.cpp \
	HtmlSpecialHandler.hpp       HtmlSpecialHandler.cpp \
	HyperlinkManager.hpp         HyperlinkManager.cpp \
	ImageToSVG.hpp               ImageToSVG.cpp \
	InputBuffer.hpp              InputBuffer.cpp \
	InputReader.hpp              InputReader.cpp \
	JFM.hpp                      JFM.cpp \
	Length.hpp                   Length.cpp \
	macros.hpp \
	MapLine.hpp                  MapLine.cpp \
	Matrix.hpp                   Matrix.cpp \
	MD5HashFunction.hpp \
	Message.hpp                  Message.cpp \
	MessageException.hpp \
	MetafontWrapper.hpp          MetafontWrapper.cpp \
	NoPsSpecialHandler.hpp       NoPsSpecialHandler.cpp \
	NumericRanges.hpp \
	OFM.hpp                      OFM.cpp \
	Opacity.hpp                  Opacity.cpp \
	PageRanges.hpp               PageRanges.cpp \
	PageSize.hpp                 PageSize.cpp \
	Pair.hpp \
	PapersizeSpecialHandler.hpp  PapersizeSpecialHandler.cpp \
	PathClipper.hpp              PathClipper.cpp \
	PDFHandler.hpp               PDFHandler.cpp \
	PDFParser.hpp                PDFParser.cpp \
	PdfSpecialHandler.hpp        PdfSpecialHandler.cpp \
	PDFToSVG.hpp                 PDFToSVG.cpp \
	PreScanDVIReader.hpp         PreScanDVIReader.cpp \
	Process.hpp                  Process.cpp \
	psdefs.cpp \
	PSInterpreter.hpp            PSInterpreter.cpp \
	PSPattern.hpp                PSPattern.cpp \
	PSPreviewHandler.hpp         PSPreviewHandler.cpp \
	PsSpecialHandler.hpp         PsSpecialHandler.cpp \
	PsSpecialHandlerProxy.hpp    PsSpecialHandlerProxy.cpp \
	RangeMap.hpp                 RangeMap.cpp \
	ShadingPatch.hpp             ShadingPatch.cpp \
	SignalHandler.hpp            SignalHandler.cpp \
	SourceInput.hpp              SourceInput.cpp \
	SpecialActions.hpp           SpecialActions.cpp \
	SpecialHandler.hpp \
	SpecialManager.hpp           SpecialManager.cpp \
	StreamReader.hpp             StreamReader.cpp \
	StreamWriter.hpp             StreamWriter.cpp \
	Subfont.hpp                  Subfont.cpp \
	SVGCharHandler.hpp           SVGCharHandler.cpp \
	SVGCharHandlerFactory.hpp    SVGCharHandlerFactory.cpp \
	SVGCharPathHandler.hpp       SVGCharPathHandler.cpp \
	SVGCharTspanTextHandler.hpp  SVGCharTspanTextHandler.cpp \
	SVGElement.hpp               SVGElement.cpp \
	SVGOutput.hpp                SVGOutput.cpp \
	SVGSingleCharTextHandler.hpp SVGSingleCharTextHandler.cpp \
	SVGTree.hpp                  SVGTree.cpp \
	System.hpp                   System.cpp \
	TensorProductPatch.hpp       TensorProductPatch.cpp \
	Terminal.hpp                 Terminal.cpp \
	TFM.hpp                      TFM.cpp \
	ToUnicodeMap.hpp             ToUnicodeMap.cpp \
	TpicSpecialHandler.hpp       TpicSpecialHandler.cpp \
	TriangularPatch.hpp          TriangularPatch.cpp \
	Unicode.hpp                  Unicode.cpp \
	utility.hpp                  utility.cpp \
	VectorIterator.hpp \
	VFActions.hpp \
	VFReader.hpp                 VFReader.cpp \
	windows.hpp \
	XMLDocument.hpp              XMLDocument.cpp \
	XMLNode.hpp                  XMLNode.cpp \
	XMLParser.hpp                XMLParser.cpp \
	XMLString.hpp                XMLString.cpp \
	XXHashFunction.hpp \
	ZLibOutputStream.hpp

libdvisvgm_la_LIBADD = fonts/libbase14fonts.la optimizer/liboptimizer.la

if ENABLE_WOFF
libdvisvgm_la_LIBADD += ttf/libttf.la
endif

EXTRA_DIST = options.xml options.dtd iapi.h ierrors.h MiKTeXCom.hpp MiKTeXCom.cpp

AM_CFLAGS = $(WARNING_CFLAGS) \
	$(ZLIB_CFLAGS) \
	$(CODE_COVERAGE_CFLAGS)

AM_CXXFLAGS = $(WARNING_CXXFLAGS) \
	-I$(dvisvgm_srcdir)/libs/boost \
	-I$(dvisvgm_srcdir)/libs/clipper \
	-I$(dvisvgm_srcdir)/libs/variant/include

AM_CXXFLAGS += \
	$(POTRACE_CFLAGS) \
	$(XXHASH_CFLAGS)

if TEXLIVE_BUILD
AM_CXXFLAGS += \
	$(KPATHSEA_INCLUDES) \
	$(POTRACE_INCLUDES) \
	$(FREETYPE2_INCLUDES) \
	$(ZLIB_INCLUDES) \
	$(CODE_COVERAGE_CFLAGS)
if WIN32
AM_CXXFLAGS += -DTEXLIVEWIN32
endif WIN32
else
AM_CXXFLAGS += \
	$(KPSE_CFLAGS) \
	$(FREETYPE_CFLAGS) \
	$(ZLIB_CFLAGS) \
	$(CODE_COVERAGE_CFLAGS)
endif !TEXLIVE_BUILD

AM_LDFLAGS = \
	$(KPSE_LIBS) \
	$(CODE_COVERAGE_LDFLAGS)

if ENABLE_WOFF
AM_CXXFLAGS += $(TTFAUTOHINT_CFLAGS)

AM_CXXFLAGS +=  \
	$(BROTLI_CFLAGS) \
	$(WOFF2_CFLAGS)

# TL: do not try to rebuild these source files.
if !TEXLIVE_BUILD
AM_LDFLAGS += $(TTFAUTOHINT_LIBS)
endif !TEXLIVE_BUILD
endif ENABLE_WOFF

AM_CXXFLAGS += -I$(dvisvgm_srcdir)/libs/md5

if !TEXLIVE_BUILD
# the command-line parser class is generated from options.xml by opt2cpp
$(srcdir)/CommandLine.hpp: options.xml
	rm -f $@
	python $(srcdir)/opt2cpp.py $< >$@

# Create a C string definition containing the PostScript routines psdefs.ps needed by class PSInterpreter
$(srcdir)/psdefs.cpp: psdefs.ps
	if test -f $<; then \
		ps2c PSInterpreter::PSDEFS $< >$@; \
	fi

psdefs.ps: ;
endif !TEXLIVE_BUILD

CLEANFILES = *.gcda *.gcno

if TEXLIVE_BUILD
# Rebuild libkpathsea:
@KPATHSEA_RULE@
# Rebuild libfreetype:
@FREETYPE2_RULE@
# Rebuild libz:
@ZLIB_RULE@
# Rebuild potrace:
@POTRACE_RULE@
endif TEXLIVE_BUILD
