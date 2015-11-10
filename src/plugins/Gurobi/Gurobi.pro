ROOT = ../..
include($$ROOT/plugin.pri)
#VERSION = $$GEMVERSION
QT += core
linux: LIBS += -lgurobi_c++
win32: LIBS += -lgurobi_c++md$${LIBMODE}2012 -L$$OUTLIB -lGEM++$$LIBMODE
INCLUDEPATH += $$ROOT/library/ \
               $$[GUROBI_HOME]/$$OS$$ARCH/include/
LIBS += -L$$[GUROBI_HOME]/$$OS$$ARCH/lib/ -lgurobi56
HEADERS += GurobiPlugin.h
SOURCES += GurobiPlugin.cpp
TARGET = $$qtLibraryTarget(GEM++Gurobi)
