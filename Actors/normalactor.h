#ifndef NORMALACTOR_H
#define NORMALACTOR_H

#include <QObject>

#include "Actors/actor.h"

class NormalActor : public Actor, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NormalActor(QString _name);
    int getWidth();
    int getHeight();

    // Pure Virtual functions...
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // overriden functions
    QPainterPath shape() const;
};

#endif // NORMALACTOR_H
