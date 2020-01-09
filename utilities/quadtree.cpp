#include "quadtree.h"
#include <iostream>
QuadTree::QuadTree()
{
    //std::cout << "Creating quadtree\n";
    level = 0;
    bounds.left = 0;
    bounds.top = 0;
    bounds.width = 0;
    bounds.height = 0;


}

QuadTree::QuadTree(int _level, sf::FloatRect _bounds)
{

    std::cout << "Creating quadtree\n";
    level = _level;
    bounds = _bounds;

    nodes[0] = nullptr;

}

QuadTree::~QuadTree()
{
}

void QuadTree::clear()
{
    objects.clear();

    //Only 4 nodes. Northeast, northwest, southwest, southeast
    for(int i = 0; i < NUM_NODES; i++)
    {
        if(nodes[i] != nullptr)
        {
            nodes[i]->clear();
            nodes[i] = nullptr;
        }
    }
}

void QuadTree::split()
{
    int subWidth = bounds.width / 2;
    int subHeight = bounds.height / 2;
    int x = bounds.left;
    int y = bounds.top;

    nodes[0] = new QuadTree(level + 1, sf::FloatRect(x + subWidth, y, subWidth, subHeight));
    nodes[1] = new QuadTree(level + 1, sf::FloatRect(x, y, subWidth, subHeight));
    nodes[2] = new QuadTree(level + 1, sf::FloatRect(x, y + subHeight, subWidth, subHeight));
    nodes[3] = new QuadTree(level + 1, sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::getIndex(Entity* ent)
{
    int index = -1;

    /*
         _________
        |    |    |
        |    |    |
        |---------|  <--Horizontal Midpoint
        |    |    |
        |____|____|

             ^ Vertical Midpoint
    */

    double verticalMidpoint = bounds.left + (bounds.width / 2);
    double horizontalMidpoint = bounds.top + (bounds.height / 2);

    //Will the rectangle fit completely in the top quadrants?
    bool topQuadrant = (ent->getBoundingBox().top < horizontalMidpoint && ent->getBoundingBox().top + ent->getBoundingBox().height < horizontalMidpoint);

    //Will the rectangle fit completely in the bottom quadrants
    bool bottomQuadrant = (ent->getBoundingBox().top > horizontalMidpoint);

    //Will the object fit within the left quadrants? If so top or bottom?
    if(ent->getBoundingBox().left < verticalMidpoint && ent->getBoundingBox().left + ent->getBoundingBox().width < verticalMidpoint)
    {
        if(topQuadrant)
            index = 1;
        else if(bottomQuadrant)
            index = 2;
    }

    //Will the rectangle fit within the right quadrants? If so top or bottom?
    else if(ent->getBoundingBox().left > verticalMidpoint)
    {
        if(topQuadrant)
            index = 0;
        else if(bottomQuadrant)
            index = 3;
    }

    return index;
}

void QuadTree::insert(Entity* ent)
{

    if(nodes[0] != nullptr)
    {

        int index = getIndex(ent);

        if(index != -1)
        {

            nodes[index]->insert(ent);

            return;
        }
    }

    objects.push_back(ent);

    if(objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
    {
        if(nodes[0] == nullptr)
            split();

        unsigned int i = 0;
        while(i < objects.size())
        {
            int index = getIndex(objects[i]);
            if(index != -1)
            {
                //Remove the element from the parent node and insert it into the child node.
                Entity* temp = objects[i];
                objects.erase(objects.begin() + i);

                nodes[index]->insert(temp);
            }
            else
                i++;
        }
    }

    std::cout << "End of insert function\n";
}

std::vector<Entity*> QuadTree::retrieve(std::vector<Entity*> returnObjects, Entity* ent)
{
    int index = getIndex(ent);

    if(index != -1 && nodes[0] != nullptr)
        nodes[index]->retrieve(returnObjects, ent);

    for(unsigned int i = 0; i < objects.size(); i++)
        returnObjects.push_back(objects[i]);

    return returnObjects;
}
