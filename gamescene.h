#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QBrush>
#include "configdata.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();

    QString name;
    QString path;
    SceneProperties *properties;
    Preferences *preferences;
};

#endif // GAMESCENE_H
