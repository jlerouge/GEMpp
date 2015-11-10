include(common.pri)
#VERSION = $$GEMVERSION
TEMPLATE = app
QT += core gui widgets
linux {
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_LFLAGS += -Wl,-rpath,\'\$$ORIGIN/../lib\'
    QMAKE_LFLAGS += -Wl,--rpath-link=$$[QT_INSTALL_LIBS]:$$OUTLIB
    QMAKE_RPATH =
}
LIBS += -L$$OUTLIB -lGEM++$$LIBMODE
win32: RC_FILE = $$ROOT/gui.rc
INCLUDEPATH += $$ROOT/library/
DESTDIR = $$OUTBIN
target.path = $$PREFIX/bin
INSTALLS += target
