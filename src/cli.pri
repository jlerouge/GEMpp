include(common.pri)
#VERSION = $$GEMVERSION
QT += core
CONFIG += console
linux {
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_LFLAGS += -Wl,-rpath,\'\$$ORIGIN/../lib\'
    QMAKE_LFLAGS += -Wl,--rpath-link=$$[QT_INSTALL_LIBS]:$$OUTLIB
    QMAKE_RPATH =
}
LIBS += -L$$OUTLIB -lGEM++$$LIBMODE
win32: RC_FILE = $$ROOT/cli.rc
INCLUDEPATH += $$ROOT/library/
DESTDIR = $$OUTBIN
target.path = $$PREFIX/bin
INSTALLS += target
