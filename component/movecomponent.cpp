#include "movecomponent.h"
#include <iostream>

MoveComponent::MoveComponent()
{
     moving = false;
     running = true;
     walkSpeed = 250;
     runSpeed = 350;
     currentSpeed = runSpeed;
}

MoveComponent::~MoveComponent()
{
    //dtor
}

sf::Vector2f MoveComponent::getMoveAmount() const
{
    return moveAmount;
}

sf::Vector2f MoveComponent::getPosition() const
{
    return currentPos;
}

int MoveComponent::getRunSpeed() const
{
    return runSpeed;
}

int MoveComponent::getWalkSpeed() const
{
    return walkSpeed;
}

int MoveComponent::getCurrentSpeed() const
{
    return currentSpeed;
}

int MoveComponent::getDirection() const
{
    return direction;
}

bool MoveComponent::isRunning() const
{
    return running;
}

bool MoveComponent::isMoving() const
{
    return moving;
}

void MoveComponent::setMaxSpeed(int speed)
{
    std::cout << "Max Speed " << speed << std::endl;
    if(speed >= 0)
    {
        runSpeed = speed;
        walkSpeed = runSpeed * walkSpeedFactor;
    }

    if(running)
        currentSpeed = runSpeed;
    else
        currentSpeed = walkSpeed;

}


void MoveComponent::setPosition(sf::Vector2f newPos)
{
    std::cout << "Old Position " << currentPos.x <<  ", " << currentPos.y << std::endl;
    currentPos = newPos;
    std::cout << "New Position " << currentPos.x <<  ", " << currentPos.y << std::endl;
}

void MoveComponent::stopMoving()
{
    moving = false;
}

void MoveComponent::moveTo(sf::Vector2f newPos)
{
        distanceToDest = sqrt((newPos.y  - currentPos.y) * (newPos.y - currentPos.y) + (newPos.x - currentPos.x) * (newPos.x - currentPos.x));

        if(distanceToDest > maxPixelsAwayFromDest)
        {
            moving = true;
            destPos = newPos;

            //std::cout << "Current Position: (" << pos.x << ", " << pos.y << ")\n";
            //std::cout << "Destination Position: (" << spriteOrigin.x << ", " << spriteOrigin.y << ")\n";

            angle = atan2((destPos.y  - currentPos.y) , (destPos.x - currentPos.x));

            //std::cout << "Angle " << angle << std::endl;
            direction = determineDirection(angle);
        }

}

void MoveComponent::updateMovement(float elapsedTime)
{

    if(moving)
    {
        //Determine the distance to the destination so we know when we can approximate where to stop
        distanceToDest = sqrt((destPos.y  - currentPos.y) * (destPos.y - currentPos.y) + (destPos.x - currentPos.x) * (destPos.x - currentPos.x));

        moveAmount.x = currentSpeed * cos(angle) * elapsedTime;
        moveAmount.y = currentSpeed * sin(angle) * elapsedTime;

        if(distanceToDest < slowingRadius)
        {
            moveAmount.x *= distanceToDest / slowingRadius;
            moveAmount.y *= distanceToDest / slowingRadius;
        }
        currentPos.x += moveAmount.x;
        currentPos.y += moveAmount.y;
        //std::cout << "Move Amount " << moveAmount.x << ", " <<  moveAmount.y << std::endl;
     //   std::cout << "Current Position " << currentPos.x << ", " << currentPos.y << std::endl;

        if(distanceToDest <= maxPixelsAwayFromDest)
        {
            moving = false;
        }
    }
}


void MoveComponent::toggleRunning()
{
    running = !running;

    if(running)
        currentSpeed = runSpeed;
    else
        currentSpeed = walkSpeed;
}

int MoveComponent::determineDirection(double mAngle)
{
    int dir = 0;

    //North
        if(mAngle >= -1.8 && mAngle <= -1.2)
        {
            dir = north;

        }

        //East
        else if(mAngle >= -0.2 && mAngle <= 0.2)
        {
            dir = east;

        }

        //South
        else if(mAngle >= 1.2 && mAngle <= 1.8)
        {
            dir = south;

        }

        //West
        else if(mAngle <= -2.9 || mAngle >= 2.9)
        {
            dir = west;

        }

        //NorthWest
        else if(mAngle > -2.9 && mAngle < -1.8)
        {
            dir = northwest;

        }

        //NorthEast
        else if(mAngle > -1.2 && mAngle < -0.2)
        {
            dir = northeast;

        }

        //SouthEast
        else if(mAngle > 0.2 && mAngle < 1.2)
        {
            dir = southeast;

        }

        //SouthWest
        else
        {
            dir = southwest;

        }

    return dir;
}




