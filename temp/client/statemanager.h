#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include "resourcemanager.h"
#include "mainmenustate.h"
#include "singleplayermenustate.h"
#include "multiplayermenustate.h"
#include "singleplayerstate.h"
#include "charactercreatestate.h"
#include "characterselectstate.h"
#include "state.h"

class StateManager
{
    public:
        StateManager(std::string&);
        ~StateManager();

        void startGameLoop();
        void handleEvents();
        void loadStates();
        void cleanUpState(State&);
        void changeState(State&);

    private:

        bool running;
        State* currentState;
        State* previousState;
        StateAction currentAction;
        std::vector<State*> stateList;

        ResourceManager resources;


};

#endif // STATEMANAGER_H
