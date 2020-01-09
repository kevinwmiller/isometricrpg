#ifndef STATEACTION_H
#define STATEACTION_H

#include <iostream>
namespace States
{
    enum stateCodes
    {
        MainMenu = 0,
        SingleplayerMenu,
        MultiplayerMenu,
        CharacterCreate,
        CharacterSelect,
        SinglePlayer,
        MultiPlayer,
        Continue,
        ExitGame,
        TotalStates
    };
}

class StateAction
{
    public:
        StateAction();


        void setAction(int, std::string = "");
        StateAction getAction();
        void operator=(StateAction);
        int getActionState();
        std::string getArgs();

    private:

        int actionState;
        std::string args;

};

#endif // STATEACTION_H
