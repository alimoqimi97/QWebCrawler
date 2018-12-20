#-------------------------------------------------
#
# Project created by QtCreator 2018-12-15T20:54:03
#
#-------------------------------------------------

QT       += core

QT       += network
QT       -= gui

TARGET = QWebCrawler
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    qwebcrawler.cpp \
    thtmlpage.cpp \
    tnode.cpp \
    ttree.cpp

HEADERS += \
    qwebcrawler.h \
    thtmlpage.h \
    tnode.h \
    ttree.h
