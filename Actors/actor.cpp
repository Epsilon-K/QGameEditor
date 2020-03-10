#include "actor.h"

Actor::Actor()
{
    createAtStartup = true;
}

QString Actor::pointToString(QPoint p)
{
    return "(" + QString::number(p.x()) + ", " + QString::number(p.y()) + ")";
}
