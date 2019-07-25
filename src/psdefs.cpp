/*************************************************************************
** psdefs.cpp                                                           **
**                                                                      **
** This file is part of dvisvgm -- a fast DVI to SVG converter          **
** Copyright (C) 2005-2019 Martin Gieseking <martin.gieseking@uos.de>   **
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

#include "PSInterpreter.hpp"

const char *PSInterpreter::PSDEFS =
"<</Install{matrix setmatrix}/HWResolution[72 72]/PageSize[10000 10000]/Imaging"
"BBox null>>setpagedevice/@dodraw true store/@patcnt 0 store/@SD systemdict def"
"/@UD userdict def true setglobal @SD/:save @SD/save get put @SD/:restore @SD/r"
"estore get put @SD/:gsave @SD/gsave get put @SD/:grestore @SD/grestore get put"
" @SD/:grestoreall @SD/grestoreall get put @SD/:newpath @SD/newpath get put @SD"
"/:stroke @SD/stroke get put @SD/:fill @SD/fill get put @SD/:eofill @SD/eofill "
"get put @SD/:clip @SD/clip get put @SD/:eoclip @SD/eoclip get put @SD/:charpat"
"h @SD/charpath get put @SD/:show @SD/show get put @SD/:stringwidth @SD/stringw"
"idth get put @SD/.setopacityalpha known not{@SD/.setopacityalpha{pop}put}if @S"
"D/.setshapealpha known not{@SD/.setshapealpha{pop}put}if @SD/.setblendmode kno"
"wn not{@SD/.setblendmode{pop}put}if @SD/prseq{-1 1{-1 roll =only( )print}for(\\"
"n)print}put @SD/prcmd{( )exch(\\ndvi.)3{print}repeat prseq}put @SD/cvxall{{cvx"
"}forall}put @SD/defpr{[exch[/copy @SD]cvxall 5 -1 roll dup 6 1 roll[/get/exec]"
"cvxall 6 -1 roll dup 7 1 roll 4 -1 roll dup 5 1 roll dup length string cvs/prc"
"md cvx]cvx def}put @SD/querypos{{currentpoint}stopped{$error/newerror false pu"
"t}{2(querypos)prcmd}ifelse}put @SD/applyscalevals{1 0 dtransform exch dup mul "
"exch dup mul add sqrt 0 1 dtransform exch dup mul exch dup mul add sqrt 1 0 dt"
"ransform dup mul exch dup dup mul 3 -1 roll add dup 0 eq{pop}{sqrt div}ifelse "
"3(applyscalevals)prcmd}put @SD/prpath{{2(moveto)prcmd}{2(lineto)prcmd}{6(curve"
"to)prcmd}{0(closepath)prcmd}pathforall}put @SD/charpath{/@dodraw false store :"
"charpath/@dodraw true store}put @SD/stringwidth{/@dodraw false store :stringwi"
"dth/@dodraw true store}put @SD/show{@dodraw{dup :gsave currentpoint 2{50 mul e"
"xch}repeat :newpath moveto 50 50/scale sysexec true charpath fill :grestore/@d"
"odraw false store :show/@dodraw true store}{:show}ifelse}put @SD/varxyshow{exc"
"h dup type/arraytype eq{<</arr 3 -1 roll/prc 5 -1 roll/chr 1 string/idx 0>>beg"
"in{chr 0 3 -1 roll put :gsave chr show :grestore currentpoint prc moveto/idx i"
"dx 1 add store}forall end}{pop show}ifelse}put @SD/xyshow{{exch arr idx 2 mul "
"get add exch arr idx 2 mul 1 add get add}varxyshow}put @SD/xshow{{exch arr idx"
" get add exch}varxyshow}put @SD/yshow{{arr idx get add}varxyshow}put @SD/awidt"
"hshow{{1 string dup 0 5 index put :gsave show :grestore pop 0 rmoveto 3 index "
"eq{4 index 4 index rmoveto}if 1 index 1 index rmoveto}exch cshow 5{pop}repeat}"
"put @SD/widthshow{0 0 3 -1 roll pstack awidthshow}put @SD/ashow{0 0 0 6 3 roll"
" awidthshow}put @SD/newpath{:newpath 1 1(newpath)prcmd}put @SD/stroke{@dodraw{"
"prcolor 0 1(newpath)prcmd prpath 0(stroke)prcmd :newpath}{:stroke}ifelse}put @"
"SD/fill{@dodraw{prcolor 0 1(newpath)prcmd prpath 0(fill)prcmd :newpath}{:fill}"
"ifelse}put @SD/eofill{@dodraw{prcolor 0 1(newpath)prcmd prpath 0(eofill)prcmd "
":newpath}{:eofill}ifelse}put @SD/clip{:clip 0 1(newpath)prcmd prpath 0(clip)pr"
"cmd}put @SD/eoclip{:eoclip 0 1(newpath)prcmd prpath 0(eoclip)prcmd}put @SD/shf"
"ill{begin currentdict/ShadingType known currentdict/ColorSpace known and curre"
"ntdict/DataSource known and currentdict/Function known not and ShadingType 4 g"
"e and DataSource type/arraytype eq and{<</DeviceGray 1/DeviceRGB 3/DeviceCMYK "
"4/bgknown currentdict/Background known/bbknown currentdict/BBox known>>begin c"
"urrentdict ColorSpace known{ShadingType ColorSpace load bgknown{1 Background a"
"load pop}{0}ifelse bbknown{1 BBox aload pop}{0}ifelse ShadingType 5 eq{Vertice"
"sPerRow}if DataSource aload length 4 add bgknown{ColorSpace load add}if bbknow"
"n{4 add}if ShadingType 5 eq{1 add}if(shfill)prcmd}if end}if end}put/@rect{4 -2"
" roll moveto exch dup 0 rlineto exch 0 exch rlineto neg 0 rlineto closepath}bi"
"nd def/@rectcc{4 -2 roll moveto 2 copy 0 lt exch 0 lt xor{dup 0 exch rlineto e"
"xch 0 rlineto neg 0 exch rlineto}{exch dup 0 rlineto exch 0 exch rlineto neg 0"
" rlineto}ifelse closepath}bind def @SD/rectclip{:newpath dup type/arraytype eq"
"{aload length 4 idiv{@rectcc}repeat}{@rectcc}ifelse clip :newpath}put @SD/rect"
"fill{gsave :newpath dup type/arraytype eq{aload length 4 idiv{@rectcc}repeat}{"
"@rectcc}ifelse fill grestore}put @SD/rectstroke{gsave :newpath dup type/arrayt"
"ype eq{aload length 4 idiv{@rect}repeat}{@rect}ifelse stroke grestore}put fals"
"e setglobal @SD readonly pop/initclip 0 defpr/clippath 0 defpr/sysexec{@SD exc"
"h get exec}def/adddot{dup length 1 add string dup 0 46 put dup 3 -1 roll 1 exc"
"h putinterval}def/setlinewidth{dup/setlinewidth sysexec 1(setlinewidth)prcmd}d"
"ef/setlinecap 1 defpr/setlinejoin 1 defpr/setmiterlimit 1 defpr/setdash{mark 3"
" 1 roll 2 copy/setdash sysexec exch aload length 1 add -1 roll counttomark(set"
"dash)prcmd pop}def/@setpagedevice{pop<<>>/setpagedevice sysexec matrix setmatr"
"ix newpath 0(setpagedevice)prcmd}def/prcolor{currentrgbcolor 3(setrgbcolor)prc"
"md}def/printgstate{@dodraw{matrix currentmatrix aload pop 6(setmatrix)prcmd ap"
"plyscalevals currentlinewidth 1(setlinewidth)prcmd currentlinecap 1(setlinecap"
")prcmd currentlinejoin 1(setlinejoin)prcmd currentmiterlimit 1(setmiterlimit)p"
"rcmd currentrgbcolor 3(setrgbcolor)prcmd currentdash mark 3 1 roll exch aload "
"length 1 add -1 roll counttomark(setdash)prcmd pop}if}def/setgstate{/setgstate"
" sysexec printgstate}def/save{@UD begin/@saveID vmstatus pop pop def end :save"
" @saveID 1(save)prcmd}def/restore{:restore printgstate @UD/@saveID known{@UD b"
"egin @saveID end}{0}ifelse 1(restore)prcmd}def/gsave 0 defpr/grestore{:grestor"
"e printgstate 0(grestore)prcmd}def/grestoreall{:grestoreall setstate 0(grestor"
"eall)prcmd}def/rotate{dup type/arraytype ne @dodraw and{dup 1(rotate)prcmd}if/"
"rotate sysexec applyscalevals}def/scale{dup type/arraytype ne @dodraw and{2 co"
"py 2(scale)prcmd}if/scale sysexec applyscalevals}def/translate{dup type/arrayt"
"ype ne @dodraw and{2 copy 2(translate)prcmd}if/translate sysexec}def/setmatrix"
"{dup/setmatrix sysexec @dodraw{aload pop 6(setmatrix)prcmd applyscalevals}{pop"
"}ifelse}def/initmatrix{matrix setmatrix}def/concat{matrix currentmatrix matrix"
" concatmatrix setmatrix}def/makepattern{gsave<</mx 3 -1 roll>>begin dup/XUID[1"
"000000 @patcnt]put mx/makepattern sysexec dup dup begin PatternType @patcnt BB"
"ox aload pop XStep YStep PaintType mx aload pop 15(makepattern)prcmd :newpath "
"matrix setmatrix PaintProc 0 1(makepattern)prcmd end/@patcnt @patcnt 1 add sto"
"re end grestore}def/setpattern{begin PatternType 1 eq{PaintType 1 eq{XUID aloa"
"d pop exch pop 1}{:gsave[currentcolorspace aload length -1 roll pop]setcolorsp"
"ace/setcolor sysexec XUID aload pop exch pop currentrgbcolor :grestore 4}ifels"
"e(setpattern)prcmd}{/setpattern sysexec}ifelse end}def/setcolor{dup type/dictt"
"ype eq{setpattern}{/setcolor sysexec/currentrgbcolor sysexec setrgbcolor}ifels"
"e}def/setgray 1 defpr/setcmykcolor 4 defpr/sethsbcolor 3 defpr/setrgbcolor 3 d"
"efpr/.setopacityalpha{dup/.setopacityalpha sysexec 1(setopacityalpha)prcmd}def"
"/.setshapealpha{dup/.setshapealpha sysexec 1(setshapealpha)prcmd}def/.setblend"
"mode{dup/.setblendmode sysexec<</Normal 0/Compatible 0/Multiply 1/Screen 2/Ove"
"rlay 3/SoftLight 4/HardLight 5/ColorDodge 6/ColorBurn 7/Darken 8/Lighten 9/Dif"
"ference 10/Exclusion 11/Hue 12/Saturation 13/Color 14/Luminosity 15/Compatible"
"Overprint 16>>exch get 1(setblendmode)prcmd}def/@pdfpagecount{(r)file runpdfbe"
"gin pdfpagecount runpdfend}def/@pdfpagebox{(r)file runpdfbegin dup dup 1 lt ex"
"ch pdfpagecount gt or{pop}{pdfgetpage/MediaBox pget pop aload pop}ifelse runpd"
"fend}def DELAYBIND{.bindnow}if ";
