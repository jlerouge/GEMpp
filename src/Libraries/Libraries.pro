ROOT = ..
include($$ROOT/common.pri)
TEMPLATE = subdirs
SUBDIRS = QGar

qtlibs.files = Qt/$$OS$$ARCH/$$QT_VERSION/*.$$DLL_FILE_EXT*
qtlibs.path = $$PREFIX/lib

qtimageformats.files = Qt/$$OS$$ARCH/$$QT_VERSION/imageformats/*.$$DLL_FILE_EXT*
qtimageformats.path = $$PREFIX/bin/imageformats/

qtplatforms.files = Qt/$$OS$$ARCH/$$QT_VERSION/platforms/*.$$DLL_FILE_EXT*
qtplatforms.path = $$PREFIX/bin/platforms/

INSTALLS += qtlibs
INSTALLS += qtimageformats
INSTALLS += qtplatforms

