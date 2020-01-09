#include <iostream>
#include "statemanager.h"


StateManager::StateManager(std::string& title)
{
    resources.loadFonts();
    resources.setupWindow(title);
    loadStates();
    previousState = nullptr;
    currentState = nullptr;
    srand(time(NULL));
    running = true;

}

StateManager::~StateManager()
{
    for(auto& state: stateList)
        delete state;
}

void StateManager::startGameLoop()
{

    changeState(*stateList[States::stateCodes::MainMenu]);

    while(running)
    {
        handleEvents();
        currentState->update();
        currentState->draw();

    }

    cleanUpState(*currentState);
}

void StateManager::loadStates()
{

    stateList.resize(States::stateCodes::ExitGame);
    stateList[States::stateCodes::MainMenu] = new MainMenuState(resources);
    stateList[States::stateCodes::SinglePlayer] = new SinglePlayerState(resources);
    stateList[States::stateCodes::SingleplayerMenu] = new SinglePlayerMenuState(resources);
    stateList[States::stateCodes::CharacterCreate] = new CharacterCreateState(resources);
    stateList[States::stateCodes::CharacterSelect] = new CharacterSelectState(resources);

}

void StateManager::handleEvents()
{
    currentAction = currentState->handleEvents();
    //std::cout << "Action: " << action << std::endl;
    //std::cout << "Continue Code: " << States::stateCodes::Continue << std::endl;

    if(currentAction.getActionState() != States::stateCodes::Continue)
    {
        if(currentAction.getActionState() == States::stateCodes::ExitGame)
        {
            running = false;
        }

        else
            changeState(*stateList[currentAction.getActionState()]);
    }

}

void StateManager::cleanUpState(State& state)
{
    state.cleanUp();
}

void StateManager::changeState(State& state)
{

    if(currentState != nullptr)
        previousState = currentState;

    currentState = &state;
    currentState->prepareState(currentAction.getArgs());

    if(previousState != nullptr)
        previousState->cleanUp();

}
