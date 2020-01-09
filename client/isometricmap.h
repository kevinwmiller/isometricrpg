#ifndef ISOMETRICMAP_H
#define ISOMETRICMAP_H

#include <vector>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
#include "isometrictile.h"
#include "vectoroverloads.h"
#include "isometricconversions.h"

class IsometricMap
{
    public:

        const int tileWidth = 128;
        const int tileHeight = 64;
        const int collidableIndex = 4;

        //Remove after testing
        const int scenerySize = 128;

        IsometricMap(const std::string, const std::string, const std::string);
        ~IsometricMap();

        void loadFloorImages(const std::string);
        void loatObjectImages(const std::string);
        void loadBuildingImages(const std::string);

        void loadFloorMap(const std::string);
        void loadObjectMap(const std::string);
        void loadBuildingMap(const std::string);

        bool isOnCollidableTile(sf::Vector2f);
        bool isOnCollidableTile(sf::Vector2i);

        void draw(sf::RenderWindow&);

        sf::Vector2i getMapSizeInTiles() const;
        sf::Vector2f getMapSizeInPixels() const;

        sf::Vector2i screenToMapCoords(sf::Vector2f);
        sf::Vector2f mapToScreenCoords(sf::Vector2i);

    private:

        sf::Image floorImages;
        sf::Image objectImages;
        sf::Image buildingImages;

        //Store the position and the sprites of all collidable tiles on the current map
        std::map<sf::Vector2f, IsometricTile> collidableTiles;

        std::vector<std::vector<IsometricTile>> floors;
        std::vector<std::vector<IsometricTile>> objects;
        std::vector<std::vector<IsometricTile>> buildings;

        std::vector<std::vector<int>> floorMap;
        std::vector<std::vector<int>> objectMap;
        std::vector<std::vector<int>> buildingMap;

        static std::vector<sf::Texture> floorTextures;
        static std::vector<sf::Texture> objectTextures;
        static std::vector<sf::Texture> buildingTextures;

        IsometricConversions isoConversions;

        sf::Vector2i mapSizeInTiles;

        sf::Vector2f mapSizeInPixels;
};

#endif // ISOMETRICMAP_H
