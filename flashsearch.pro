#-------------------------------------------------
#
# Project created by QtCreator 2023-12-09T10:55:58
#
#-------------------------------------------------

QT       += core gui sql printsupport



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = flashsearch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablehash.cpp \
    successdelete.cpp \
    faileddelete.cpp \
    successinsert.cpp \
    failedinsert.cpp \
    qcustomplot.cpp \
    comparehashnohash.cpp \
    comparehashhash.cpp \
    basenonchargee.cpp \
    basesauvegardee.cpp \
    donneescorrompues.cpp

HEADERS  += mainwindow.h \
    tablehash.h \
    dbheader.h \
    successdelete.h \
    faileddelete.h \
    successinsert.h \
    failedinsert.h \
    qcustomplot.h \
    comparehashnohash.h \
    comparehashhash.h \
    basenonchargee.h \
    basesauvegardee.h \
    donneescorrompues.h

FORMS    += mainwindow.ui \
    successdelete.ui \
    faileddelete.ui \
    successinsert.ui \
    failedinsert.ui \
    comparehashnohash.ui \
    comparehashhash.ui \
    basenonchargee.ui \
    basesauvegardee.ui \
    donneescorrompues.ui

RESOURCES += \
    resources.qrc
