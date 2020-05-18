#include "actor.h"

Actor::Actor()
{
    createAtStartup = true;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
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

    // origin point item
    originPointItem = new QGraphicsEllipseItem(0,0,12,12, this);
    originPointItem->setBrush(QColor(160,70,255));
    originPointItem->setPen(QPen(Qt::NoPen));
    originPointItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    originPointItem->setFlag(QGraphicsItem::ItemIgnoresParentOpacity);  // Why is this Flag not respected!!, the point have same opacity as Actor
    originPointItem->setVisible(false);
}

QPoint Actor::pos()
{
    QPoint po = QGraphicsItem::pos().toPoint();
    po.setX(po.x() + originPointItem->x());
    po.setY(po.y() + originPointItem->y());
    return po;
}

QPoint Actor::scenePos()
{
    QPoint po = QGraphicsItem::scenePos().toPoint();
    po.setX(po.x() + originPointItem->x());
    po.setY(po.y() + originPointItem->y());
    return po;
}

void Actor::setPos(int nx, int ny)
{
    Actor::x = nx;
    Actor::y = ny;
    QGraphicsItem::setPos(nx - originPointItem->x(), ny - originPointItem->y());
}

void Actor::setPos(QPointF f)
{
    Actor::x = int(f.rx());
    Actor::y = int(f.ry());
    QGraphicsItem::setPos(QPointF(f.rx() - originPointItem->x(), f.ry() - originPointItem->y()));
}

void Actor::setX(int nx)
{
    Actor::x = nx;
    QGraphicsItem::setX(nx - originPointItem->x());
}

void Actor::setY(int ny)
{
    Actor::y = ny;
    QGraphicsItem::setY(ny - originPointItem->y());
}

void Actor::setXScale(qreal newXScale)
{
    QTransform tr;

    tr.translate(originPointItem->x(), originPointItem->y());  // to origin
    tr.rotate(rotation);
    tr.scale(newXScale, yscale);
    tr.translate(-originPointItem->x(), -originPointItem->y()); // and back

    setTransform(tr);
    xscale = newXScale;
    width = abs(getWidth() * xscale);
}

void Actor::setYScale(qreal newYScale)
{
    QTransform tr;

    tr.translate(originPointItem->x(), originPointItem->y());  // to origin
    tr.rotate(rotation);
    tr.scale(xscale, newYScale);
    tr.translate(-originPointItem->x(), -originPointItem->y()); // and back

    setTransform(tr);
    yscale = newYScale;
    height = abs(getHeight() * yscale);
}

void Actor::setRotation(qreal ro)
{
    QTransform tr;

    tr.translate(originPointItem->x(), originPointItem->y());  // to origin
    tr.rotate(ro);
    tr.scale(xscale, yscale);
    tr.translate(-originPointItem->x(), - originPointItem->y()); // and back

    setTransform(tr);
    rotation = ro;
}

void Actor::setTintColor(QColor color)
{
    tint = color;
    colorEffect->setColor(tint);
}

void Actor::setTintStrength(qreal strength)
{
    colorFXStrenght = strength;
    colorEffect->setStrength(strength);

    // calling this to live-update the actor when dragging the tint-Strength slider
    setTintColor(tint);
}

void Actor::lockUnLock()
{
    setFlag(QGraphicsItem::ItemIsMovable, isLocked);
    setFlag(QGraphicsItem::ItemIsFocusable, isLocked);
    setFlag(QGraphicsItem::ItemIsSelectable, isLocked);

    isLocked = !isLocked;
}

void Actor::sendDeleteSignal()
{
    emit deleteActor(this); // :(
}

// Protected --------------------------------------------------------------------
//     -----------------------------------------------------------------------

QVariant Actor::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange){
        QPoint newPos = value.toPointF().toPoint();
        newPos.rx() += originPointItem->x();
        newPos.ry() += originPointItem->y();

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

        newPos.rx() -= originPointItem->x();
        newPos.ry() -= originPointItem->y();

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
            if(type == NORMAL)
                colorEffect->setStrength(0.3);
            else colorEffect->setStrength(1);
        }else{
            colorEffect->setColor(tint);
            colorEffect->setStrength(colorFXStrenght);
        }

        originPointItem->setVisible(selected);
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
        default:
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

void Actor::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *lockAction = menu.addAction(isLocked ? "UnLock Actor" : "Lock Actor");
    lockAction->setShortcut(Qt::Key_L);
    QAction *deleteAction = menu.addAction("Delete Actor");
    QAction *selectedAction = menu.exec(event->screenPos());

    // connect those actions to slots
    connect(lockAction, &QAction::triggered, this, &Actor::lockUnLock);
    connect(deleteAction, &QAction::triggered, this, &Actor::sendDeleteSignal);

    if(selectedAction){
        selectedAction->trigger();
    }

}

void Actor::keyPressEvent(QKeyEvent *event)
{
    // if in editor mode then react to arrow keys to move the actor
    if(isSelected()){
        switch(event->key()){
        case Qt::Key_Right:
            setX(x+1);
        break;
        case Qt::Key_Left:
            setX(x-1);
        break;
        case Qt::Key_Up:
            setY(y-1);
        break;
        case Qt::Key_Down:
            setY(y+1);
        break;
        }
    }
}
