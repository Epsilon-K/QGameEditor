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
    if (change == ItemPositionChange){
        QPoint newPos = value.toPointF().toPoint();
        newPos.rx() += origin.rx();
        newPos.ry() += origin.ry();

        Actor::xprevious = Actor::x;
        Actor::yprevious = Actor::y;

        // handle mouse move snapping
        if(ySnap){  // Snap to Y Axis
            newPos.rx() = xprevious;
        }else if(xSnap) {  // Snap to X Axis
            newPos.ry() = yprevious;
        }

        Actor::x = newPos.rx();
        Actor::y = newPos.ry();

        newPos.rx() -= origin.rx();
        newPos.ry() -= origin.ry();

        return QPointF(newPos);
    }
    else if(change == ItemPositionHasChanged){
        // emit a pos change signal
        emit positionChanged(this);
    }
    return QGraphicsItem::itemChange(change, value);
}

void ViewActor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void ViewActor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
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
    setCursor(QCursor(Qt::PointingHandCursor));
}

void ViewActor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
    // reset snap axis
    xSnap = ySnap = false;
}

void ViewActor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Actor is moved by mouse
    QGraphicsItem::mouseMoveEvent(event);
    if(event->modifiers() == Qt::SHIFT){
        if(! (xSnap || ySnap)){
            // Move actor on a straight line
            int xDiff = abs(xprevious - Actor::x);
            int yDiff = abs(yprevious - Actor::y);
            if(xDiff < yDiff) ySnap = true;
            else xSnap = true;
        }
    }else{
        // reset snap axis
        xSnap = ySnap = false;
    }
}
