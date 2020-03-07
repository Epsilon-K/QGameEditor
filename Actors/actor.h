#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QGraphicsItem>

class Actor : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Actor();
};

#endif // ACTOR_H
