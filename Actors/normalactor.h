#ifndef NORMALACTOR_H
#define NORMALACTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "Actors/actor.h"

class NormalActor : public Actor, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    NormalActor(QString _name);
};

#endif // NORMALACTOR_H
