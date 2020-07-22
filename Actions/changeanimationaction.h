#ifndef CHANGEANIMATIONACTION_H
#define CHANGEANIMATIONACTION_H

#include "Actions/action.h"

class ChangeAnimationAction : public Action
{
public:
    ChangeAnimationAction();

    QString actor;
    QString animation;
    int animState{0}; // {FORWARD, BACKWARD, STOPPED, NO_CHANGE}
};

#endif // CHANGEANIMATIONACTION_H
