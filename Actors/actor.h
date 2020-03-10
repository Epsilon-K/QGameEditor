#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QCursor>

enum ActorType{NORMAL, VIEW, CANVAS, WIRE_FRAME_REGION, FILLED_REGION, LABEL /*,TILE*/};

class Actor : public QObject
{
    Q_OBJECT
public:
    Actor();
    QString pointToString(QPoint p);

    QPoint origin;

    // Actor Properties
    ActorType type;
    QString name;
    QString clonename;
    int cloneindex;

    int x, y;
    int xprevious, yprevious;
    int xscreen, yscreen;
    int xvelocity, yvelocity;
    int angle, directional_velocity;
    int width, height;
    qreal zdepth, transp;

    // user vars...
};

#endif // ACTOR_H
