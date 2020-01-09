#ifndef WOLF_H
#define WOLF_H

#include <SFML/Graphics.hpp>
#include "entity.h"
#include "characterdata.h"
#include "animationcomponent.h"
#include "movecomponent.h"
#include "attackcomponent.h"
#include "aicomponent.h"

class Wolf : public Entity
{
    public:
        Wolf();
        ~Wolf();

        void startAttack(sf::Vector2f);
        void stopAttack();

        static void loadAnimations();

        sf::Vector2f getEntityOrigin();
        void onEntityCollision(Entity*);
        void updateBoundingBox();
        void handleEvents();
        void update(float, IsometricMap*);
        void draw(sf::RenderWindow&);

        private:

        static int numWolves;

        CharacterData data;
        AnimationComponent cAnimation;
        MoveComponent cMove;
        AttackComponent cAttack;
        AIComponent cAI;


};

#endif // WOLF_H
