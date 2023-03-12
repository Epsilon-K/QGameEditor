#ifndef KEYDOWNEVENT_H
#define KEYDOWNEVENT_H

#include "Events/event.h"

enum ExecutionType {At_Least_One_Pressed, All_Pressed, Pressed_In_Order};

class KeyDownEvent : public Event
{
public:
    KeyDownEvent();

    QList <int> keys;
    ExecutionType executeWhen{At_Least_One_Pressed};
    bool repeat{true};
};

#endif // KEYDOWNEVENT_H
