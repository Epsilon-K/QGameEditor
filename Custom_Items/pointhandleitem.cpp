#include "pointhandleitem.h"

PointHandleItem::PointHandleItem(QRect r, QGraphicsItem * _parent = nullptr)
{
    setRect(r);
    if(_parent) setParentItem(_parent);

    setBrush(selectionColor);
    setPen(QPen(Qt::NoPen));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity);
    setVisible(false);
}
