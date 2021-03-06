#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T11:20:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableDetection_GUI
TEMPLATE = app

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/include/python2.7

LIBS += -L/usr/local/lib -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -fopenmp
LIBS += -L/usr/lib -ltesseract -llept -pthread #-lPythonQt
LIBS += -lpython2.7


CONFIG +=c++11
QMAKE_CXXFLAGS += -fopenmp -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    mydialog1.cpp \
    mydialog2.cpp \
    preprocessing.cpp \
    averagecharheight.cpp \
    connectingcomponents.cpp \
    lineprocessing.cpp \
    intersectionpoints.cpp \
    reconstruction.cpp \
    pagesegmentation.cpp \
    tableretention.cpp \
    detecttabularlines.cpp \
    white_space_processing.cpp \
    whitespacesegmentation.cpp \
    wsretention.cpp

HEADERS  += mainwindow.h \
    mydialog1.h \
    mydialog2.h \
    preprocessing.h \
    averagecharheight.h \
    connectingcomponents.h \
    lineprocessing.h \
    intersectionpoints.h \
    reconstruction.h \
    pagesegmentation.h \
    tableretention.h \
    detecttabularlines.h \
    white_space_processing.h \
    whitespacesegmentation.h \
    wsretention.h

FORMS    += mainwindow.ui \
    mydialog1.ui \
    mydialog2.ui

OTHER_FILES += \
    pyDocMaker.py


install_this.path = $$OUT_PWD
install_this.files = $$PWD/pyDocMaker.py

INSTALLS += \
        install_this
