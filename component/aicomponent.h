#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include <SFML/Graphics.hpp>
#include "movecomponent.h"

class AIComponent
{
    public:
        AIComponent();
        ~AIComponent();

        void setRoamingDistance(int);
        void setHome(sf::Vector2f);

        sf::Vector2f wander();

        void seek(sf::Vector2f);
        void flee(sf::Vector2f);
        void attack(sf::Vector2f);


        void moveToHome();
        void teleportToHome();

    private:

        sf::Vector2f homeLoc;
        int roamingDistance;

        MoveComponent cMove;
};

#endif // AICOMPONENT_H
