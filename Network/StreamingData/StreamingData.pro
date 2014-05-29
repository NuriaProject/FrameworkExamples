CONFIG   += console nuria
QT       += core gui network
NURIA    += core network

DEFINES  += SOURCE_PATH="\\\"$$PWD\\\""
TARGET    = StreamingData
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
