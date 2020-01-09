#include "isometrictile.h"

IsometricTile::IsometricTile(sf::Texture& tex, sf::Vector2f position,  bool isWalkable)
{
    sprite.setTexture(tex);
    sprite.setPosition(position);
    logicalCoords = position;
    isoCoords = logicalToIsoCoords(position);

    setWalkable(isWalkable);
}

IsometricTile::~IsometricTile()
{
    //dtor
}

void IsometricTile::setPosition(sf::Vector2f position)
{
    sprite.setPosition(position);
}

void IsometricTile::setSprite(const sf::Texture& tex)
{
    sprite.setTexture(tex);
}

void IsometricTile::setWalkable(bool isWalkable)
{
    walkable = isWalkable;
}

bool IsometricTile::getWalkable() const
{
    return walkable;
}

sf::Vector2f IsometricTile::getWorldCoords()
{
    return logicalCoords;
}

sf::Vector2f IsometricTile::logicalToIsoCoords(sf::Vector2f pos)
{
    return sf::Vector2f( (2 * pos.x) - (2 * pos.y), pos.x + pos.y);
}

sf::Vector2f IsometricTile::isoToLogicalCoords(sf::Vector2f pos)
{
    return sf::Vector2f( (2 * pos.x) - (2 * pos.y), pos.x + pos.y);
}

void IsometricTile::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(sprite);
}
