#ifndef PHYSICALRESPONSEACTION_H
#define PHYSICALRESPONSEACTION_H

#include "Actions/action.h"

enum MoveOption {Move_Event_Actor, Move_Collide_Actor, Move_Both};

class PhysicalResponseAction : public Action
{
public:
    PhysicalResponseAction();

    MoveOption moveOption{Move_Event_Actor};

    bool calculatedMass{true};
    qreal eventMass{1};
    qreal collideMass{1};

    qreal eventFinalVelocityMultiplier{1};
    qreal collideFinalVelocityMultiplier{1};
};

#endif // PHYSICALRESPONSEACTION_H
