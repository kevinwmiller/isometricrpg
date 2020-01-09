#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"
#include "menu.h"

class MainMenuState : public State
{
    public:
        MainMenuState(ResourceManager&);
        ~MainMenuState();

        void prepareState(std::string);
        void cleanUp();

        StateAction handleEvents();
        void update();
        void draw();

        void processChoice(int);


    private:

        Menu menu;
};

#endif // MAINMENUSTATE_H
