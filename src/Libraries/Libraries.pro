ROOT = ..
include($$ROOT/common.pri)
TEMPLATE = subdirs
SUBDIRS = QGar
linux: qtlibs.files = Qt/linux$$ARCH/lib*
win32: qtlibs.files = Qt/win$$ARCH/*
qtlibs.path = $$PREFIX/lib
INSTALLS += qtlibs
linux {
    imageformats.files = Qt/linux$$ARCH/imageformats/*
    imageformats.path = $$PREFIX/bin/imageformats/
    INSTALLS += imageformats

    platforms.files = Qt/linux$$ARCH/platforms/*
    platforms.path = $$PREFIX/bin/platforms/
    INSTALLS += platforms
}
