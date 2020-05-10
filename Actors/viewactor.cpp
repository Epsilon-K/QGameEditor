#include "viewactor.h"

ViewActor::ViewActor(QString _name, QRect r)
{
    name = _name;
    Actor::type = VIEW;
    setFlag(QGraphicsItem::ItemClipsToShape);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    QPen cp; cp.setColor(QColor(255,255,255)); cp.setWidth(0);
    setPen(cp);
    setRect(r);
    setAcceptHoverEvents(true);

    origin = QPoint(getWidth()/2, getHeight()/2);
    setTransformOriginPoint(origin);
    setPos(0,0);
    width = getWidth();
    height = getHeight();
}

int ViewActor::getWidth()
{
    return int(boundingRect().width());
}

int ViewActor::getHeight()
{
    return int(boundingRect().height());
}

QPoint ViewActor::pos()
{
    QPoint po = QGraphicsItem::pos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

QPoint ViewActor::scenePos(){
    QPoint po = QGraphicsItem::scenePos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

void ViewActor::setPos(int nx, int ny)
{
    Actor::x = nx;
    Actor::y = ny;
    QGraphicsItem::setPos(nx - origin.x(), ny - origin.y());
}

void ViewActor::setPos(QPointF f)
{
    Actor::x = int(f.rx());
    Actor::y = int(f.ry());
    QGraphicsItem::setPos(QPointF(f.rx() - origin.rx(), f.ry() - origin.ry()));
}

void ViewActor::setX(int nx)
{
    Actor::x = nx;
    QGraphicsItem::setX(nx - origin.rx());
}

void ViewActor::setY(int ny)
{
    Actor::y = ny;
    QGraphicsItem::setY(ny - origin.ry());
}


QPainterPath ViewActor::shape() const
  {
      QPainterPath rectPath;
      rectPath.addRect(this->rect());
      QPainterPathStroker ps; ps.setWidth(3);
      QPainterPath path = ps.createStroke(rectPath);
      return path;
      //return QGraphicsRectItem::shape();
}

QVariant ViewActor::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

void ViewActor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::PointingHandCursor));
}

void ViewActor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(QCursor(Qt::ArrowCursor));
}

void ViewActor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(event->button()){
        case Qt::LeftButton:
        emit actorClicked(this);
        break;
    }
    QGraphicsItem::mousePressEvent(event);
}

void ViewActor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
