#ifndef ENTITYEVENTS_H
#define ENTITYEVENTS_H

#include <queue>
#include <iostream>



struct Event
{
    Event(int eType, int eValue = 0, std::string eArgs = " " )
    {
        type = eType;
        value = eValue;
        arguments = eArgs;
    }

    int type = -1;
    std::string arguments = "";
    int value = 0;
};

class Entity;
class EntityEvents
{
    public:
        EntityEvents();
        ~EntityEvents();

        //Events that are sent back up to the entity list when an entity needs to be created or deleted.
        enum ReturnEvents
        {
            Create = 0,
            DeleteEnt,
            NoEvent,
            TotalReturnEvents
        };

        //Events that are used for inter-Entity communication
        enum InterEntityEvents
        {
            ModifyStat = TotalReturnEvents,
            PermModifyStat,
            PickUp,
            Drop
        };

        void sendCreateEntityEvent(Entity*);
        void sendDeleteEntityEvent();

        void storeEvent(int, int = 0, std::string = "");
        void sendEvent(Entity*, int, int = 0, std::string = "");

        int getReturnEvent() const;
        int getNextEventType();
        int getNextEventValue();
        std::string getNextEventArgs();
        void removeEvent();

        bool isEventListEmpty();
        int getNumberOfEvents();
        std::queue<Entity*>& getCreatedEntities();


    private:

        int returnEvent;
        std::queue<Event> interEntityEvents;
        std::queue<Entity*> createdEntities;

};

#endif // ENTITYEVENTS_H
