#include "actor.h"

Actor::Actor()
{

}

QString Actor::pointToString(QPoint p)
{
    return "(" + QString::number(p.x()) + ", " + QString::number(p.y()) + ")";
}
