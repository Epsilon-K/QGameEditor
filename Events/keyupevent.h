#ifndef KEYUPEVENT_H
#define KEYUPEVENT_H

#include "Events/event.h"

class KeyUpEvent : public Event
{
public:
    KeyUpEvent();

    int key;
};

#endif // KEYUPEVENT_H
