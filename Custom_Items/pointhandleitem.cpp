#include "pointhandleitem.h"

PointHandleItem::PointHandleItem(QRect r, QGraphicsItem * _parent)
{
    setRect(r);
    if(_parent != nullptr) setParentItem(_parent);

    setBrush(color);
    setPen(QPen(Qt::NoPen));

    setVisible(false);
    setAcceptHoverEvents(true);
    //setFlag(ItemIgnoresTransformations);      //TODO : activate this without messing eveything up!
    setFlag(ItemIgnoresParentOpacity);
    setFlag(ItemSendsScenePositionChanges);
}

void PointHandleItem::setPos(int nx, int ny)
{
    QGraphicsItem::setPos(nx - boundingRect().width()/2,
                          ny - boundingRect().height()/2);
    if(!mouseGrabber){
        finalPosition = QPoint(nx, ny);
        emit pointChanged();
    }
}

void PointHandleItem::setPos(QPoint p)
{
    QGraphicsItem::setPos(p.x() - boundingRect().width()/2,
                          p.y() - boundingRect().height()/2);
    if(!mouseGrabber){
        finalPosition = p;
        emit pointChanged();
    }
}

void PointHandleItem::setPos(QPointF f)
{
    PointHandleItem::setPos(f.toPoint());
}

void PointHandleItem::setX(int x)
{
    setPos(x, y());
}

void PointHandleItem::setY(int y)
{
    setPos(x(), y);
}

QPoint PointHandleItem::pos()
{
    QPoint po = QGraphicsItem::pos().toPoint();
    po.setX(po.x() + boundingRect().width()/2);
    po.setY(po.y() + boundingRect().height()/2);
    return po;
}

qreal PointHandleItem::x()
{
    return PointHandleItem::pos().x();
}

qreal PointHandleItem::y()
{
    return PointHandleItem::pos().y();
}

QVariant PointHandleItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange){
        return value.toPoint();
    }
    return QGraphicsItem::itemChange(change, value);
}

void PointHandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setCompositionMode(QPainter::CompositionMode_Difference);
    QGraphicsEllipseItem::paint(painter,option,widget);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->setPen(QPen(Qt::darkYellow, 0));
    painter->drawLine(0, boundingRect().height()/2, boundingRect().width(), boundingRect().height()/2);
    painter->drawLine(boundingRect().width()/2, 0, boundingRect().width()/2, boundingRect().height());
}

void PointHandleItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
}

void PointHandleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
}

void PointHandleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mouseGrabber = true;
    pressPos = mapToParent(event->pos()).toPoint();
    setCursor(QCursor(Qt::PointingHandCursor));
}

void PointHandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(scene()->mouseGrabberItem() == this){
        setPos(mapToParent(event->pos().toPoint()));
        emit posChanging();
    }
}

void PointHandleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mouseGrabber = false;
    setCursor(QCursor(Qt::PointingHandCursor));
    finalPosition = pos();
    releasePoint = parentItem()->mapToParent(mapToParent(event->pos().toPoint())).toPoint();
    emit pointChanged();
}
