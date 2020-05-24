#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QFile>
#include <QMovie>
#include <QDebug>

class Frame{
public:
    QPixmap *pixmap;

    // other frame information [future stuff]
};

enum AnimationFileType {SingleFile, MultipleFiles};

class Animation : public QObject
{
    Q_OBJECT
public:
    explicit Animation(QString filePath, QString projectPath, AnimationFileType fType, int hf, int vf, int fps);

    QString name;
    int frameRate;
    int verticalFrames;
    int horizontalFrames;
    AnimationFileType fileType;
    QVector<QString> filesPaths;     // on "data/" folder

    // ------------------------------------
    QVector<Frame*> frames;

signals:

public slots:
};

#endif // ANIMATION_H
