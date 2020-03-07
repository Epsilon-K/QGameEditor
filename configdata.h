#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QtCore>
#include <QColor>

enum WindowModes { Windowed, FullScreen};
enum AudioFormats { _44100Hz, _22050Hz, _11050Hz};
enum AudioChannels { Mono, Stereo};

class SceneProperties{
public:
    SceneProperties(){
        windowSize = QSize(720, 480);
        windowMode = WindowModes::Windowed;
        windowTitle = "";
        windowIcon = "";
        frameRate = 60;
        showMouse = true;
        exitWithESC = true;
        suspendWithoutFocus = true;
        motionCompensation = false;
        backgroundColor = QColor(10,10,10);
        audioFormat = AudioFormats::_44100Hz;
        audioChannels = AudioChannels::Stereo;
        maxNumOfSimultaneousSounds = 8;

        sceneSize = QSize(60000,60000);
    }

    QSize windowSize;
    WindowModes windowMode;
    QString windowTitle;
    QString windowIcon;
    qreal frameRate;
    bool showMouse;
    bool exitWithESC;
    bool suspendWithoutFocus;
    bool motionCompensation;
    QColor backgroundColor;
    AudioFormats audioFormat;
    AudioChannels audioChannels;
    int maxNumOfSimultaneousSounds ;

    QSize sceneSize;
};

class Preferences{
public:
    Preferences(){
        gridSize = QSize(20, 20);
        gridColor = QColor(100,100,100);
        resoultionColor = QColor(230,230,230);
        showGrid = true;
        gridSnap = false;
        toolTips = true;
        persistentUndo = false;
        maxUndoLevel = 50;
    }

    QSize gridSize ;
    QColor gridColor ;
    QColor resoultionColor;
    bool showGrid ;
    bool gridSnap;
    bool toolTips;
    bool persistentUndo;
    int maxUndoLevel;
};

#endif // CONFIGDATA_H
