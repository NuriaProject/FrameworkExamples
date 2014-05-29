CONFIG   += console nuria
QT       += core network
NURIA    += core network
QT       -= gui

DEFINES  += SOURCE_PATH="\\\"$$PWD\\\""
TARGET    = FileDelivery
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
