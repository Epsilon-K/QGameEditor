#include "normalactor.h"

NormalActor::NormalActor(QString _name)
{
    name = _name;
    Actor::type = NORMAL;
    QPixmap pix(":/Resources/images/GE Actor in editor.png");
    setPixmap(pix);

    originPointItem->setPos(QPoint(getWidth()/2, getHeight()/2));
    width = getWidth();
    height = getHeight();
    Actor::setTransformOriginPoint(originPointItem->pos());
}

int NormalActor::getWidth()
{
    return int(pixmap().width());
}

int NormalActor::getHeight()
{
    return int(pixmap().height());
}

void NormalActor::addAnimation(Animation *animation)
{
    animations.append(animation);
    changeAnimation(animation->name, FORWARD);
}

int NormalActor::changeAnimation(QString animationName, AnimationState state)
{
    for(int i = 0; i < animations.size(); i++){
        if(animations[i]->name == animationName){
            // set animations[i] as current animation
            animationState = state;
            animindex = i;
            nframes = animations[i]->frames.size();

            // set the first frame of the animation
            setPixmap(*(animations[i]->frames[0]->pixmap));
            return 1;
        }
    }

    return 0;   // no such animation exists!
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
