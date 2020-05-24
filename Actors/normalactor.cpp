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

    localTimeLine.setCurveShape(QTimeLine::LinearCurve);
    localTimeLine.setLoopCount(0);
    connect(&localTimeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
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
    changeAnimation(animation->name, animationState);
}

int NormalActor::changeAnimation(QString animationName, AnimationState state)
{
    for(int i = 0; i < animations.size(); i++){
        if(animations[i]->name == animationName){
            // set animations[i] as current animation
            animationState = state;
            animindex = i;
            nframes = animations[i]->frames.size();

            localTimeLine.stop();
            localTimeLine.setDuration((double(nframes) / animations[animindex]->frameRate) * 1000);
            localTimeLine.setFrameRange(0, animations[animindex]->frames.size());
            if(animationState == FORWARD){
                localTimeLine.setDirection(QTimeLine::Forward);
                localTimeLine.start();
            }else if(animationState == BACKWARD){
                localTimeLine.setDirection(QTimeLine::Backward);
                localTimeLine.start();
            }
            else if(animationState == STOPPED){
                setFrame(0);
            }

            return 1;
        }
    }

    return 0;   // no such animation exists!
}

int NormalActor::ChangeAnimationDirection(AnimationState state)
{
    localTimeLine.stop();
    switch(state){
    case FORWARD:
        localTimeLine.setDirection(QTimeLine::Forward);
        localTimeLine.start();
        break;
    case BACKWARD:
        localTimeLine.setDirection(QTimeLine::Backward);
        localTimeLine.start();
        break;
    case STOPPED:
        setFrame(0);
    }
    return 1;
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

void NormalActor::setFrame(int frameIndex)
{
    if(frameIndex > animations[animindex]->frames.size()-1) return;
    qreal ox = originPointItem->x() / width;
    qreal oy = originPointItem->y() / height;
    int olx = Actor::x;
    int oly = Actor::y;

    animpos = frameIndex;
    setPixmap(*(animations[animindex]->frames[animpos]->pixmap));

    // update...
    width = abs(getWidth() * xscale);
    height = abs(getHeight() * yscale);

    originPointItem->setPos(int(width * ox), int(height * oy));
    Actor::update();
    Actor::setPos(olx, oly);
    Actor::setRotation(Actor::rotation);
}
