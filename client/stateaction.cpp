#include "stateaction.h"

StateAction::StateAction()
{
    actionState = States::stateCodes::Continue;
    args = "";
}

void StateAction::setAction(int act, std::string arguments)
{
    if(act >= 0 && act < States::stateCodes::TotalStates)
        actionState = act;
    args = arguments;
}

StateAction StateAction::getAction()
{
    StateAction act;
    act.actionState = actionState;
    act.args = args;

    return act;
}

void StateAction::operator=(StateAction other)
{
    actionState = other.actionState;
    args = other.args;
}

int StateAction::getActionState()
{
    return actionState;
}

std::string StateAction::getArgs()
{
    return args;
}
