#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <SFML/Graphics.hpp>
#include "animationset.h"
#include "characterdata.h"

class MobileEntity
{
    public:
        MobileEntity();
        ~MobileEntity();

        const double PI = 3.141592654;

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

        void update(float, bool);

        //Each entity has different animations to load
        virtual void loadAnimations() = 0;

        //Each entity has a diffeent sprite and therefore a different foot position
        virtual sf::Vector2f getFeetPosition() = 0;

        void moveTo(sf::Vector2f);
        void changeAnimation(AnimationSet&);
        int determineDirection(double);
        void toggleRunning();

        void onTileCollision();
        void onEntityCollision();

        //Stores information such as stats, position, level, etc.
        CharacterData data;

        virtual void draw(sf::RenderWindow&) = 0;

    protected:



        sf::Color color;

        void setPosition(sf::Vector2f);
        void setSprite(sf::Texture&);

        bool alive;
        bool moving;
        bool attacking;
        bool running;
        sf::Texture unarmedTexture;

        //Variables to move the entity and fine tune position
        sf::Vector2f destPos;
        sf::Vector2f trueDestPos;
        double angle;
        double distanceToDest;

        int walkSpeed;
        int runSpeed;

        sf::Texture* currentTexture;
        AnimationSet* currentAnimation;

        sf::Sprite sprite;

};

#endif // MOBILEENTITY_H
