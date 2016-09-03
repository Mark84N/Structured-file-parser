TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    node.cpp \
    nodetree.cpp \
    variablenode.cpp \
    parseengine.cpp \
    xmltreewriter.cpp \
    parserprogram.cpp

HEADERS += \
    node.h \
    nodetree.h \
    resources.h \
    variablenode.h \
    parseengine.h \
    itreewriter.h \
    xmltreewriter.h \
    parserprogram.h
