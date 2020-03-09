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
    addItem(view);
    actors.append(view);
}

QRect GameScene::getwindowRect()
{
    QSize ws = properties->windowSize;
    return QRect(-ws.width()/2, -ws.height()/2, ws.width(), ws.height());
}
