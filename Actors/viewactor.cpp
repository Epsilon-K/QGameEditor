#include "viewactor.h"

ViewActor::ViewActor(QString _name, QRect r)
{
    QPen cp; cp.setColor(QColor(255,255,255)); cp.setWidth(0);
    setPen(cp);
    setRect(r);
    setFlag(QGraphicsItem::ItemClipsToShape);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    name = _name;
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
    QGraphicsItem::mousePressEvent(event);
}

void ViewActor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
