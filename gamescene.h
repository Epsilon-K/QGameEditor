#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsLineItem>
#include <QBrush>
#include <Dialogs/configdata.h>

#include "Actors/normalactor.h"
#include "Actors/viewactor.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    QRect getwindowRect();
    Actor * getActorByName(QString actorName);

    QString name;
    QString path;
    SceneProperties *properties;
    Preferences *preferences;

    QVector<Actor*> actors;
};

#endif // GAMESCENE_H
