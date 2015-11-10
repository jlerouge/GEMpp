ROOT = ../..
include($$ROOT/plugin.pri)
#VERSION = $$GEMVERSION
QT += core
DEFINES += ILOUSESTL
INCLUDEPATH += $$ROOT/library/ \
               $$[CPLEX_HOME]/cplex/include \
               $$[CPLEX_HOME]/concert/include
linux {
    contains(QMAKE_HOST.arch, x86_64) { CPLEXDIR = x86-64 } else { CPLEXDIR = x86 }
    CPLEXDIR = $${CPLEXDIR}_linux/static_pic
    LIBS += -L$$[CPLEX_HOME]/cplex/lib/$${CPLEXDIR} -lilocplex -L$$[CPLEX_HOME]/concert/lib/$${CPLEXDIR} -lconcert -lcplex -lm -lpthread
}
win32 {
    contains(QMAKE_TARGET.arch, x86_64) { CPLEXDIR = x64 } else { CPLEXDIR = x86 }
    CPLEXDIR = $${CPLEXDIR}_windows_vs2012
    CONFIG(release,debug|release) { CPLEXDIR = $${CPLEXDIR}/stat_mda }
    CONFIG(debug,debug|release) { CPLEXDIR = $${CPLEXDIR}/stat_mdd }
    LIBS += -L$$[CPLEX_HOME]/cplex/lib/$$CPLEXDIR -lilocplex -lcplex1260 -L$$[CPLEX_HOME]/concert/lib/$$CPLEXDIR -lconcert -L$$OUTLIB -lGEM++$$LIBMODE#-lm -lpthread -lmsvcrt
}
HEADERS += CplexPlugin.h
SOURCES += CplexPlugin.cpp
TARGET = $$qtLibraryTarget(GEM++Cplex)
