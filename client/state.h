#ifndef STATE_H
#define STATE_H

#include "resourcemanager.h"
#include "stateaction.h"



class State
{
    public:
        State(ResourceManager& resourceManager): resources(resourceManager) {}
        virtual ~State() {}
        virtual void prepareState(std::string) = 0;
        virtual void cleanUp() = 0;

        virtual StateAction handleEvents() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        void setAction(int, std::string = "");
        StateAction getAction();

        ResourceManager& resources;

    protected:

        StateAction action;

};

#endif // STATE_H
