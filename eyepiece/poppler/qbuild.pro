# Build file for the poppler library adopted for qt extended
# (c) Alex Samorukov, samm@os2.kiev.ua

# It builds poppler 0.13.3 (0.14 Beta 2) with enabled: splash renderer, libjpeg and qt4 binding
# To build library you will need to have armel 
# packages (library + dev) for freetype, jpeg, fontconfig and expat
# i just downloaded them to my build host, unpacked (ar -xv <file>.deb, tar -xvzf data.tar.gz)
# and placed content into /opt/toolchains/debian-armel/

LIBS += -L$$MKSPEC.LIBDIR -lfreetype -ljpeg -lfontconfig -lexpat

# Also please note that port require qt extendedc configured with -rtti switch. It is very easy
# to avoid (only 2 dynamic casts per code, in rare used functions), but will require minor patch.
# with -rtti 0.13.3 builds without modifications

# set this variable to the absolute path with poppler source (this dir)
# for some reason qbuild fail to work correctly with relative paths. 
INC = $$shellQuote($$path(,project))

TEMPLATE=lib

# remove staticlib if you want to buil shared library
CONFIG+=qtopia  staticlib singleexec

TARGET=poppler-qt4
MODULE_NAME=poppler

# thats all. Everything else migrated from gnu makefiles

HEADERS += goo/GooHash.h goo/GooList.h goo/GooTimer.h \
	goo/GooMutex.h goo/GooString.h goo/GooVector.h goo/gtypes.h goo/gmem.h goo/gfile.h \
	goo/FixedPoint.h goo/PNGWriter.h goo/JpegWriter.h goo/ImgWriter.h goo/gstrtod.h
	
SOURCES += goo/gfile.cc				\
	goo/gmempp.cc				\
	goo/GooHash.cc				\
	goo/GooList.cc				\
	goo/GooTimer.cc				\
	goo/GooString.cc				\
	goo/gmem.cc					\
	goo/FixedPoint.cc				\
	goo/PNGWriter.cc				\
	goo/JpegWriter.cc				\
	goo/ImgWriter.cc				\
	goo/gstrtod.cc 
	
# .. and fofi	

HEADERS += fofi/FoFiBase.h		\
	fofi/FoFiEncodings.h		\
	fofi/FoFiTrueType.h		\
	fofi/FoFiType1.h		\
	fofi/FoFiType1C.h
	
SOURCES += fofi/FoFiBase.cc		\
	fofi/FoFiEncodings.cc	\
	fofi/FoFiTrueType.cc		\
	fofi/FoFiType1.cc		\
	fofi/FoFiType1C.cc		

# splash
HEADERS += splash/Splash.h				\
	splash/SplashBitmap.h				\
	splash/SplashClip.h				\
	splash/SplashErrorCodes.h			\
	splash/SplashFTFont.h				\
	splash/SplashFTFontEngine.h			\
	splash/SplashFTFontFile.h			\
	splash/SplashFont.h				\
	splash/SplashFontEngine.h			\
	splash/SplashFontFile.h			\
	splash/SplashFontFileID.h			\
	splash/SplashGlyphBitmap.h			\
	splash/SplashMath.h				\
	splash/SplashPath.h				\
	splash/SplashPattern.h				\
	splash/SplashScreen.h				\
	splash/SplashState.h				\
	splash/SplashT1Font.h				\
	splash/SplashT1FontEngine.h			\
	splash/SplashT1FontFile.h			\
	splash/SplashTypes.h				\
	splash/SplashXPath.h				\
	splash/SplashXPathScanner.h
	
SOURCES += splash/Splash.cc				\
	splash/SplashBitmap.cc				\
	splash/SplashClip.cc				\
	splash/SplashFTFont.cc				\
	splash/SplashFTFontEngine.cc			\
	splash/SplashFTFontFile.cc			\
	splash/SplashFont.cc				\
	splash/SplashFontEngine.cc			\
	splash/SplashFontFile.cc			\
	splash/SplashFontFileID.cc			\
	splash/SplashPath.cc				\
	splash/SplashPattern.cc			\
	splash/SplashScreen.cc				\
	splash/SplashState.cc				\
	splash/SplashT1Font.cc				\
	splash/SplashT1FontEngine.cc			\
	splash/SplashT1FontFile.cc			\
	splash/SplashXPath.cc				\
	splash/SplashXPathScanner.cc

# and popple itself

HEADERS += poppler/DCTStream.h \
	poppler/Annot.h \
	poppler/Array.h \
	poppler/ArthurOutputDev.h \
	poppler/BuiltinFont.h \
	poppler/BuiltinFontTables.h \
	poppler/CachedFile.h \
	poppler/Catalog.h \
	poppler/CharCodeToUnicode.h \
	poppler/CharTypes.h \
	poppler/CMap.h \
	poppler/CompactFontTables.h \
	poppler/DateInfo.h \
	poppler/Decrypt.h \
	poppler/Dict.h \
	poppler/ErrorCodes.h \
	poppler/Error.h \
	poppler/FileSpec.h \
	poppler/FontEncodingTables.h \
	poppler/FontInfo.h \
	poppler/Form.h \
	poppler/Function.h \
	poppler/GfxFont.h \
	poppler/Gfx.h \
	poppler/GfxState.h \
	poppler/GfxState_helpers.h \
	poppler/GlobalParams.h \
	poppler/JArithmeticDecoder.h \
	poppler/JBIG2Stream.h \
	poppler/JPXStream.h \
	poppler/Lexer.h \
	poppler/Link.h \
	poppler/LocalPDFDocBuilder.h \
	poppler/Movie.h \
	poppler/NameToCharCode.h \
	poppler/NameToUnicodeTable.h \
	poppler/Object.h \
	poppler/OptionalContent.h \
	poppler/Outline.h \
	poppler/OutputDev.h \
	poppler/Page.h \
	poppler/PageLabelInfo.h \
	poppler/PageTransition.h \
	poppler/Parser.h \
	poppler/PDFDocBuilder.h \
	poppler/PDFDocEncoding.h \
	poppler/PDFDocFactory.h \
	poppler/PDFDoc.h \
	poppler/PopplerCache.h \
	poppler/poppler-config.h \
	poppler/PreScanOutputDev.h \
	poppler/ProfileData.h \
	poppler/PSOutputDev.h \
	poppler/PSTokenizer.h \
	poppler/Rendition.h \
	poppler/SecurityHandler.h \
	poppler/Sound.h \
	poppler/StdinCachedFile.h \
	poppler/StdinPDFDocBuilder.h \
	poppler/Stream-CCITT.h \
	poppler/Stream.h \
	poppler/TextOutputDev.h \
	poppler/UnicodeCClassTables.h \
	poppler/UnicodeCompTables.h \
	poppler/UnicodeDecompTables.h \
	poppler/UnicodeMap.h \
	poppler/UnicodeMapTables.h \
	poppler/UnicodeTypeTable.h \
	poppler/UTF8.h \
	poppler/XpdfPluginAPI.h \
	poppler/XRef.h \
	poppler/SplashOutputDev.h

SOURCES += poppler/DCTStream.cc \
	poppler/Annot.cc \
	poppler/Array.cc \
	poppler/ArthurOutputDev.cc \
	poppler/BuiltinFont.cc \
	poppler/BuiltinFontTables.cc \
	poppler/CachedFile.cc \
	poppler/Catalog.cc \
	poppler/CharCodeToUnicode.cc \
	poppler/CMap.cc \
	poppler/DateInfo.cc \
	poppler/Decrypt.cc \
	poppler/Dict.cc \
	poppler/Error.cc \
	poppler/FileSpec.cc \
	poppler/FontEncodingTables.cc \
	poppler/FontInfo.cc \
	poppler/Form.cc \
	poppler/Function.cc \
	poppler/Gfx.cc \
	poppler/GfxFont.cc \
	poppler/GfxState.cc \
	poppler/GlobalParams.cc \
	poppler/JArithmeticDecoder.cc \
	poppler/JBIG2Stream.cc \
	poppler/JPXStream.cc \
	poppler/Lexer.cc \
	poppler/Link.cc \
	poppler/LocalPDFDocBuilder.cc \
	poppler/Movie.cc \
	poppler/NameToCharCode.cc \
	poppler/Object.cc \
	poppler/OptionalContent.cc \
	poppler/Outline.cc \
	poppler/OutputDev.cc \
	poppler/Page.cc \
	poppler/PageLabelInfo.cc \
	poppler/PageTransition.cc \
	poppler/Parser.cc \
	poppler/PDFDoc.cc \
	poppler/PDFDocEncoding.cc \
	poppler/PDFDocFactory.cc \
	poppler/PopplerCache.cc \
	poppler/PreScanOutputDev.cc \
	poppler/ProfileData.cc \
	poppler/PSOutputDev.cc \
	poppler/PSTokenizer.cc \
	poppler/Rendition.cc \
	poppler/SecurityHandler.cc \
	poppler/Sound.cc \
	poppler/StdinCachedFile.cc \
	poppler/StdinPDFDocBuilder.cc \
	poppler/Stream.cc \
	poppler/TextOutputDev.cc \
	poppler/UnicodeMap.cc \
	poppler/UnicodeTypeTable.cc \
	poppler/XpdfPluginAPI.cc \
	poppler/XRef.cc \
	poppler/SplashOutputDev.cc

# and qt4

HEADERS += qt4/src/poppler-annotation.h \
     qt4/src/poppler-annotation-helper.h \
     qt4/src/poppler-annotation-private.h \
     qt4/src/poppler-converter-private.h \
     qt4/src/poppler-export.h \
     qt4/src/poppler-form.h \
     qt4/src/poppler-link-extractor-private.h \
     qt4/src/poppler-link.h \
     qt4/src/poppler-optcontent.h \
     qt4/src/poppler-optcontent-private.h \
     qt4/src/poppler-page-private.h \
     qt4/src/poppler-page-transition.h \
     qt4/src/poppler-page-transition-private.h \
     qt4/src/poppler-private.h \
     qt4/src/poppler-qiodeviceoutstream-private.h \
     qt4/src/poppler-qt4.h

SOURCES +=   qt4/src/poppler-annotation.cc \
     qt4/src/poppler-base-converter.cc \
     qt4/src/poppler-document.cc \
     qt4/src/poppler-embeddedfile.cc \
     qt4/src/poppler-fontinfo.cc \
     qt4/src/poppler-form.cc \
     qt4/src/poppler-link.cc \
     qt4/src/poppler-link-extractor.cc \
     qt4/src/poppler-movie.cc \
     qt4/src/poppler-optcontent.cc \
     qt4/src/poppler-page.cc \
     qt4/src/poppler-page-transition.cc \
     qt4/src/poppler-pdf-converter.cc \
     qt4/src/poppler-private.cc \
     qt4/src/poppler-ps-converter.cc \
     qt4/src/poppler-qiodeviceoutstream.cc \
     qt4/src/poppler-sound.cc \
     qt4/src/poppler-textbox.cc 
    



INCLUDEPATH += $$INC $$INC/goo/ $$INC/poppler/ $$INC/qt4/src/ \
        $$MKSPEC.INCDIR/freetype2
        