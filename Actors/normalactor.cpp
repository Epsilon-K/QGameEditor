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
    originPointItem->setPos(Actor::x, Actor::y);
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
    //QGraphicsPixmapItem::paint(painter, option, widget);

    // 1] draw the pixmap
    // TODO: Render Settings to set rendering options, for now just use the default pixely look
        painter->setRenderHint(QPainter::SmoothPixmapTransform, false);

    QPixmap img = pixmap();
    painter->drawPixmap(boundingRect(), img, QRect(QPoint(0,0), img.size()));

    // 2] draw the purple selection box
    if(Actor::isSelected()){
        QPen p; p.setColor(QColor(160,70,255)); p.setWidth(0);
        painter->setPen(p);
        QRectF r(boundingRect());
        painter->drawRect(r);
    }
}

QPainterPath NormalActor::shape() const
{
    return QGraphicsPixmapItem::shape();
}
