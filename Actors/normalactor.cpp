#include "normalactor.h"

NormalActor::NormalActor(QString _name)
{
    setFlag(QGraphicsItem::ItemClipsToShape);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setAcceptHoverEvents(true);

    QPixmap pix(":/Resources/images/GE Actor in editor.png");
    setPixmap(pix);

    setOriginPointToCenter();
    setPos(0,0);

    name = _name;
}

int NormalActor::width()
{
    return int(boundingRect().width());
}

int NormalActor::height()
{
    return int(boundingRect().height());
}

void NormalActor::setOriginPointToCenter()
{
    origin = QPoint(width()/2, height()/2);
    setTransformOriginPoint(origin);
}

QPoint NormalActor::pos()
{
    QPoint po = QGraphicsPixmapItem::pos().toPoint();
    po.setX(po.x() + origin.x());
    po.setY(po.y() + origin.y());
    return po;
}

void NormalActor::setPos(qreal nx, qreal ny)
{
    QGraphicsItem::setPos(nx - origin.x(), ny - origin.y());
}

QVariant NormalActor::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged){
        // emit a pos change signal
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
