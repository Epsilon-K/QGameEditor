#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include "Actions/action.h"
#include <QStringList>

enum EventType {Activation_Event, Animation_Finished, Collision, Collision_Finished, Actor_Created,
                Actor_Destroyed, Draw_Actor, Key_Down, Key_Up, Mouse_Down, Mouse_Up,
                Mouse_Enter, Mouse_Leave, Move_Finished, Out_Of_Vision,
                Path_Finished, Timer_Up};

static const QStringList eventTypeString{"Activation Event", "Animation Finish", "Collision", "Collision Finish", "Create Actor",
            "Destroy Actor", "Draw Actor", "Key Down", "Key Up", "Mouse Down", "Mouse Up",
            "Mouse Enter", "Mouse Leave", "Move Finish", "Out Of Vision",
            "Path Finish", "Timer Up"};

class Event : public QObject
{
    Q_OBJECT
public:
    Event();

    EventType type{Actor_Created};
    QString name;
    Action * action;

signals:

public slots:
};

#endif // EVENT_H
