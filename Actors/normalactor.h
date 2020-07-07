#ifndef NORMALACTOR_H
#define NORMALACTOR_H

#include <QObject>

#include "Actors/actor.h"
#include "Components/animation.h"
#include <QTimeLine>
#include <QPainter>

enum AnimationState {FORWARD, BACKWARD, STOPPED, NO_CHANGE};

class NormalActor : public Actor, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NormalActor(QString _name);
    int getWidth();
    int getHeight();
    void createTintImage(QSize s);

    // Animation/Graphics stuff
    QTimeLine localTimeLine;
    QVector<Animation*> animations;
    int animpos{0};
    int animindex{0};
    int nframes;
    AnimationState animationState{STOPPED};
    void addAnimation(Animation * animation);
    void editAnimation(Animation * newAnimation, Animation * oldAnimation);
    int changeAnimation(QString animationName, AnimationState state);
    int changeAnimationDirection(AnimationState state);
    int changeAnimationFrameRate(int fps);
    int getAnimationIndex(QString animName);
    bool antialiasing{false};
    QPainter::CompositionMode compositionMode{QPainter::CompositionMode_SourceOver};
    void setCompositionMode(QString mode);
    QPixmap tintImage;

    // Pure Virtual functions...
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTintColor(QColor color);
    void setTintStrength(qreal strength);

    // overriden functions
    QPainterPath shape() const;
    void setPixmap(const QPixmap &pix);

public slots:
    void setFrame(int frameIndex);
};

#endif // NORMALACTOR_H
