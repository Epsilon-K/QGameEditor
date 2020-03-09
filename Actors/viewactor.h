#ifndef VIEWACTOR_H
#define VIEWACTOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QImage>
#include <QPainter>
#include <QTimer>

#include "Actors/actor.h"

class ViewActor : public Actor, public QGraphicsRectItem
{
    Q_OBJECT
public:
    ViewActor(QString _name, QRect r);

protected:
    QPainterPath shape() const;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // VIEWACTOR_H
