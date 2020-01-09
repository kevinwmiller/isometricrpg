//Generic quadtree class with necessary structs.
//Point is used to represent a coordinate.
//Bounding box is the rectangle used to represent the objects that are stored in the quad tree

#ifndef QUADTREE_H
#define QUADTREE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"

class QuadTree
{
    public:
        QuadTree();
        QuadTree(int, sf::FloatRect);
        ~QuadTree();

      const unsigned int MAX_OBJECTS = 10;
      const unsigned int MAX_LEVELS = 5;
      const unsigned int NUM_NODES = 4;

      void clear();
      void split();
      int getIndex(Entity*);
      void insert(Entity*);
      std::vector<Entity*> retrieve(std::vector<Entity*>, Entity*);

    private:

        int level;
        std::vector<Entity*> objects;
        sf::FloatRect bounds;

        QuadTree** nodes;


};



#endif // QUADTREE_H
