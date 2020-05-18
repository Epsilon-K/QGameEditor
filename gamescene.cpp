#include "gamescene.h"

GameScene::GameScene()
{
    properties = new SceneProperties();
    preferences = new Preferences();
    name = "Untitled";
    path = "none";

    // for performance
    setItemIndexMethod(QGraphicsScene::NoIndex);

    // Add Default View Actor
    ViewActor *view = new ViewActor("view", getwindowRect());
    addItem((Actor*)view);
    view->Actor::setPos(0,0);
    actors.append((Actor*)view);

    // Add a normal actor
    NormalActor *actor = new NormalActor("tester");
    addItem((Actor*)actor);
    actor->Actor::setPos(0,0);
    actors.append((Actor*)actor);
}

QRect GameScene::getwindowRect()
{
    QSize ws = properties->windowSize;
    return QRect(0, 0, ws.width(), ws.height());
}

Actor *GameScene::getActorByName(QString actorName)
{
    for(int i = 0; i < actors.size(); i++){
        if(actorName == actors[i]->name){
            return actors[i];
        }
    }

    // this should not happen!!!
    // TODO: log a warning message
    return actors[0];
}
