#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include "Actions/action.h"

enum EventType {Activation_Event, Animation_Finish, Collision, Collision_Finish, Create_Actor,
                Destroy_Actor, Draw_Actor, Key_Down, Key_Up, Mouse_Down, Mouse_Up,
                Mouse_Enter, Mouse_Leave, Move_Finish, Out_Of_Vision,
                Path_Finish, Timer_Up};

class Event : public QObject
{
    Q_OBJECT
public:
    Event();

    EventType type{Create_Actor};
    QString name;
    QVector<Action *> actions;

signals:

public slots:
};

#endif // EVENT_H
