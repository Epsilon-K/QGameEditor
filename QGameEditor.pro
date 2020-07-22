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
        Actions/action.cpp \
        Actions/changeanimationaction.cpp \
        Actors/actor.cpp \
        Actors/filledregionactor.cpp \
        Actors/normalactor.cpp \
        Actors/textactor.cpp \
        Actors/viewactor.cpp \
        Components/animation.cpp \
        Custom_Items/pointhandleitem.cpp \
        Dialogs/actiondialog.cpp \
        Dialogs/addactordialog.cpp \
        Dialogs/animationdialog.cpp \
        Dialogs/animationsequencedialog.cpp \
        Dialogs/changeanimationdialog.cpp \
        Dialogs/configdialog.cpp \
        Dialogs/eventdialog.cpp \
        Dialogs/settextdialog.cpp \
        Events/collisionevent.cpp \
        Events/createactorevent.cpp \
        Events/drawactorevent.cpp \
        Events/event.cpp \
        Events/keydownevent.cpp \
        Events/keyupevent.cpp \
        editorview.cpp \
        gamescene.cpp \
        main.cpp \
        qgameeditor.cpp

HEADERS += \
        Actions/action.h \
        Actions/changeanimationaction.h \
        Actors/actor.h \
        Actors/filledregionactor.h \
        Actors/normalactor.h \
        Actors/textactor.h \
        Actors/viewactor.h \
        Components/animation.h \
        Custom_Items/pointhandleitem.h \
        Dialogs/actiondialog.h \
        Dialogs/addactordialog.h \
        Dialogs/animationdialog.h \
        Dialogs/animationsequencedialog.h \
        Dialogs/changeanimationdialog.h \
        Dialogs/configdata.h \
        Dialogs/configdialog.h \
        Dialogs/eventdialog.h \
        Dialogs/settextdialog.h \
        Events/collisionevent.h \
        Events/createactorevent.h \
        Events/drawactorevent.h \
        Events/event.h \
        Events/keydownevent.h \
        Events/keyupevent.h \
        editorview.h \
        gamescene.h \
        helper.h \
        qgameeditor.h

FORMS += \
        Dialogs/actiondialog.ui \
        Dialogs/addactordialog.ui \
        Dialogs/animationdialog.ui \
        Dialogs/animationsequencedialog.ui \
        Dialogs/changeanimationdialog.ui \
        Dialogs/configdialog.ui \
        Dialogs/eventdialog.ui \
        Dialogs/settextdialog.ui \
        qgameeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

#This is for Android
android {
    equals(ANDROID_TARGET_ARCH, armeabi-v7a){
        QMAKE_LINK += -nostdlib++
    }
}

DISTFILES +=
