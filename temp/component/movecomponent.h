#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H

#include <SFML/Graphics.hpp>

class MoveComponent
{
    public:
        MoveComponent();
        ~MoveComponent();

        const double PI = 3.141592654;
        const int slowingRadius = 70;

        //Walking is half the speed of running
        const float walkSpeedFactor = 0.5;
        const int maxPixelsAwayFromDest = 4;

        enum Direction
        {
            north = 0,
            east,
            south,
            west,
            northwest,
            northeast,
            southeast,
            southwest
        };

        sf::Vector2f getPosition() const;
        sf::Vector2f getMoveAmount() const;
        int getRunSpeed() const;
        int getWalkSpeed() const;
        int getCurrentSpeed() const;
        int getDirection() const;
        bool isRunning() const;
        bool isMoving() const;

        void setMaxSpeed(int);
        void setPosition(sf::Vector2f);
        void stopMoving();
        void resetMoveAmount();

        void moveTo(sf::Vector2f);
        void updateMovement(float);

        void toggleRunning();
        int determineDirection(double);

    private:

        bool moving;
        bool running;

        //Variables to move the entity and fine tune position
        sf::Vector2f currentPos;
        sf::Vector2f destPos;
        sf::Vector2f moveAmount;

        double angle;
        double distanceToDest;

        int direction;
        int walkSpeed;
        int runSpeed;
        int currentSpeed;
};

#endif // MOVECOMPONENT_H
