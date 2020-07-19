#include "event.h"

Event::Event(EventType _type, QObject *parent) : QObject(parent)
{
    type = _type;
}
