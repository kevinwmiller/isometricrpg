#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "isometricmap.h"
#include "isometricconversions.h"
#include "entityevents.h"

class EntityEvents;
class Entity
{
    public:
        Entity();
        virtual ~Entity();

        enum Type
        {
            Mobile = 0,
            Static,
            Misc,
            TotalTypes
        };

        enum MobileSubType
        {
            Player = 0,
            Npc,
            Projectile,
            TotalMobileSubTypes
        };

        enum StaticSubType
        {
            Scenery = 0,
            Trap,
            Item,
            TotalStaticSubTypes
        };

        float getDepthValue() const;
        std::string getName() const;

        int getEntityType() const;
        int getSubType() const;
        void toggleBoundingBox();

        sf::FloatRect getBoundingBox() const;
        void setBoundingBox(const sf::FloatRect&);

        virtual sf::Vector2f getEntityOrigin() = 0;
        virtual void onEntityCollision(Entity*) = 0;
        virtual void updateBoundingBox() = 0;
        virtual void handleEvents() = 0;
        virtual void update(float, IsometricMap*) = 0;
        virtual void draw(sf::RenderWindow&) = 0;

        void setCollidingWithEntity(bool);

        void storeEvent(int, int = 0, std::string = "");
        int getReturnEvent() const;
        std::queue<Entity*> getCreatedEnts();


    protected:

        sf::Color color;
        int entityType;
        int subType;
        float depthValue;
        std::string name;
        float height;
        IsometricConversions isoConversions;
        sf::FloatRect boundingBox;
        sf::RectangleShape visibleBoundingBox;
        sf::Sprite sprite;
        static bool boundingBoxVisible;

        bool collidingWithEntity;

        EntityEvents events;
};

#endif // ENTITY_H
