#include "staticentity.h"

StaticEntity::StaticEntity()
{
    entityType = Entity::Type::Static;
}

StaticEntity::~StaticEntity()
{
   // std::cout << "Static Entity destructor called\n";
}
