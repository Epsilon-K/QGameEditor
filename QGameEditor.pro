#-------------------------------------------------
#
# Project created by QtCreator 2019-09-19T05:10:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGameEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

RC_ICONS = GE_Icon.ico

SOURCES += \
        Actors/actor.cpp \
        Actors/normalactor.cpp \
        Actors/viewactor.cpp \
        Dialogs/addactordialog.cpp \
        Dialogs/configdialog.cpp \
        editorview.cpp \
        gamescene.cpp \
        main.cpp \
        qgameeditor.cpp

HEADERS += \
        Actors/actor.h \
        Actors/normalactor.h \
        Actors/viewactor.h \
        Dialogs/addactordialog.h \
        Dialogs/configdata.h \
        Dialogs/configdialog.h \
        editorview.h \
        gamescene.h \
        qgameeditor.h

FORMS += \
        Dialogs/addactordialog.ui \
        Dialogs/configdialog.ui \
        qgameeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES +=

#This is for Android
android {
    equals(ANDROID_TARGET_ARCH, armeabi-v7a){
        QMAKE_LINK += -nostdlib++
    }
}
