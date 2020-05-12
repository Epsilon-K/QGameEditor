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
    view->setPos(0,0);
    actors.prepend(view);
}

QRect GameScene::getwindowRect()
{
    QSize ws = properties->windowSize;
    return QRect(0, 0, ws.width(), ws.height());
}
