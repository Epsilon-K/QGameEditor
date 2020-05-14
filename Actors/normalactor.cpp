#include "normalactor.h"

NormalActor::NormalActor(QString _name)
{
    name = _name;
    Actor::type = NORMAL;
    QPixmap pix(":/Resources/images/GE Actor in editor.png");
    setPixmap(pix);

    origin = QPoint(getWidth()/2, getHeight()/2);
    width = getWidth();
    height = getHeight();
    Actor::setTransformOriginPoint(origin);
}

int NormalActor::getWidth()
{
    return int(pixmap().width());
}

int NormalActor::getHeight()
{
    return int(pixmap().height());
}

QRectF NormalActor::boundingRect() const
{
    return QGraphicsPixmapItem::boundingRect();
}

void NormalActor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 1] draw the pixmap
    QPixmap img = pixmap();
    painter->drawPixmap(boundingRect(), img, QRect(QPoint(0,0), img.size()));

    // 2] draw the purple selection box
    if(Actor::isSelected()){
        QPen p; p.setColor(QColor(160,70,255)); p.setWidth(1);
        painter->setPen(p);
        QRectF r(0.5,0.5,boundingRect().width()-1, boundingRect().height()-1);
        painter->drawRect(r);
    }
}

QPainterPath NormalActor::shape() const
{
    return QGraphicsPixmapItem::shape();
}
