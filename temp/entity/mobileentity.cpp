#include "mobileentity.h"
#include <iostream>

MobileEntity::MobileEntity()
{











}

MobileEntity::~MobileEntity()
{
   // std::cout << "Mobile Entity destructor called\n";
}
/*

void MobileEntity::moveTo(sf::Vector2f newPos, sf::Vector2f spriteOrigin)
{

        data.setDirection(determineDirection(angle));
        currentAnimation->changeDirection(data.getDirection());
}


//spriteOrigin is the point where the sprite appears to touch the ground. Call this function with the point that you want the sprite to move around
void MobileEntity::update(float elapsedTime, sf::Vector2f spriteOrigin, IsometricMap* world)
{
//std::cout << "Elapsed Time: " << elapsedTime << std::endl;
        //std::cout << "Angle: " << angle << std::endl;
        //std::cout << "Direction: " << direction << std::endl;





       // std::cout << world->isOnCollidableTile(sf::Vector2f(spriteOrigin.x + moveAmount.x, spriteOrigin.y + moveAmount.y)) << std::endl;

        if(!world->isOnCollidableTile(sf::Vector2f(spriteOrigin.x + moveAmount.x, spriteOrigin.y + moveAmount.y)))
        {
            collidingWithTile = false;
            sprite.move(moveAmount);
            data.setPos(sprite.getPosition());


        }

         //Move back if player is colliding with something. Move this to a better place after testing
        else
        {
            onTileCollision(elapsedTime);

        }



       // setBoundingBox(sprite.getGlobalBounds());
        //depthValue = (sprite.getGlobalBounds().top);
}


void MobileEntity::onTileCollision(float elapsedTime)
{
    moving = false;
    collidingWithTile = true;
}

void MobileEntity::toggleRunning()
{
    running = !running;

    if(running)
        data.setMaxSpeed(data.getRunSpeed());
    else
        data.setMaxSpeed(data.getWalkSpeed());

}

void MobileEntity::changeAnimation(AnimationSet& newAnim)
{
    currentAnimation = &newAnim;
}
*/
