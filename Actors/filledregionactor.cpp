#include "filledregionactor.h"

FilledRegionActor::FilledRegionActor(QString _name, QRect r)
{
    name = _name;
    Actor::type = FILLED_REGION;
    QPen cp(Qt::blue, 0);
    setPen(cp);
    setRect(r);

    width = getWidth();
    height = getHeight();
    originPointItem->setPos(QPoint(width/2, height/2));
    updateOriginPoint();
}

int FilledRegionActor::getWidth()
{
    return int(QGraphicsRectItem::boundingRect().width());
}

int FilledRegionActor::getHeight()
{
    return int(QGraphicsRectItem::boundingRect().height());
}

QRectF FilledRegionActor::boundingRect() const
{
    return QGraphicsRectItem::boundingRect();
}

void FilledRegionActor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->setOpacity(1);

    // 1] draw the rect
    QRectF rf = boundingRect();
    painter->drawRect(rf);

    if(Actor::isSelected()){
        QPen p(Qt::white, 0, Qt::DotLine);
        painter->setPen(p);
        painter->drawRect(rf);
    }
}

void FilledRegionActor::setTintColor(QColor color)
{
    tint = color;
}

void FilledRegionActor::setTintStrength(qreal strength)
{
    colorFXStrenght = strength;
    Actor::update();
}
