#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "characterdata.h"
#include "animationcomponent.h"
#include "movecomponent.h"
#include "attackcomponent.h"

class Player : public Entity
{
    public:
        Player();
        ~Player();

        sf::Vector2f getEntityOrigin();
        void onEntityCollision(Entity*);
        void updateBoundingBox();
        void handleEvents();
        void update(float, IsometricMap*);
        void draw(sf::RenderWindow&);

        static void loadAnimations();
        void loadCharacterData(std::string&);
        void saveCharacterData(std::string&);

        void moveTo(sf::Vector2f);
        void attack(sf::Vector2f);
        void toggleRunning();
        int retrieveStatValue(int, const std::string&) const;


    private:

        std::string saveFile;
        CharacterData data;
        AnimationComponent cAnimation;
        MoveComponent cMove;
        AttackComponent cAttack;



};

#endif // PLAYER_H
