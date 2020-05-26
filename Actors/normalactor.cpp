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
            if(state != NO_CHANGE){
                animationState = state;
            }
            animindex = i;
            nframes = animations[i]->frames.size();

            localTimeLine.stop();
            changeAnimationFrameRate(animations[i]->frameRate);
            changeAnimationDirection(animationState);
            return 1;
        }
    }

    return 0;   // no such animation exists!
}

int NormalActor::changeAnimationDirection(AnimationState state)
{
    animationState = state;
    if(animations.isEmpty()) return 0;
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

int NormalActor::changeAnimationFrameRate(int fps)
{
    if(animations.isEmpty()) return 0;

    animations[animindex]->frameRate = fps;
    QTimeLine::State originalState = localTimeLine.state();

    if(originalState == QTimeLine::Running) localTimeLine.setPaused(true);
    localTimeLine.setDuration((double(nframes) / fps) * 1000);
    localTimeLine.setFrameRange(0, nframes);
    if(originalState == QTimeLine::Running) localTimeLine.setPaused(false);

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
    painter->setRenderHint(QPainter::SmoothPixmapTransform, antialiasing);

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
    if(animations.isEmpty()) return;
    if(frameIndex > animations[animindex]->frames.size()-1 || frameIndex < 0) return;
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
