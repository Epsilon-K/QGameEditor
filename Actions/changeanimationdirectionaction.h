#ifndef CHANGEANIMATIONDIRECTIONACTION_H
#define CHANGEANIMATIONDIRECTIONACTION_H

#include "Actions/action.h"

class ChangeAnimationDirectionAction : public Action
{
public:
    ChangeAnimationDirectionAction();

    QString actor;
    int animState{0}; // {FORWARD, BACKWARD, STOPPED}
};

#endif // CHANGEANIMATIONDIRECTIONACTION_H
