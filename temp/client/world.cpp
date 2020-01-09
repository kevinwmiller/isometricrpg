#include "IsometricMap.h"
#include <iostream>
#include <cmath>

std::vector<sf::Texture> IsometricMap::floorTextures;
std::vector<sf::Texture> IsometricMap::objectTextures;
std::vector<sf::Texture> IsometricMap::buildingTextures;

IsometricMap::IsometricMap(const std::string floorImgFile, const std::string objectImgFile, const std::string buildingImgFile)
{
    mapHeight = 0;
    mapWidth = 0;

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

    int tileCount = 1024 / tileWidth;

    floorTextures.resize(tileCount * tileCount);

    for (int y = 0; y < tileCount; y++)
    {
        for (int x = 0; x < tileCount; x++)
        {
            if (!floorTextures[y * tileCount + x].loadFromImage(floorImages,
                sf::IntRect(x * tileWidth, y * tileWidth,
                (x + 1) * tileWidth, (y + 1) * tileWidth)))
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
    int tileCount = 1024 / tileWidth;

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
    int tileCount = 1024 / tileWidth;

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

void IsometricMap::loadFloorMap(const std::string file)
{
    std::cout << "Loading floor map\n";
    int tileCode = 0;
    std::ifstream in(file);
    in >> mapWidth >> mapHeight;

    //std::cout << "Map width: " << mapWidth << std::endl;

    //std::cout << "Map height: " << mapHeight << std::endl;

    floorMap.resize(mapHeight);
    floors.resize(mapHeight);

    for(int i = 0; i < mapWidth; i++)
    {
        for(int j = 0; j < mapHeight; j++)
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
    in >> mapWidth >> mapHeight;

    //std::cout << "Map width: " << mapWidth << std::endl;

    //std::cout << "Map height: " << mapHeight << std::endl;

    objectMap.resize(mapHeight);
    objects.resize(mapHeight);

    for(int i = 0; i < mapWidth; i++)
    {

        for(int j = 0; j < mapHeight; j++)
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
    in >> mapWidth >> mapHeight;

    //std::cout << "Map width: " << mapWidth << std::endl;

    //std::cout << "Map height: " << mapHeight << std::endl;

    buildingMap.resize(mapHeight);
    buildings.resize(mapHeight);

    for(int i = 0; i < mapWidth; i++)
    {

        for(int j = 0; j < mapHeight; j++)
        {
            in >> tileCode;
            buildingMap[i].push_back(tileCode);
            //std::cout << tileCode << " ";

            buildings[i].emplace_back(buildingTextures[tileCode], mapToScreenCoords(sf::Vector2i(i, j)), true);

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
    //Determine rectangle
    int i = screenCoords.y / (tileHeight / 2);
    int halfTileHeight = tileHeight / 2;
    int halfTileWidth = tileWidth / 2;
    int j = 0;
    int upperLeftB = 0;
    int upperRightB = 0;
    int bottomLeftB = 0;
    int bottomRightB = 0;
    sf::Vector2f tileCoords;

    //If i is odd
    if(i % 2 != 0)
        j = screenCoords.x / tileWidth;
    else
        j = (screenCoords.x - (tileWidth / 2)) / tileWidth;

    //Tiles width is twice the length of its height.
    //Positive slope is 1/2, negative slow is -1/2
    //Find the formula for the hypotenuse of the triangle formed at the corners
    //The formula of a line is y = mx + b. Y and X are points on the line and b is the y-intercept.
    //b = y - mx where m is the slope of the line.
    //To find the corner, check where the y value of the screen coords is in relation to the y value of the line
    tileCoords = mapToScreenCoords(sf::Vector2i(i, j));

    upperLeftB = (tileCoords.y - (1 / 2) * (tileCoords.x + halfTileWidth));
    upperRightB = (tileCoords.y - (-1 / 2) * (tileCoords.x + halfTileWidth));
    bottomLeftB = (tileCoords.y + halfTileHeight - (-1 / 2) * tileCoords.x);
    bottomRightB = ((tileCoords.y + tileHeight) -  (1 / 2 ) * (tileCoords.x + halfTileWidth));

    //Determine quadrant.
    //If in upper left corner, the map coords are (i, j - 1)
    //If in upper right corner, the map coords are (i + 1, j - 1)
    //If in bottom left corner, the map coords are (i, j + 1)
    //If in bottom right corner, the map coords are (i + 1, j + 1)
    //If in tht middle, the map coords are (i, j)

 /*   //If in top left
    if(screenCoords.x < tileCoords.x + halfTileWidth && screenCoords.y < (1 / 2) * screenCoords.x + upperLeftB)
    {
        j -= 1;
        std::cout << "Upper left\n";
    }
    //Bottom left
    else if(screenCoords.x < tileCoords.x + halfTileWidth && screenCoords.y >  (-1 / 2) * screenCoords.x + bottomLeftB)
    {
        j += 1;
        std::cout << "Bottom left\n";
    }
    //Top Right
    else if(screenCoords.x > tileCoords.x + halfTileWidth && screenCoords.y < (-1 / 2) * screenCoords.x + upperRightB)
    {
        i += 1;
        j -= 1;
        std::cout << "Upper right\n";
    }
    //Bottom Right
    else if(screenCoords.x > tileCoords.x + halfTileWidth && screenCoords.y > (1 / 2) * screenCoords.x + bottomRightB)
    {
        i += 1;
        j += 1;
        std::cout << "Bottom Right\n";
    }*/
    //y = m(x - x1) + y1 where x1 and y1 are points on the line

    if(screenCoords.x < tileCoords.x + halfTileWidth && screenCoords.y < (1 / 2) * (screenCoords.x - tileCoords.x) + (tileCoords.y + halfTileHeight))
    {
        i -= 1;
        std::cout << "Upper left\n";
    }
    //Bottom left
    else if(screenCoords.x < tileCoords.x + halfTileWidth && screenCoords.y >  (-1 / 2) * (screenCoords.x - tileCoords.x) + (tileCoords.y + halfTileHeight))
    {
        i += 1;
        std::cout << "Bottom left\n";
    }
    //Top Right
    else if(screenCoords.x > tileCoords.x + halfTileWidth && screenCoords.y < (-1 / 2) * (screenCoords.x - (tileCoords.x + tileWidth) ) + (tileCoords.y + halfTileHeight))
    {
        i -= 1;
        j += 1;
        std::cout << "Upper right\n";
    }
    //Bottom Right
    else if(screenCoords.x > tileCoords.x + halfTileWidth && screenCoords.y > (1 / 2) * (screenCoords.x - (tileCoords.x + tileWidth) ) + (tileCoords.y + halfTileHeight))
    {
        i += 1;
        j += 1;
        std::cout << "Bottom Right\n";
    }
    //Otherwise the coordinates are in the middle and the map coords are (i, j)
    return sf::Vector2i(i, j);
}

sf::Vector2f IsometricMap::mapToScreenCoords(sf::Vector2i mapCoords)
{
    //Map coords should be in the form (row, column);
    float screenYPos = mapCoords.x * (tileHeight / 2);
    float screenXPos = 0;

    if(mapCoords.x % 2 != 0)
        screenXPos = mapCoords.y * tileWidth + (tileWidth / 2);
    else
        screenXPos = mapCoords.y * tileWidth;

    return sf::Vector2f(screenXPos, screenYPos);
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
