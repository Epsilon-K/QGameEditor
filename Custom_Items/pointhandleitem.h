#ifndef POINTHANDLE_H
#define POINTHANDLE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include "helper.h"

class PointHandleItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    PointHandleItem(QRect r, QGraphicsItem * _parent);
    void setPos(int nx, int ny);
    void setPos(QPoint p);
    void setPos(QPointF f);
    QPoint pos();
    qreal x();
    qreal y();

    QColor selectionColor{QColor(255,255,255)};
    QPoint releasePoint{QPoint(0,0)};
    QPoint finalPosition{QPoint(0,0)};
    bool mouseGrabber = false;

signals:
    void pointChanged();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // POINTHANDLE_H
