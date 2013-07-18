QT       += core network sql
QT       -= gui
TARGET    = helloWorld.qgi
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE  = app
SOURCES  += main.cpp \
    QtCGI.cpp

HEADERS += \
    QtCGI.h
