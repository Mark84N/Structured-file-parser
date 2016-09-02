TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    node.cpp \
    nodetree.cpp \
    parser.cpp \
    variablenode.cpp

HEADERS += \
    node.h \
    nodetree.h \
    parser.h \
    resources.h \
    variablenode.h
