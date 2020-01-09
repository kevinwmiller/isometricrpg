#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <vector>
#include <entity.h>

#include "quadtree.h"
#include "isometricmap.h"
#include "entityevents.h"

class EntityList
{
    public:

        EntityList();
        ~EntityList();

        void addEntity(Entity*);
        int getTotalEntities() const;
        void removeEntity(unsigned int);
        Entity* getEntity(unsigned int);
        void cleanUp();

        void handleCollisions();
        void depthSortEntities();

        bool sortByDepthValue(Entity*, Entity*);

        void updateEntities(float, IsometricMap*);
        void drawEntities(sf::RenderWindow&);

    private:

        void quicksort(int, int);
        int totalEntities;
        std::vector<Entity*> entityList;
        QuadTree* quadTree;
};

#endif // ENTITYLIST_H
