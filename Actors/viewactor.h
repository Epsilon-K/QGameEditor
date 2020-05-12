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
    int getWidth();
    int getHeight();
    QPoint pos();
    QPoint scenePos();
    void setPos(int nx, int ny);
    void setPos(QPointF f);
    void setX(int nx);
    void setY(int ny);

protected:
    QPainterPath shape() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // VIEWACTOR_H
