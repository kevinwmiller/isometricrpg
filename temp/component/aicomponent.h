#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include <SFML/Graphics.hpp>

class AIComponent
{
    public:
        AIComponent();
        ~AIComponent();

        void setRoamingDistance(int);
        void setHome(const sf::Vector2f&);

        int getHomeLoc() const;
        int getRoamingDistance() const;

        sf::Vector2f wander();

        void seek(sf::Vector2f);
        void flee(sf::Vector2f);
        void attack(sf::Vector2f);


        void moveToHome();
        void teleportToHome();

    private:

        sf::Vector2f homeLoc;
        int roamingDistance;

};

#endif // AICOMPONENT_H
