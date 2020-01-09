#include "mousecursor.h"
#include <iostream>

MouseCursor::MouseCursor()
{
    entityType = Entity::Type::Misc;
    subType = -1;
    depthValue = 0;
    cursorPos.x = 0;
    cursorPos.y = 0;
    height = 0;
    name = "Mouse Cursor";
    //Make the bounding box a single point where the mouse cursor is pointing to

}

MouseCursor::~MouseCursor()
{
    std::cout << "Mouse Cursor destructor called\n";
}

void MouseCursor::updateCursorPosition(sf::RenderWindow& window, sf::View& view)
{

    cursorPos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
  //  std::cout << "Mouse Position " << cursorPos.x  << ", " << cursorPos.y << std::endl;
    setBoundingBox(sf::FloatRect(cursorPos.x, cursorPos.y, 1, 1));
}


void MouseCursor::onEntityCollision(Entity* otherEntity)
{
  //  std::cout << name << " colliding with " << otherEntity->getName() << std::endl;

    if(otherEntity->getEntityType() == Entity::Type::Mobile)
    {
        if(otherEntity->getSubType() == Entity::MobileSubType::Player)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                events.sendEvent(otherEntity, EntityEvents::InterEntityEvents::ModifyStat, 1, "Health");
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                events.sendEvent(otherEntity, EntityEvents::InterEntityEvents::ModifyStat, -1, "Health");
        }
    }
}
void MouseCursor::handleEvents()
{

}

sf::Vector2f MouseCursor::getEntityOrigin()
{
    return cursorPos;
}

void MouseCursor::updateBoundingBox()
{
    setBoundingBox(sf::FloatRect(cursorPos.x, cursorPos.y, 1, 1));
}

//Currently, the mouse cursor doesn't need to update anything, but they are needed because of the entity class.
//These can be used if the mouse cursor is replaced in the future.
void MouseCursor::update(float elapsedTime, IsometricMap* world)
{

}

void MouseCursor::draw(sf::RenderWindow& window)
{

}
