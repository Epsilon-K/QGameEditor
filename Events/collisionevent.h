#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "Events/event.h"

enum Sides {Any, Top, Bottom, Left, Right, TopOrBottom, LeftOrRight};

class CollisionEvent : public Event
{
public:
    CollisionEvent();

    Sides side{Any};
    QString collideActor;
    bool repeat{false};
};

#endif // COLLISIONEVENT_H
