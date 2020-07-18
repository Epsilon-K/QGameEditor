#include "viewactor.h"

ViewActor::ViewActor(QString _name, QRect r)
{
    name = _name;
    Actor::type = VIEW;
    QPen cp(Qt::white, 0);
    setPen(cp);
    setRect(r);

    width = getWidth();
    height = getHeight();
    originPointItem->setPos(QPoint(width/2, height/2));
    updateOriginPoint();
}

int ViewActor::getWidth()
{
    return int(QGraphicsRectItem::boundingRect().width());
}

int ViewActor::getHeight()
{
    return int(QGraphicsRectItem::boundingRect().height());
}

QRectF ViewActor::boundingRect() const
{
    return QGraphicsRectItem::boundingRect();
}

void ViewActor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    painter->setPen(pen());
    painter->setOpacity(1);

    // 1] draw the view rect
    QRectF rf = boundingRect();
    painter->drawRect(rf);


    if(Actor::isSelected()){
        QPen p(Qt::blue, 0, Qt::DotLine);
        painter->setPen(p);
        painter->drawRect(rf);
    }
}

void ViewActor::setTintColor(QColor color)
{
    tint = color;
}

void ViewActor::setTintStrength(qreal strength)
{
    colorFXStrenght = strength;
    Actor::update();
}

QPainterPath ViewActor::shape() const
{
    // the default shape has a filled rect, which we don't want, It should be a hollow rectangle
        //return QGraphicsRectItem::shape();

    QPainterPath rect;
    rect.addRect(QRectF(QPointF(QGraphicsRectItem::x()+0.5, QGraphicsRectItem::y()+0.5), QSizeF(QGraphicsRectItem::boundingRect().width()-1, QGraphicsRectItem::boundingRect().height()-1)));
    QPainterPathStroker ps; ps.setWidth(1);
    QPainterPath rectOutline = ps.createStroke(rect);
    return rectOutline;
}

