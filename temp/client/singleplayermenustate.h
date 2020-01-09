#ifndef SINGLEPLAYERMENUSTATE_H
#define SINGLEPLAYERMENUSTATE_H

#include "state.h"
#include "menu.h"

class SinglePlayerMenuState: public State
{
    public:
        SinglePlayerMenuState(ResourceManager&);
        ~SinglePlayerMenuState();

        void prepareState(std::string);
        void cleanUp();

        StateAction handleEvents();
        void update();
        void draw();

        void processChoice(int);
    private:

        Menu menu;
};

#endif // SINGLEPLAYERMENUSTATE_H
