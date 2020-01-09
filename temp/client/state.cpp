#include "state.h"

void State::setAction(int act, std::string args)
{
    action.setAction(act, args);
}

StateAction State::getAction()
{
    return action;
}
