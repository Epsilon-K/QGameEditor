#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QImage>
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

enum AnimationFileType {SINGLE_FILE, MULTIPLE_FILES};
enum AnimationType {PURE_ANIMATION, SEQUENCE_ANIMATION};

class Animation : public QObject
{
    Q_OBJECT
public:
    explicit Animation(QString animationName, QString filePath, QString projectPath, AnimationFileType fType, int hf, int vf, int fps, bool transpPixel, bool temporary);
    explicit Animation(QString animationName, Animation * base, QVector<int> seq, int fps);
    ~Animation();
    QPixmap * defaultPixmap{new QPixmap(defaultSpritePath)};

    QPixmap *drawClippedImage(QImage &img, QRgb maskColor);

    QString name;
    int frameRate;
    int verticalFrames;
    int horizontalFrames;
    bool firstPixelAsTransparent{false};
    AnimationFileType fileType{SINGLE_FILE};
    QVector<QString> filesPaths;     // on "data/" folder

    AnimationType type{PURE_ANIMATION};

    // ------------------------------------
    QVector<Frame*> frames;

    QVector<int> sequence;  // a sequence of frames in a different Pure-Animation (0_index based)
    Animation *baseAnimation;   // the animation this sequence is based on


    // ------------ Functions ------------------
    int getNumberOfFrames();
    QPixmap *getFramePixmap(int frameNumber);

signals:

public slots:
};

#endif // ANIMATION_H
