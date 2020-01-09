#ifndef ISOMETRICTILE_H
#define ISOMETRICTILE_H

#include <SFML/Graphics.hpp>

class IsometricTile : public sf::Drawable
{
    public:
        IsometricTile(sf::Texture&, sf::Vector2f, bool);
        ~IsometricTile();

        void setPosition(sf::Vector2f);
        void setSprite(const sf::Texture&);
        void setWalkable(bool);

        sf::Vector2f getWorldCoords();

        bool getWalkable() const;

        sf::Vector2f logicalToIsoCoords(sf::Vector2f);
        sf::Vector2f isoToLogicalCoords(sf::Vector2f);

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

    private:

        bool walkable;
        sf::Sprite sprite;
        sf::Vector2f logicalCoords;
        sf::Vector2f isoCoords;
};

#endif // ISOMETRICTILE_H
