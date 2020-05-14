#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QDebug>
#include <QCursor>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

enum ActorType{NORMAL, VIEW, CANVAS, WIRE_FRAME_REGION, FILLED_REGION, LABEL /*,TILE*/};

class Actor : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Actor();

    // ...
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    QPoint pos();
    QPoint scenePos();
    void setPos(int nx, int ny);
    void setPos(QPointF f);
    void setX(int nx);
    void setY(int ny);

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

    // QGraphicsItem Interface
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    // Editor vars
        // for mouse movement with SHIFT key modifier
    bool xSnap{false};
    bool ySnap{false};

signals:
    // in-Editor signals
    void actorClicked(Actor *);
    void positionChanged(Actor *);
    void actorSelectionChanged(Actor *, bool state);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ACTOR_H
