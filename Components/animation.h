#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QFile>
#include <QDir>
#include <QMovie>
#include <QPainter>
#include <QRegion>
#include <QBitmap>

#include "helper.h"

class Frame{
public:
    Frame(){}
    ~Frame(){
        delete pixmap;
    }
    QPixmap *pixmap;

    // other frame information [future stuff]
};

enum AnimationFileType {SingleFile, MultipleFiles};

class Animation : public QObject
{
    Q_OBJECT
public:
    explicit Animation(QString animationName, QString filePath, QString projectPath, AnimationFileType fType, int hf, int vf, int fps, bool transpPixel, bool temporary);
    ~Animation();
    QPixmap *drawClippedImage(QImage &img, QRgb maskColor);

    QString name;
    int frameRate;
    int verticalFrames;
    int horizontalFrames;
    bool firstPixelAsTransparent{false};
    AnimationFileType fileType;
    QVector<QString> filesPaths;     // on "data/" folder

    // ------------------------------------
    QVector<Frame*> frames;

signals:

public slots:
};

#endif // ANIMATION_H
