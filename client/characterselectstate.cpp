#include "characterselectstate.h"

const std::string createdNamesFile = "saves/CharacterNames.txt";
CharacterSelectState::CharacterSelectState(ResourceManager& resources) : State(resources)
{
    characterFile = "saves/";
    action.setAction(States::stateCodes::Continue);
}

CharacterSelectState::~CharacterSelectState()
{
    //dtor
}

void CharacterSelectState::prepareState(std::string args)
{
    std::cout << "Preparing CharacterSelectState\n";
    menu.setUpMenu("resources/images/backgrounds/MenuBackground.jpg",
                   sf::Color(25, 25, 25, 255), 18,
                   sf::Vector2f(resources.window.getSize().x / 2.05, resources.window.getSize().y / 2.02),
                   resources.window,
                   resources.fontNormal,
                   "resources/images/gui/ButtonTemplate.png");

    availableCharacters.setupList(resources.window, sf::FloatRect(0 , 0, .5, .5), resources.fontBold, 20, true, true, "resources/images/gui/parchment.png");
   // characterStats.setupList(resources.window, sf::FloatRect(.7, .03, .3, .4), resources.fontBold, 14, false, true, "resources/images/gui/parchment.png");
   loadCharacterNames();

    menu.addMenuButton("Load Character", sf::Vector2f(resources.window.getSize().x / 2.2, resources.window.getSize().y / 1.05));
    menu.addMenuButton("Previous Screen", sf::Vector2f(5, resources.window.getSize().y / 1.05));

    std::cout << "Finished Preparing CharacterSelectState!\n";
}

void CharacterSelectState::cleanUp()
{
    std::cout << "Cleaning up CharacterSelectState\n";
    menu.clearButtons();
    availableCharacters.clearList();
    characterNames.clear();
}

StateAction CharacterSelectState::handleEvents()
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
                currentCharacter = availableCharacters.handleMouseClicked(event, resources.window);

                break;

            case sf::Event::MouseButtonReleased:
                processChoice(menu.handleMouseReleased(event, resources.window));
                break;
            case sf::Event::MouseWheelMoved:
                availableCharacters.handleScrolling(event, resources.window);

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

void CharacterSelectState::update()
{
    menu.updateMenu();
}

void CharacterSelectState::processChoice(int choice)
{
    if(choice == 1)
    {
        if(currentCharacter != "")
        {

            characterFile = "saves/" + currentCharacter + ".txt";
            setAction(States::stateCodes::SinglePlayer, characterFile);
        }
        else
        {
            std::string errorString;
            if(characterNames.size() > 0)
                errorString = "Please choose a character";
            else
                errorString = "No availiable characters. Please create one.";
            menu.setErrorTextString(errorString);
            menu.setErrorTextPosition(sf::Vector2f(resources.window.getSize().x /2, resources.window.getSize().y / 2), true);
        }
    }

    else if(choice == 2)
        setAction(States::stateCodes::MainMenu);
}

void CharacterSelectState::loadCharacterNames()
{
    std::ifstream in;
    in.open(createdNamesFile);

    if(in.is_open())
    {
        while(!in.eof())
        {
            std::string name;
            in >> name;
            if(name != "")
            {
                characterNames.push_back(name);
                availableCharacters.addItemWithHiddenText(name, name, sf::Color::Black);
            }
        }
        if(characterNames.size() <= 0)
        {
            std::string errorString = "No availiable characters. Please create one.";
            menu.setErrorTextString(errorString);
            menu.setErrorTextPosition(sf::Vector2f(resources.window.getSize().x /2, resources.window.getSize().y / 2), true);
        }
    }
    else
    {
        std::cout << "Could not open character names file.\n";
    }
}

void CharacterSelectState::draw()
{
    resources.window.clear();

    resources.window.draw(menu);
    resources.window.draw(availableCharacters);
    //resources.window.draw(characterStats);

    resources.window.display();
}


