TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    node_source.cpp \
    nodetree_source.cpp \
    parser_source.cpp \
    variablenode_source.cpp

HEADERS += \
    node.h \
    nodetree.h \
    parser.h \
    resources.h \
    variablenode.h
