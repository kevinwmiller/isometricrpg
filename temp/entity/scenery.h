#ifndef SCENERY_H
#define SCENERY_H

#include "entity.h"

class Scenery : public Entity
{
    public:


        //Type of scenery and position
        Scenery(int, sf::Vector3f);
        ~Scenery();

        static void loadTextures(const std::string&);

        const int scenerySize = 128;

        const int totalSceneryTypes = 32;
        const int totalSceneryTypesPerLine = 16;

        sf::Vector2f getEntityOrigin();
        void onEntityCollision(Entity*);
        void updateBoundingBox();
        void handleEvents();
        void update(float, IsometricMap*);
        void draw(sf::RenderWindow&);

    private:

        int sceneryType;
        sf::Vector2f entityOrigin;
        sf::Vector3f position;

        static sf::Texture sceneryTextures;
};

#endif // SCENERY_H
