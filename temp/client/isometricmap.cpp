#include "isometricmap.h"
#include <iostream>
#include <cmath>

std::vector<sf::Texture> IsometricMap::floorTextures;
std::vector<sf::Texture> IsometricMap::objectTextures;
std::vector<sf::Texture> IsometricMap::buildingTextures;

IsometricMap::IsometricMap(const std::string floorImgFile, const std::string objectImgFile, const std::string buildingImgFile)
{
    mapSizeInPixels.x = 0;
    mapSizeInPixels.y = 0;

    mapSizeInTiles.x = 0;
    mapSizeInTiles.y = 0;

    loadFloorImages(floorImgFile);
    loadBuildingImages(buildingImgFile);
}

IsometricMap::~IsometricMap()
{
    //dtor
}


void IsometricMap::loadFloorImages(const std::string file)
{
    std::cout << "Loading " << file << "...\n";

    floorImages.loadFromFile(file);

    int tileCount = 16;

    floorTextures.resize(tileCount * tileCount);

    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            if (!floorTextures[y * tileCount + x].loadFromImage(floorImages,
                sf::IntRect(x * tileWidth, y * tileWidth,
                tileWidth, tileHeight)))
                    exit(103);
            floorTextures[y * tileCount + x].setSmooth(false);
        }
    }

    std::cout << file << " loaded successfully!\n";

}

void IsometricMap::loatObjectImages(const std::string file)
{
    std::cout << "Loading " << file << "...\n";
    objectImages.loadFromFile(file);

    // Split up the image into separate textures on your GPU
    int tileCount = (scenerySize * 16) / tileWidth;

    objectTextures.resize(tileCount * tileCount);

    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            if (!objectTextures[y * tileCount + x].loadFromImage(objectImages,
                sf::IntRect(x * tileWidth, y * tileWidth,
                (x + 1) * tileWidth, (y + 1) * tileWidth)))
                    exit(103);
            objectTextures[y * tileCount + x].setSmooth(false);
        }
    }
    std::cout << file << " loaded successfully!\n";
}

void IsometricMap::loadBuildingImages(const std::string file)
{
    std::cout << "Loading " << file << "...\n";
    buildingImages.loadFromFile(file);

    // Split up the image into separate textures on your GPU
    int tileCount = (scenerySize * 16) / tileWidth;

    buildingTextures.resize(tileCount * tileCount);

    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            if (!buildingTextures[y * tileCount + x].loadFromImage(buildingImages,
                sf::IntRect(x * tileWidth, y * tileWidth,
                (x + 1) * tileWidth, (y + 1) * tileWidth)))
                    exit(103);
            buildingTextures[y * tileCount + x].setSmooth(false);
        }
    }
    std::cout << file << " loaded successfully!\n";
}

sf::Vector2i IsometricMap::getMapSizeInTiles() const
{
    return mapSizeInTiles;
}

sf::Vector2f IsometricMap::getMapSizeInPixels() const
{
    return mapSizeInPixels;
}

/*void IsometricMap::loadSceneryImages(const std::string file)
{
    std::cout << "Loading " << file << "...\n";
    sceneryImages.loadFromFile(file);

    // Split up the image into separate textures on your GPU
    int tileCount = 16;

    sceneryTextures.resize(tileCount * tileCount);

    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            if (!sceneryTextures[y * tileCount + x].loadFromImage(sceneryImages,
                sf::IntRect(x * scenerySize, y * scenerySize,
                scenerySize, scenerySize)))
                    exit(103);
            sceneryTextures[y * tileCount + x].setSmooth(false);
        }
    }
    std::cout << file << " loaded successfully!\n";
}
*/
void IsometricMap::loadFloorMap(const std::string file)
{
    std::cout << "Loading floor map\n";
    int tileCode = 0;
    std::ifstream in(file);
    in >> mapSizeInTiles.y >> mapSizeInTiles.x;

    mapSizeInPixels.x = mapSizeInTiles.x * tileWidth + (tileWidth / 2);
    mapSizeInPixels.y = mapSizeInTiles.y * tileHeight + (tileHeight / 2);

    std::cout << "Map width: " << mapSizeInTiles.x << std::endl;


    floorMap.resize(mapSizeInTiles.y);
    floors.resize(mapSizeInTiles.x);
std::cout << "Map height: " << mapSizeInTiles.y << std::endl;

    for(int i = 0; i < mapSizeInTiles.y; i++)
    {
        for(int j = 0; j < mapSizeInTiles.x; j++)
        {
            in >> tileCode;
            floorMap[i].push_back(tileCode);
            //std::cout << tileCode << " ";

            //Non collidable tiles occupy a specific range in the tileset, and collidable tiles occupy the other set.
            bool collidableTile = tileCode >= collidableIndex;
            floors[i].emplace_back(floorTextures[tileCode], mapToScreenCoords(sf::Vector2i(i, j)), collidableTile);



        }
        //std::cout << std::endl;
    }

    in.close();

    std::cout << "Loading floor map completed!\n";
}

void IsometricMap::loadObjectMap(const std::string file)
{
    sf::Texture tempTex;
    std::cout << "Loading object map\n";
    int tileCode = 0;
    std::ifstream in(file);
    in >> mapSizeInTiles.y >> mapSizeInTiles.x;

    //std::cout << "Map width: " << mapWidth << std::endl;

    //std::cout << "Map height: " << mapHeight << std::endl;

    objectMap.resize(mapSizeInPixels.y);
    objects.resize(mapSizeInTiles.x);

    for(int i = 0; i < mapSizeInTiles.y; i++)
    {

        for(int j = 0; j < mapSizeInTiles.x; j++)
        {
            in >> tileCode;
            objectMap[i].push_back(tileCode);
            //std::cout << tileCode << " ";

            objects[i].emplace_back(objectTextures[tileCode], mapToScreenCoords(sf::Vector2i(i, j)), true);

        }
        //std::cout << std::endl;
    }

    in.close();

    std::cout << "Loading object map completed!\n";
}

void IsometricMap::loadBuildingMap(const std::string file)
{
    sf::Texture tempTex;
    std::cout << "Loading building map\n";
    int tileCode = 0;
    std::ifstream in(file);
    in >> mapSizeInTiles.y >> mapSizeInTiles.x;

    //std::cout << "Map width: " << mapWidth << std::endl;

    //std::cout << "Map height: " << mapHeight << std::endl;

    buildingMap.resize(mapSizeInTiles.y);
    buildings.resize(mapSizeInTiles.x);

    for(int i = 0; i < mapSizeInTiles.y; i++)
    {

        for(int j = 0; j < mapSizeInTiles.x; j++)
        {
            in >> tileCode;
            buildingMap[i].push_back(tileCode);
            //std::cout << tileCode << " ";

            buildings[i].emplace_back(buildingTextures[tileCode], mapToScreenCoords(sf::Vector2i(i, j)), false);

        }
        // std::cout << std::endl;
    }
    in.close();

    std::cout << "Loading building map completed!\n";
}



/*
    Improve function by only drawing visible tiles.
    Also add depth sorting
*/
sf::Vector2i IsometricMap::screenToMapCoords(sf::Vector2f screenCoords)
{
    isoConversions.screenToMapCoords(screenCoords);
}

sf::Vector2f IsometricMap::mapToScreenCoords(sf::Vector2i mapCoords)
{
    isoConversions.mapToScreenCoords(mapCoords);
}

//Find it by position
bool IsometricMap::isOnCollidableTile(sf::Vector2f pos)
{
    sf::Vector2i tileCoords = screenToMapCoords(pos);

    return isOnCollidableTile(tileCoords);
}

//Find it by map coordinates
bool IsometricMap::isOnCollidableTile(sf::Vector2i tile)
{
    bool collidable = false;

    //Check collidable floors
    if(tile.x >= 0 && tile.y >= 0 && tile.x < floorMap.size() && tile.y < floorMap[tile.x].size())
    {
        if(floorMap[tile.x][tile.y] >= collidableIndex)
        {
            collidable = true;
       //     std::cout << "Collidable\n";
        }
    }

    //Check buildings
    //If already on a collidable floor, no reason to check this
    if(!collidable && tile.x >= 0 && tile.y >= 0 && tile.x < buildingMap.size() && tile.y < buildingMap[tile.x].size())
    {
        if(buildingMap[tile.x][tile.y] >= 0)
            collidable = true;
    }

    return collidable;

}

void IsometricMap::draw(sf::RenderWindow& window)
{

    sf::View view = window.getView();

    sf::Vector2f viewSize(view.getSize());
    sf::Vector2f viewCenter(view.getCenter());
    sf::FloatRect viewRect(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2, viewSize.x, viewSize.y);


    int startX = floor(viewRect.left / tileWidth) - 2;
    int startY = floor(viewRect.top / (tileHeight / 2)) - 2;

    //Use the screen position to locate the floorMap coordinates
   // std::map<sf::Vector2f, sf::Vector2f>::iterator iter;
   // iter = floorCoords.upper_bound(sf::Vector2f(viewRect.left, viewRect.top));
   // sf::Vector2f startCoords = iter->second;

//    std::cout << "Start X: " << startCoords.x << std::endl;
    //std::cout << "Start Y: " << startCoords.y << std::endl;

    int endX = ceil((viewRect.left + viewRect.width) / tileWidth) + 2;
    int endY = ceil((viewRect.top + viewRect.height) / (tileHeight / 2)) + 2;

    //iter = floorCoords.lower_bound(sf::Vector2f(viewRect.left + viewRect.width, viewRect.top + viewRect.height));
    //sf::Vector2f endCoords = iter->second;

    //std::cout << "End X: " << endCoords.x << std::endl;
    //std::cout << "End Y: " << eCoords.y << std::endl;


    if(startX < 0)
        startX = 0;
    if(startY < 0)
        startY = 0;
    if(endX >= floors.front().size())
        endX = floors.front().size() - 1;
    if(endY >= floors.size())
        endY = floors.size() -1;


 /*   if(startCoords.x < 0)
        startCoords.x = 0;
    if(startCoords.y < 0)
        startCoords.y = 0;
    if(endCoords.x >= floors.front().size())
        endCoords.x = floors.front().size() - 1;
    if(endCoords.y >= floors.size())
        endCoords.y = floors.size() -1;

    //Draw floors
    for(int i = startCoords.y; i < endCoords.y; i++)
    {
        for(int j = startCoords.x; j < endCoords.x; j++)
        {
            window.draw(floors[i][j]);
        }
    }*/

    for(int i = startY; i < endY; i++)
    {
        for(int j = startX; j < endX; j++)
        {
            window.draw(floors[i][j]);
        }
    }

    //std::cout << "Buildings size: " << buildings.size() << std::endl;
    for(int i = 0; i < buildings.size(); i++)
    {
        for(int j = 0; j < buildings[i].size(); j++)
        {
            window.draw(buildings[i][j]);
        }
    }


}
