#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QPixmap>
#include <QImage>

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
    explicit Animation(QObject *parent = nullptr);

    QString name;
    int frameRate;
    int verticalFrames;
    int horizontalFrames;
    AnimationFileType fileType;

    // ------------------------------------
    QVector<Frame*> frames;

signals:

public slots:
};

#endif // ANIMATION_H
