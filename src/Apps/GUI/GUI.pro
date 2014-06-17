ROOT = ../..
include($$ROOT/gui.pri)
RESOURCES = GUI.qrc
HEADERS  += \
    MainWindow.h \
    QGraphWidget.h \
    QSubgraphDialog.h
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    QGraphWidget.cpp \
    QSubgraphDialog.cpp

TARGET = GEM++gui
