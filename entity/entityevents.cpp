#include "entityevents.h"
#include "entity.h"

EntityEvents::EntityEvents()
{
    returnEvent = NoEvent;
}

EntityEvents::~EntityEvents()
{
  /*  while(!isEventListEmpty())
    {
        delete events.front();
        events.pop();
    }*/
}

void EntityEvents::sendCreateEntityEvent(Entity* ent)
{

    returnEvent = Create;
    createdEntities.push(ent);

}

void EntityEvents::sendDeleteEntityEvent()
{
   returnEvent = DeleteEnt;
}

void EntityEvents::storeEvent(int eType, int eVal, std::string eArgs)
{
    std::cout << "Storing event " << eType << ", " << eVal << ", " << eArgs << std::endl;
    interEntityEvents.emplace(eType, eVal, eArgs);
    std::cout << "Stored event " << interEntityEvents.front().type << ", " << interEntityEvents.front().value << ", " << interEntityEvents.front().arguments << std::endl;
}

//Delivers an event to an entity for the entity to receive when it is ready
void EntityEvents::sendEvent(Entity* destEntity, int eType, int eValue, std::string eArgs)
{
    std::cout << "Sending event to " << destEntity->getName() << std::endl;
    destEntity->storeEvent(eType, eValue, eArgs);
}

int EntityEvents::getNextEventType()
{
    int noEvent = 0;
    if(!isEventListEmpty())
        return interEntityEvents.front().type;
    else
        return noEvent;
}

int EntityEvents::getNextEventValue()
{
    int noValue = 0;
    if(!isEventListEmpty())
        return interEntityEvents.front().value;
    return noValue;

}

std::string EntityEvents::getNextEventArgs()
{
    std::string noArg("");

    if(!isEventListEmpty())
        return interEntityEvents.front().arguments;
    else
        return noArg;
}

int EntityEvents::getReturnEvent() const
{
    return returnEvent;
}

void EntityEvents::removeEvent()
{
    if(!isEventListEmpty())
    {
        interEntityEvents.pop();
    }
}

 bool EntityEvents::isEventListEmpty()
 {
     return interEntityEvents.size() == 0;
 }

 int EntityEvents::getNumberOfEvents()
 {
     return interEntityEvents.size();
 }

std::queue<Entity*>& EntityEvents::getCreatedEntities()
{
    returnEvent = NoEvent;
    return createdEntities;
}
