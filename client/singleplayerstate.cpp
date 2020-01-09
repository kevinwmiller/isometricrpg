#include "singleplayerstate.h"
#include <iostream>
#include <sstream>

const std::string floorImgFile = "resources/images/tiles/floors.png";
const std::string objectImgFile = "unused";
const std::string buildingImgFile = "resources/images/tiles/buildings.png";
const std::string sceneryImgFile = "resources/images/StaticEntities/scenery.png";

const std::string floorMapFile = "resources/maps/testMap.txt";
const std::string buildingMapFile = "resources/maps/testBuildingMap.txt";
const std::string sceneryMapFile = "resources/maps/testSceneryMap.txt";

SinglePlayerState::SinglePlayerState(ResourceManager& resources) : State(resources), gameMap(floorImgFile, objectImgFile, buildingImgFile)
{

   std::cout << "Creating SinglePlayerState\n";

   Player::loadAnimations();
   Wolf::loadAnimations();
   Scenery::loadTextures(sceneryImgFile);
   gameView.reset(sf::FloatRect(resources.window.getPosition().x, resources.window.getPosition().y, resources.window.getSize().x, resources.window.getSize().y));
   gameView.zoom(0.9);
   zoomedOut = false;
   setAction(States::stateCodes::Continue);
}

SinglePlayerState::~SinglePlayerState()
{
    //dtor
}

void SinglePlayerState::prepareState(std::string args)
{
    std::cout << "Preparing SinglePlayerState\n";

    cursor = new MouseCursor;
    player = new Player;
    std::cout << "Added Entities\n";
    playerSaveFile = args;
    hasFocus = true;
    gameMap.loadFloorMap(floorMapFile);
    gameMap.loadBuildingMap(buildingMapFile);




    player->loadCharacterData(playerSaveFile);
    gameView.setCenter(player->getEntityOrigin());

    hud.setUp(resources, player);
    elapsedTime = clock.restart().asSeconds();
//    entityList.addEntity(&player);

    Entity* cursorPtr = cursor;
    entityList.addEntity(cursorPtr);

    Entity* playerPtr = player;

    entityList.addEntity(playerPtr);



    loadSceneryMap(sceneryMapFile);

  /*  for(int i = 0; i < 5; i++)
    {
        Entity* wolf = new Wolf;
        entityList.addEntity(wolf);

    }*/

    std::cout << "SinglePlayerState Prepared!\n";
}

void SinglePlayerState::cleanUp()
{
    std::cout << "Cleaning up SinglePlayerState\n";
    player->saveCharacterData(playerSaveFile);

    entityList.cleanUp();

}

StateAction SinglePlayerState::handleEvents()
{

    setAction(States::stateCodes::Continue);

    sf::Event event;
    while (resources.window.pollEvent(event))
    {

        switch (event.type)
        {
            case sf::Event::Closed:
                setAction(States::stateCodes::ExitGame);
                break;
            case sf::Event::LostFocus:
                hasFocus = false;
                break;

            case sf::Event::GainedFocus:
                hasFocus = true;
                break;

            case sf::Event::MouseMoved:
                hud.handleMouseMoved(event, resources.window);
                break;

            case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                    }
                break;

            case sf::Event::MouseButtonReleased:
                break;

            //Allow user to make selections with the keyboard. Enter makes a selection
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                    //Eventually make this bring up pause menu
                    case sf::Keyboard::Escape:
                        setAction(States::stateCodes::MainMenu);
                        break;
                    case sf::Keyboard::F1:
                        takeScreenShot();
                        break;
                    case sf::Keyboard::Key::R:
                        player->toggleRunning();
                        break;
                    case sf::Keyboard::Key::M:
                        toggleZoomedOut();
                        break;
                    case sf::Keyboard::Key::F2:
                        player->toggleBoundingBox();
                        break;
                    case sf::Keyboard::Key::PageUp:
                        {

                        }
                        break;

                    case sf::Keyboard::Key::PageDown:
                        {

                        }
                        break;
                    default:
                        break;

                }

                break;

            case sf::Event::Resized:

                break;

            default:
                break;
        }
    }

    if(hasFocus)
        handleInput();

    return getAction();
}

void SinglePlayerState::toggleZoomedOut()
{
    zoomedOut = !zoomedOut;

    if(zoomedOut)
        gameView.zoom(4);
    else
        gameView.zoom(.25);
}

void SinglePlayerState::handleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
       gameView.move(0, -15);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
       gameView.move(0, 15);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
       gameView.move(-15, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
       gameView.move(15, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            //std::cout << "Attack\n";
            player->attack(resources.window.mapPixelToCoords(sf::Mouse::getPosition(resources.window)));
        }
    }

    else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2f mouseCoords(resources.window.mapPixelToCoords(sf::Mouse::getPosition(resources.window)));
        //std::cout << "Move\n";
        player->moveTo(mouseCoords);
    }
}

void SinglePlayerState::update()
{

    cursor->updateCursorPosition(resources.window, gameView);
    entityList.updateEntities(elapsedTime, &gameMap);
    hud.update(player);
    gameView.setCenter(player->getEntityOrigin());

}

void SinglePlayerState::takeScreenShot()
{
    std::cout << "Taking screenshot\n";
    //Get the current system time.
    time_t currTime = time(0);
    std::string fileName = "resources/screenshots/";
    std::stringstream ss;
    ss << currTime;

    //Add the time.png to the end of the file name and save it.
    fileName += ss.str() + ".png";
    sf::Image scrShot = resources.window.capture();
    scrShot.saveToFile(fileName);

}

void SinglePlayerState::loadSceneryMap(const std::string file)
{
    int scenerySize = 128;
    sf::Texture tempTex;
    std::cout << "Loading scenery map\n";
    int mapWidth = 0;
    int mapHeight = 0;

    int tileCode = 0;
    std::ifstream in(file);
    in >> mapWidth >> mapHeight;

    std::cout << "Map width: " << mapWidth << std::endl;

    std::cout << "Map height: " << mapHeight << std::endl;

    sceneryMap.resize(mapHeight);

    for(int i = 0; i < mapHeight; i++)
    {

        for(int j = 0; j < mapWidth; j++)
        {
            in >> tileCode;
            sceneryMap[i].push_back(tileCode);
            //std::cout << tileCode << " ";
            if(tileCode >= 0)
            {
          //      std::cout << "Tile Code " << tileCode << std::endl;

                sf::Vector2f sceneryCoords = isoConversions.mapToScreenCoords(sf::Vector2i(i, j));
                //sceneryCoords.x -= (scenerySize - 128);
                sceneryCoords.y -= (scenerySize - 60);
                Entity* scenery = new Scenery(tileCode, sf::Vector3f(sceneryCoords.x, sceneryCoords.y, 0));
                entityList.addEntity(scenery);

            }

        }
       //  std::cout << std::endl;
    }
    in.close();

    std::cout << "Loading scenery map completed!\n";
}


void SinglePlayerState::draw()
{
    resources.window.clear();
    resources.window.setView(gameView);

    gameMap.draw(resources.window);
    entityList.drawEntities(resources.window);

    hud.draw(resources.window);

    resources.window.setView(gameView);

    resources.window.display();

    elapsedTime = clock.restart().asSeconds();

}
