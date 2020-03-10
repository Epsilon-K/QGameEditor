#ifndef NORMALACTOR_H
#define NORMALACTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "Actors/actor.h"

class NormalActor : public Actor, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NormalActor(QString _name);
    int width();
    int height();
    void setOriginPointToCenter();
    QPoint pos();
    void setPos(qreal nx, qreal ny);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

};

#endif // NORMALACTOR_H
