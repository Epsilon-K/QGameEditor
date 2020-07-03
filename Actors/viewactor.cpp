#include "viewactor.h"

ViewActor::ViewActor(QString _name, QRect r)
{
    name = _name;
    Actor::type = VIEW;
    QPen cp(Qt::white, 0);
    setPen(cp);
    setRect(r);

    originPointItem->setPos(QPoint(getWidth()/2, getHeight()/2));
    width = getWidth();
    height = getHeight();
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
    // 1] draw the view rect
    QRectF rf = QRectF(QPointF(QGraphicsRectItem::x()+0.5, QGraphicsRectItem::y()+0.5), QSizeF(QGraphicsRectItem::boundingRect().width()-1, QGraphicsRectItem::boundingRect().height()-1));
    painter->drawRect(rf);



    if(Actor::isSelected()){
        QPen p(selectionColor, 0, Qt::DashLine);
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

