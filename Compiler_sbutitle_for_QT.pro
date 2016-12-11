#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T14:24:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Compiler_sbutitle_for_QT
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Token.cpp \
    Subtitle.cpp \
    Parser.cpp \
    Lexical_analyser.cpp

HEADERS  += MainWindow.h \
    Token.h \
    Subtitle.h \
    Parser.h \
    Lexical_analyser.h

FORMS    += MainWindow.ui

DISTFILES += \
    Compiler_sbutitle_for_QT.pro.user
