GEMMAJOR = 1
GEMMINOR = 0
GEMPATCH = 0
GEMVERSION = $$GEMMAJOR.$$GEMMINOR.$$GEMPATCH

linux: {
    contains(QMAKE_HOST.arch, x86_64) { ARCH=64 } else { ARCH=32 }
    OS = linux
    DEFINES += LINUX
}
win32 {
    contains(QMAKE_TARGET.arch, x86_64) { ARCH=64 } else { ARCH=32 }
    OS = win
}

CONFIG(release,debug|release) {
    DEFINES += GEMRELEASE # Release mode
    LIBMODE =
    COMPMODE = release
}
CONFIG(debug,debug|release) {
    DEFINES += GEMDEBUG # Debug mode
    win32 { LIBMODE = d } else { LIBMODE = }
    COMPMODE = debug
}

linux {
    PREFIX = /usr/local
    OUTBIN = $$ROOT/$$OS$$ARCH/$$COMPMODE/bin
    OUTLIB = $$ROOT/$$OS$$ARCH/$$COMPMODE/lib
}

win32 {
    PREFIX =
    OUTBIN = $$ROOT/$$OS$$ARCH/$$COMPMODE/
    OUTLIB = $$ROOT/$$OS$$ARCH/$$COMPMODE/
}
