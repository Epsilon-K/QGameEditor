#ifndef NORMALACTOR_H
#define NORMALACTOR_H

#include <QObject>

#include "Actors/actor.h"
#include "Components/animation.h"
#include <QTimeLine>

enum AnimationState {FORWARD, BACKWARD, STOPPED, NO_CHANGE};

class NormalActor : public Actor, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NormalActor(QString _name);
    int getWidth();
    int getHeight();

    // Animation stuff
    QTimeLine localTimeLine;
    QVector<Animation*> animations;
    int animpos{0};
    int animindex{0};
    int nframes;
    AnimationState animationState{STOPPED};
    void addAnimation(Animation * animation);
    int changeAnimation(QString animationName, AnimationState state);
    int ChangeAnimationDirection(AnimationState state);

    // Pure Virtual functions...
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // overriden functions
    QPainterPath shape() const;

public slots:
    void setFrame(int frameIndex);
};

#endif // NORMALACTOR_H
