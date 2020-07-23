#ifndef SCRIPTACTION_H
#define SCRIPTACTION_H

#include "Actions/action.h"

class ScriptAction : public Action
{
public:
    ScriptAction();

    QString script;
};

#endif // SCRIPTACTION_H
