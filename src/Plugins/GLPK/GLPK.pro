ROOT = ../..
include($$ROOT/plugin.pri)
GLPK_HOME = C:\glpk-4.56
#VERSION = $$GEMVERSION
QT += core
win32 {
    INCLUDEPATH += $$GLPK_HOME/src
    LIBS += -L$$GLPK_HOME/w$$ARCH/ -lglpk_4_56
}
linux : LIBS += -lglpk
LIBS += -L$$OUTLIB -lGEM++$$LIBMODE
INCLUDEPATH += $$ROOT/GEM++/
HEADERS += GLPKPlugin.h
SOURCES += GLPKPlugin.cpp
TARGET = $$qtLibraryTarget(GEM++GLPK)
