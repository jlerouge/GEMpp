include(common.pri)
TEMPLATE = lib
CONFIG += plugin
linux {
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_LFLAGS += -Wl,-rpath,\'.\'
    QMAKE_RPATH =
}
DESTDIR = $$OUTLIB
target.path = $$PREFIX/lib
INSTALLS += target
