#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QDebug>
#include <QCursor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

enum ActorType{NORMAL, VIEW, CANVAS, WIRE_FRAME_REGION, FILLED_REGION, LABEL /*,TILE*/};

class Actor : public QObject
{
    Q_OBJECT
public:
    Actor();

    // ...
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual QPoint pos() = 0;
    virtual QPoint scenePos() = 0;
    virtual void setPos(int nx, int ny) = 0;
    virtual void setPos(QPointF f) = 0;
    virtual void setX(int nx) = 0;
    virtual void setY(int ny) = 0;

    // Actor Properties
    ActorType type;
    QString name;
    QString clonename;
    int cloneindex;

    QPoint origin;
    bool createAtStartup;

    int x, y;
    int xprevious, yprevious;
    int xscreen, yscreen;
    int xvelocity, yvelocity;
    int angle, directional_velocity;
    int width, height;
    qreal zdepth, transp;
    qreal rotation;
    qreal xscale, yscale;
    // user vars...

    // ...

    // Editor vars
        // for mouse movement with SHIFT key modifier
    bool xSnap{false};
    bool ySnap{false};

signals:
    // in-Editor signals
    void actorClicked(Actor *);
    void positionChanged(Actor *);
};

#endif // ACTOR_H
