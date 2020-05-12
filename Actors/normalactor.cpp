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
    //setPos(0,0);
    width = getWidth();
    height = getHeight();
}

int NormalActor::getWidth()
{
    return int(pixmap().width());
}

int NormalActor::getHeight()
{
    return int(pixmap().height());
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

void NormalActor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void NormalActor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

void NormalActor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(event->button()){
        case Qt::LeftButton:
            emit actorClicked(this);
        break;
    }

    QGraphicsItem::mousePressEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void NormalActor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
    // reset snap axis
    xSnap = ySnap = false;
}

void NormalActor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
