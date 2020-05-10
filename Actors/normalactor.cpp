#include "normalactor.h"

NormalActor::NormalActor(QString _name)
{
    name = _name;
    Actor::type = NORMAL;
    setFlag(QGraphicsItem::ItemClipsToShape);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

    QPixmap pix(":/Resources/images/GE Actor in editor.png");
    setPixmap(pix);

    origin = QPoint(getWidth()/2, getHeight()/2);
    setTransformOriginPoint(origin);
    setPos(0,0);
    width = getWidth();
    height = getHeight();
}

int NormalActor::getWidth()
{
    return int(boundingRect().width());
}

int NormalActor::getHeight()
{
    return int(boundingRect().height());
}

QPoint NormalActor::pos()
{
    QPoint po = QGraphicsItem::pos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

QPoint NormalActor::scenePos(){
    QPoint po = QGraphicsItem::scenePos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

void NormalActor::setPos(int nx, int ny)
{
    Actor::x = nx;
    Actor::y = ny;
    QGraphicsItem::setPos(Actor::x - origin.x(), Actor::y - origin.y());
}

void NormalActor::setPos(QPointF f)
{
    Actor::x = int(f.rx());
    Actor::y = int(f.ry());
    QGraphicsItem::setPos(Actor::x - origin.x(), Actor::y - origin.y());
}

void NormalActor::setX(int nx)
{
    Actor::x = nx;
    QGraphicsItem::setX(nx - origin.rx());
}

void NormalActor::setY(int ny)
{
    Actor::y = ny;
    QGraphicsItem::setY(ny - origin.ry());
}

QVariant NormalActor::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged){
        Actor::x = pos().rx();
        Actor::y = pos().ry();
        // because it should be discreet numbers
        setPos(Actor::x, Actor::y);
        // emit a pos change signal
        emit positionChanged(this);
    }
    return QGraphicsItem::itemChange(change, value);
}

void NormalActor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    // emit mouse enter signal
}

void NormalActor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
    // emit mouse leave signal
}

void NormalActor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(event->button()){
        case Qt::LeftButton:
            emit actorClicked(this);
        break;
    }

    QGraphicsItem::mousePressEvent(event);
}
