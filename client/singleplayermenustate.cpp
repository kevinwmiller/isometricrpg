#include "singleplayermenustate.h"

SinglePlayerMenuState::SinglePlayerMenuState(ResourceManager& resources) : State(resources)
{
    setAction(States::stateCodes::Continue);
}

SinglePlayerMenuState::~SinglePlayerMenuState()
{
    std::cout << "Destroying SinglePlayerMenuState\n";
    menu.clearButtons();
}

void SinglePlayerMenuState::prepareState(std::string args)
{
    std::cout << "Preparing SingleplayerMenuState\n";
    menu.setUpMenu("resources/images/backgrounds/MenuBackground.jpg",
                   sf::Color(25, 25, 25, 255), 18,
                   sf::Vector2f(resources.window.getSize().x / 2 - 64, resources.window.getSize().y / 2 - 16),
                   resources.window,
                   resources.fontNormal,
                   "resources/images/gui/ButtonTemplate.png");

    menu.addMenuButton("Create Character");
    menu.addMenuButton("Select Character");
    menu.addMenuButton("Previous Screen");
}

void SinglePlayerMenuState::cleanUp()
{
    std::cout << "Cleaning up SingleplayerMenuState\n";
    menu.clearButtons();
}

StateAction SinglePlayerMenuState::handleEvents()
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
                    processChoice(menu.handleKeyPressed(event, resources.window));
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

void SinglePlayerMenuState::update()
{
    menu.updateMenu();
}

void SinglePlayerMenuState::draw()
{
    resources.window.clear();

    resources.window.draw(menu);

    resources.window.display();
}

void SinglePlayerMenuState::processChoice(int choice)
{
    if(choice == 1)
        setAction(States::stateCodes::CharacterCreate);

    else if(choice == 2)
        setAction(States::stateCodes::CharacterSelect);

    else if(choice == 3)

        setAction(States::stateCodes::MainMenu);

}
