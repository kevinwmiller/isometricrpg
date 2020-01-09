#include "scenery.h"
#include <iostream>
#include <sstream>
sf::Texture Scenery::sceneryTextures;


Scenery::Scenery(int sceneType, sf::Vector3f pos)
{
    std::stringstream ss;

   // std::cout << "Scene Type " << sceneType << std::endl;
    if(sceneType >= 0 && sceneType < totalSceneryTypes)
        sceneryType = sceneType;
    else
        sceneryType = 0;

    ss << sceneryType;
    position = pos;
    sprite.setTexture(sceneryTextures);
    sprite.setPosition(position.x, position.y);

    entityType = Entity::Type::Static;
    subType = Entity::StaticSubType::Scenery;

    //Determine the position of the correct image in the texture set
    int row = sceneryType / totalSceneryTypesPerLine * scenerySize;
    int col = (sceneryType % totalSceneryTypesPerLine) * scenerySize;

    //std::cout << "Image Position " << sceneryType << ": " << row << ", " << col << std::endl;

    sprite.setTextureRect(sf::IntRect(col, row, scenerySize, scenerySize));
    updateBoundingBox();
    //Scenery Objects are 128 x 128 by default and share a similar size.


    entityOrigin = sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().top + 106);

    name = "Scenery type " + ss.str();

  //  std::cout << "Position " << position.x << ", " << position.y << std::endl << std::endl;;
}


Scenery::~Scenery()
{
    //dtor
}

sf::Vector2f Scenery::getEntityOrigin()
{
    return entityOrigin;
}

void Scenery::updateBoundingBox()
{
    setBoundingBox(sf::FloatRect(sprite.getPosition().x + 55, sprite.getPosition().y + 73, 22, 36));
}

void Scenery::onEntityCollision(Entity* ent)
{
    //Scenery doesn't need to do anything
  //  std::cout << name << " colliding with " << ent->getName() << std::endl;
}

void Scenery::loadTextures(const std::string& sceneryTextureFile)
{
    sceneryTextures.loadFromFile(sceneryTextureFile);
}

void Scenery::handleEvents()
{

}

void Scenery::update(float elapsedTime, IsometricMap* world)
{

 //   sprite.setPosition(position.x, position.y - position.z);
    depthValue = entityOrigin.y + position.z;
}

void Scenery::draw(sf::RenderWindow& window)
{
  /*  int color = rand() % 10;

    if(color == 0)
        sprite.setColor(sf::Color::Red);
    else if(color == 1)
        sprite.setColor(sf::Color::Blue);
    else if(color == 2)
        sprite.setColor(sf::Color::Green);
    else if(color == 3)
        sprite.setColor(sf::Color::Cyan);
    else if(color == 4)
        sprite.setColor(sf::Color::Transparent);
    else if(color == 5)
        sprite.setColor(sf::Color::Magenta);
    else if(color == 6)
        sprite.setColor(sf::Color::Black);
    else if(color == 7)
        sprite.setColor(sf::Color::Yellow);
    else if(color == 8)
        sprite.setColor(sf::Color(34, 34, 50, 75));
    else if(color == 9)
        sprite.setColor(sf::Color::White);
*/
    window.draw(sprite);

    if(boundingBoxVisible)
        window.draw(visibleBoundingBox);
}
