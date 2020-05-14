#include "actor.h"

Actor::Actor()
{
    createAtStartup = true;
    //setFlag(QGraphicsItem::ItemClipsToShape);     // no need for this anymore... we will see.
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);


    //default RGB colorEffect in GE
    tint = QColor(255,170,0);
    colorEffect = new QGraphicsColorizeEffect();
    colorEffect->setColor(tint);
    colorEffect->setStrength(colorFXStrenght);
    Actor::setGraphicsEffect(colorEffect);
    colorEffect->setEnabled(true);
}

QPoint Actor::pos()
{
    QPoint po = QGraphicsItem::pos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

QPoint Actor::scenePos()
{
    QPoint po = QGraphicsItem::scenePos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

void Actor::setPos(int nx, int ny)
{
    Actor::x = nx;
    Actor::y = ny;
    QGraphicsItem::setPos(nx - origin.x(), ny - origin.y());
}

void Actor::setPos(QPointF f)
{
    Actor::x = int(f.rx());
    Actor::y = int(f.ry());
    QGraphicsItem::setPos(QPointF(f.rx() - origin.rx(), f.ry() - origin.ry()));
}

void Actor::setX(int nx)
{
    Actor::x = nx;
    QGraphicsItem::setX(nx - origin.rx());
}

void Actor::setY(int ny)
{
    Actor::y = ny;
    QGraphicsItem::setY(ny - origin.ry());
}

void Actor::setTintColor(QColor color)
{
    QColor newColor = color;
    tint = newColor;
    colorFXStrenght = tint.alphaF();
    colorEffect->setColor(tint);
    colorEffect->setStrength(colorFXStrenght);
    update();
}

// Protected --------------------------------------------------------------------

QVariant Actor::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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

    if(change == ItemSelectedHasChanged){
        bool selected = value.toBool();

        if(selected){
            colorEffect->setColor(QColor(160,70,255,255));
            colorEffect->setStrength(0.3);
        }else{
            colorEffect->setColor(tint);
            colorEffect->setStrength(colorFXStrenght);
        }
        // emit the change
        emit actorSelectionChanged(this, selected);
    }
    return QGraphicsItem::itemChange(change, value);
}

void Actor::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void Actor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
    setCursor(QCursor(Qt::ArrowCursor));
}

void Actor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch(event->button()){
        case Qt::LeftButton:
            emit actorClicked(this);
        break;
    }
    QGraphicsItem::mousePressEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
}

void Actor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    setCursor(QCursor(Qt::PointingHandCursor));
    // reset snap axis
    xSnap = ySnap = false;
}

void Actor::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
