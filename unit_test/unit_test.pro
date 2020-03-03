QT += core
QT -= gui

QMAKE_CXXFLAGS += -std=c++1y
CONFIG += c++1y

TARGET = unit_test
CONFIG += console
CONFIG -= app_bundle

LIBS += -lpthread
LIBS += ../bignumber.o
LIBS += /usr/src/gtest/src/libgtest.a
LIBS += /usr/src/gtest/src/libgtest_main.a

TEMPLATE = app

SOURCES += main.cpp

