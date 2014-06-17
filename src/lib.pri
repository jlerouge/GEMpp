include(common.pri)
TEMPLATE = lib
CONFIG += dll
DEFINES += DLL_BUILD
linux {
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_LFLAGS += -Wl,-rpath,\'.\'
    QMAKE_LFLAGS += -Wl,--rpath-link=$$[QT_INSTALL_LIBS]
    QMAKE_RPATH =
}
DESTDIR = $$OUTLIB
target.path = $$PREFIX/lib
INSTALLS += target
