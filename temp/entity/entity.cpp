#include "entity.h"
#include <iostream>

bool Entity::boundingBoxVisible;

Entity::Entity()
{
    collidingWithEntity = false;
    boundingBox = sprite.getGlobalBounds();
    visibleBoundingBox.setFillColor(sf::Color(50, 50, 50, 50));
    visibleBoundingBox.setOutlineColor(sf::Color::Red);
    visibleBoundingBox.setOutlineThickness(1);
    depthValue = 0;
    entityType = -1;
    subType = -1;

}

Entity::~Entity()
{

}

sf::FloatRect Entity::getBoundingBox() const
{
    return boundingBox;
}

sf::FloatRect Entity::setBoundingBox(sf::FloatRect box)
{
    boundingBox = box;
    visibleBoundingBox.setPosition(boundingBox.left, boundingBox.top);
    visibleBoundingBox.setSize(sf::Vector2f(boundingBox.width, boundingBox.height));

}

std::string Entity::getName() const
{
    return name;
}

float Entity::getDepthValue() const
{
    return depthValue;
}

int Entity::getEntityType() const
{
    return entityType;
}

int Entity::getSubType() const
{
    return subType;
}

void Entity::toggleBoundingBox()
{
    boundingBoxVisible = !boundingBoxVisible;
}

void Entity::storeEvent(int eType, int eVal, std::string eArgs)
{
    std::cout << "Stored event for " << getName() << " " << eType << ", " << eVal << ", " << eArgs << std::endl;
    events.storeEvent(eType, eVal, eArgs);

}

int Entity::getReturnEvent() const
{
    return events.getReturnEvent();
}

std::queue<Entity*> Entity::getCreatedEnts()
{
    events.getCreatedEntities();
}

void Entity::setCollidingWithEntity(bool colliding)
{
    collidingWithEntity = colliding;
}





