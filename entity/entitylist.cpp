#include "entitylist.h"
#include <iostream>
EntityList::EntityList()
{
    std::cout << "Creating Entity List\n";
    totalEntities = 0;
    //Reserve space for 100 entities
    entityList.reserve(100);
}

EntityList::~EntityList()
{

}



void EntityList::addEntity(Entity* entity)
{
    //std::cout << "Adding entity " << entity->getName() << std::endl;
    entityList.push_back(entity);
   // std::cout << "Finished Adding entity " << entity->getName() << std::endl;

    totalEntities++;
}

int EntityList::getTotalEntities() const
{
    return totalEntities;
}

void EntityList::removeEntity(unsigned int index)
{
    if(index < entityList.size() && index >= 0)
    {
        entityList.erase(entityList.begin() + index);
        totalEntities--;
    }
}

Entity* EntityList::getEntity(unsigned int index)
{
    Entity* test = nullptr;

    if(index >= 0 && index < entityList.size())
        return entityList[index];
    else
        return test;
}

void EntityList::handleCollisions()
{

}

void EntityList::depthSortEntities()
{
    //std::cout << "Before sort\n";
    for(unsigned int i = 0; i < entityList.size(); i++)
    {

     //   std::cout << i << ": " << entityList[i]->getBoundingBox().top << std::endl;
        //std::cout << i << ": " << sortedEntityIndeces[i] << std::endl;
    }
    quicksort(0, entityList.size() - 1);
    //std::sort(entityList.begin(), entityList.end());
   // std::cout << "After sort\n";
    for(unsigned int i = 0; i < entityList.size(); i++)
    {
      //  std::cout << i << ": " << entityList[i]->getBoundingBox().top << std::endl;
        //std::cout << i << ": " << sortedEntityIndeces[i] << std::endl;
    }
}

void EntityList::updateEntities(float elapsedTime, IsometricMap* world)
{
  /*  quadTree = new QuadTree(0, sf::FloatRect(sf::Vector2f(0,0) , world->getMapSizeInPixels()));
    for(int i = 0; i < entityList.size(); i++)
        quadTree->insert(entityList[i]);

    std::vector<Entity*> returnObjects;
*/
    for(unsigned int i = 0; i < entityList.size(); i++)
    {
        entityList[i]->update(elapsedTime, world);

        for(unsigned int k = 0; k < entityList.size(); k++)
        {
            if (k != i)
            {
                if(entityList[i]->getBoundingBox().intersects(entityList[k]->getBoundingBox()))
                    entityList[i]->onEntityCollision(entityList[k]);

            }

            if(entityList[i]->getReturnEvent() == EntityEvents::ReturnEvents::Create)
            {
                while(!entityList[i]->getCreatedEnts().empty())
                {
                    addEntity(entityList[i]->getCreatedEnts().front());
                    entityList[i]->getCreatedEnts().pop();
                }
            }
        }


   /*     returnObjects.clear();
        returnObjects = quadTree->retrieve(returnObjects, entityList[i]);*/

    /*    for(int k = 0; k < returnObjects.size(); i++)
        {
            if(entityList[i]->getBoundingBox().intersects(returnObjects[k]->getBoundingBox()))
               entityList[i]->onEntityCollision(returnObjects[k]);
        }
*/
       // std::cout << "Updating " << entityList[i]->getName() << std::endl;
    }

  /*  quadTree->clear();
    delete quadTree;*/
}

void EntityList::cleanUp()
{
    for(unsigned int i = 0; i < entityList.size(); i++)
    {
        std::cout << "Total Entities " << totalEntities << std::endl;
        std::cout << "Size " << entityList.size() << "\n";
        std::cout << "Deleting Entity " << entityList[i]->getName() << "\n";
        delete entityList[i];
        totalEntities--;
    }
    entityList.clear();
}

void EntityList::drawEntities(sf::RenderWindow& window)
{
    depthSortEntities();
    for(unsigned int i = 0; i < entityList.size(); i++)
    {
        entityList[i]->draw(window);
      //  std::cout << "Drawing " << entityList[i]->getName() << std::endl;
    }
}


void EntityList::quicksort(int left, int right)
{

    int i = left;
    int j = right;
    Entity* temp;
    Entity* pivot = entityList[(left + right) / 2];

    while (i <= j)
    {
     //   std::cout << "i" << i << "\n";
      //  std::cout << "j" << j << "\n";
        while (entityList[i]->getDepthValue() < pivot->getDepthValue())
        {
      //      std::cout << "increasing i " << i << "\n";
            i++;
        }
     //   std::cout << "j Portion" << "\n";
        while (entityList[j]->getDepthValue() > pivot->getDepthValue())
        {
            j--;
      //      std::cout << "decreasing j " << j << "\n";
        }
     //   std::cout << "swap Portion" << "\n";
        if( i <= j)
        {
      //      std::cout << "Swapping\n";
            temp = entityList[i];
            entityList[i] = entityList[j];
            entityList[j] = temp;
            temp = nullptr;
            i++;
            j--;
        }
    }

//std::cout << "After while loop\n\n";
    if(left < j)
    {
      //  std::cout << "Left " << left<< "\n";
       // std::cout << "Right " << j<< "\n";
        quicksort(left, j);
    }

    if(i < right)
    {
      //  std::cout << "AALeft " << i<< "\n";
      //  std::cout << "AARight " << right<< "\n";
        quicksort(i, right);
    }

}
