#include <iostream>
#include "mainmenustate.h"


MainMenuState::MainMenuState(ResourceManager& resources): State(resources)
{

    setAction(States::stateCodes::Continue);
}

MainMenuState::~MainMenuState()
{
    std::cout << "Destroying MainMenuState\n";
    menu.clearButtons();
}

void MainMenuState::prepareState(std::string)
{
    std::cout << "Preparing MainMenuState\n";
    menu.setUpMenu("resources/images/backgrounds/MenuBackground.jpg",
                   sf::Color(25, 25, 25, 255), 18,
                   sf::Vector2f(resources.window.getSize().x / 2.05, resources.window.getSize().y / 2.02),
                   resources.window,
                   resources.fontNormal,
                   "resources/images/gui/ButtonTemplate.png");

    menu.createLabel(resources.version, sf::Vector2f(5, resources.window.getSize().y / 1.05));
    menu.addMenuButton("Singleplayer");
    menu.addMenuButton("Multiplayer");
    menu.addMenuButton("Exit Game", sf::Vector2f(resources.window.getSize().x / 1.1, resources.window.getSize().y / 1.05));

    std::cout << "Finished Preparing MainMenuState!\n";

}

void MainMenuState::cleanUp()
{
    std::cout << "Cleaning up MainMenuState\n";
    menu.clearButtons();
}

StateAction MainMenuState::handleEvents()
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

            case sf::Event::MouseMoved:
                menu.handleMouseMovement(event, resources.window);
                break;

            case sf::Event::MouseButtonPressed:
                menu.handleMousePressed(event, resources.window);
                break;

            case sf::Event::MouseButtonReleased:
                processChoice(menu.handleMouseReleased(event, resources.window));
                break;

            //Allow user to make selections with the keyboard. Enter makes a selection
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    setAction(States::stateCodes::ExitGame);
                else
                    menu.handleKeyPressed(event, resources.window);
                break;
            case sf::Event::KeyReleased:
                break;

            case sf::Event::Resized:
                menu.handleResize(event, resources.window);
                break;

            default:
                break;
        }
    }

    return getAction();
}

void MainMenuState::update()
{
    menu.updateMenu();
}

void MainMenuState::processChoice(int choice)
{

   /* if(choice == 1)
        setAction(States::stateCodes::SinglePlayer);*/

    if(choice == 1)
        setAction(States::stateCodes::SingleplayerMenu);

    else if(choice == 2)

       setAction(States::stateCodes::ExitGame);

    else if(choice == 3)
        setAction(States::stateCodes::ExitGame);
}

void MainMenuState::draw()
{
    resources.window.clear();

    resources.window.draw(menu);

    resources.window.display();
}
