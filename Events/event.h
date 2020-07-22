#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include "Actions/action.h"

enum EventType {Activation_Event, Animation_Finished, Collision, Collision_Finished, Actor_Created,
                Actor_Destroyed, Draw_Actor, Key_Down, Key_Up, Mouse_Down, Mouse_Up,
                Mouse_Enter, Mouse_Leave, Move_Finished, Out_Of_Vision,
                Path_Finished, Timer_Up};

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
