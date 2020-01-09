#include "charactercreatestate.h"
std::string createdNamesFile = "saves/CharacterNames.txt";
std::string saveDestination = "saves/";

CharacterCreateState::CharacterCreateState(ResourceManager& resources) : State(resources)
{
    action.setAction(States::stateCodes::Continue);
}

CharacterCreateState::~CharacterCreateState()
{
    //dtor
}

void CharacterCreateState::prepareState(std::string args)
{

    std::cout << "Preparing CreateCharacterState\n";
    loadCharacterNames(createdNamesFile);

    currentClass = -1;

    warriorDesc = "Warrior: A strong melee fighter with high defenses and health. Has the ability to go into a rage for a short time to increase damage done and reduce all incoming damage by a significant amount.";
    rangerDesc = "Ranger: A fast long ranged attacker who is a master with a bow. Has the ability to increase speed for a short time.";
    thiefDesc = "Thief: A melee fighter who specializes in moving quickly around the battlefield while attacking his oppenent. Has the ability to turn invisible for a short time.";
    mageDesc = "Mage: A magic user who is a master of the elements. Has the ability to teleport to a targeted location within sight of the player.";
    palaDesc = "Paladin: A warrior who uses holy attacks to strike down his oppenents. Has the ability to use auras to enhance his skills.";
    necroDesc = "Necromancer: A magic user who specializes in the undead. Has the ability to summon minions to fight by his side.";

    classStats.resize(CharacterData::ClassType::TotalClasses);

    classStats[CharacterData::ClassType::Warrior].setUpCharacter    ("", 25, 10, 10, 75, 80, 50, 4, 250, 1, CharacterData::ClassType::Warrior);
    classStats[CharacterData::ClassType::Ranger].setUpCharacter     ("", 15, 25, 10, 60, 60, 50, 4, 275, 1, CharacterData::ClassType::Ranger);
    classStats[CharacterData::ClassType::Thief].setUpCharacter      ("", 15, 25, 10, 60, 65, 50, 4, 280, 1, CharacterData::ClassType::Thief);
    classStats[CharacterData::ClassType::Mage].setUpCharacter       ("", 10, 10, 25, 50, 50, 80, 4, 250, 1, CharacterData::ClassType::Mage);
    classStats[CharacterData::ClassType::Paladin].setUpCharacter    ("", 20, 10, 15, 75, 70, 70, 5, 260, 1, CharacterData::ClassType::Paladin);
    classStats[CharacterData::ClassType::Necromancer].setUpCharacter("", 10, 10, 25, 60, 55, 75, 4, 250, 1, CharacterData::ClassType::Necromancer);

    classButtons.resize(7);
    menu.setUpMenu("resources/images/backgrounds/MenuBackground.jpg",
                   sf::Color(25, 25, 25, 255), 16,
                   sf::Vector2f(resources.window.getSize().x / 1.5, resources.window.getSize().y / 2),
                   resources.window,
                   resources.fontBold,
                   "resources/images/gui/ButtonTemplate.png");

    menu.setErrorTextPosition(sf::Vector2f(resources.window.getSize().x /4, resources.window.getSize().y / 1.05), true);

    menu.addMenuButton("Warrior  ", sf::Vector2f(resources.window.getSize().x / 10, resources.window.getSize().y / 2), true, 18);
    menu.addMenuButton("Ranger  ", sf::Vector2f(resources.window.getSize().x / 5, resources.window.getSize().y / 2), true, 18);
    menu.addMenuButton("Thief  ", sf::Vector2f(resources.window.getSize().x / 3.45, resources.window.getSize().y / 2), true, 18);
    menu.addMenuButton("Mage  ", sf::Vector2f(resources.window.getSize().x / 2.7, resources.window.getSize().y / 2), true, 18);
    menu.addMenuButton("Paladin  ", sf::Vector2f(resources.window.getSize().x / 10, resources.window.getSize().y / 1.5), true, 18);
    menu.addMenuButton("Necromancer  ", sf::Vector2f(resources.window.getSize().x / 5, resources.window.getSize().y / 1.5), true, 18);

    menu.addMenuButton("Previous Screen", sf::Vector2f(2, resources.window.getSize().y / 1.053));
    menu.addMenuButton("Create Character", sf::Vector2f(resources.window.getSize().x / 1.75, resources.window.getSize().y / 1.053));
    nameBox.setUp(14, resources.fontBold, resources.window.getSize().x / 2 - resources.window.getSize().x / 16, resources.window.getSize().y / 1.053, resources.window.getSize().x / 8, false);
    menu.createLabel("Name: ", sf::Vector2f(resources.window.getSize().x / 2.6, resources.window.getSize().y / 1.058));
    startingStats.setupList(resources.window, sf::FloatRect(.7, .3, .3, .4), resources.fontBold, 14, false, true, "resources/images/gui/parchment.png");
    descriptionBox.setupList(resources.window, sf::FloatRect(.7 , .77, .3, .20), resources.fontBold, 14, false, true, "resources/images/gui/parchment.png");
    //descriptionBox.addTextItem("Class: Warrior\nDescription:", sf::Color::Black);

}


void CharacterCreateState::cleanUp()
{
    std::cout << "Cleaning up CreateCharacterState\n";
    menu.clearButtons();
    startingStats.clearList();
    descriptionBox.clearList();
    classButtons.clear();
    nameBox.clear();
}

StateAction CharacterCreateState::handleEvents()
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
            case sf::Event::MouseWheelMoved:
                startingStats.handleScrolling(event, resources.window);
                descriptionBox.handleScrolling(event, resources.window);
                break;

            case sf::Event::MouseButtonPressed:
                menu.handleMousePressed(event, resources.window);
                nameBox.handleMouseClicked(event, resources.window);
                break;

            case sf::Event::MouseButtonReleased:
                processChoice(menu.handleMouseReleased(event, resources.window));
                break;

            //Allow user to make selections with the keyboard. Enter makes a selection
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape:
                        setAction(States::stateCodes::SingleplayerMenu);
                        break;
                    case sf::Keyboard::Return:
                        processChoice(menu.handleKeyPressed(event, resources.window));
                        break;
                    default:
                        menu.handleKeyPressed(event, resources.window);
                        break;

                }
                nameBox.processInput(event.key.code);
                break;
            case sf::Event::TextEntered:
                if(nameBox.isActive())
                    nameBox.processTextEntered(event.text.unicode);
                break;

            case sf::Event::Resized:
                menu.handleResize(event, resources.window);
                break;

            default:
                break;
        }
    }
    nameBox.updateCursor();
    return getAction();
}


void CharacterCreateState::update()
{
    menu.updateMenu();
}

void CharacterCreateState::draw()
{
    resources.window.clear();

    resources.window.draw(menu);
    resources.window.draw(nameBox);
    resources.window.draw(startingStats);
    resources.window.draw(descriptionBox);

    resources.window.display();
}

void CharacterCreateState::loadCharacterNames(const std::string& file)
{
    std::ifstream in;
    in.open(file);

    if(in.is_open())
    {
        while(!in.eof())
        {
            std::string name;
            in >> name;
            createdCharacterNames.push_back(name);
        }
        in.close();
    }
    else
    {
        std::cout << "Could not open " << file <<". Exiting program.\n";
        exit(300);
    }
}

void CharacterCreateState::fixNameFormat(std::string& name)
{
    int i = 1;
    //Remove spaces from beginning and end of string by finding the beginning non space character and last non space character,
    //then creating a sub string in that range
    int beg = name.find_first_not_of(' ');
    int end = name.find_last_not_of(' ');
    name = name.substr(beg, end + 1);

    //Capitalize first letter of the name
    name[0] = toupper(name[0]);

    //lowercase for all other letters
    while(i < name.size())
    {
        name[i] = tolower(name[i]);
        i++;
    }

    std::cout << name << std::endl;

}

bool CharacterCreateState::checkForExistingName(const std::string& name)
{
    bool found = false;
    int i = 0;
    while(i < createdCharacterNames.size() && !found)
    {
        if(createdCharacterNames[i] == name)
            found = true;
        i++;
    }
    return found;
}

void CharacterCreateState::processChoice(int choice)
{
    if(choice == CharacterData::ClassType::Warrior)
    {
        currentClass = CharacterData::ClassType::Warrior;
        startingStats.clearList();
        descriptionBox.clearList();
        startingStats.addTextItem(classStats[CharacterData::ClassType::Warrior].getStatsAsString(), sf::Color::Black);
        descriptionBox.addTextItem(warriorDesc, sf::Color::Black);
    }
    else if(choice == CharacterData::ClassType::Ranger)
    {
        currentClass = CharacterData::ClassType::Ranger;
        startingStats.clearList();
        descriptionBox.clearList();
        startingStats.addTextItem(classStats[CharacterData::ClassType::Ranger].getStatsAsString(), sf::Color::Black);
        descriptionBox.addTextItem(rangerDesc, sf::Color::Black);
    }
    else if(choice == CharacterData::ClassType::Thief)
    {
        currentClass = CharacterData::ClassType::Thief;
        startingStats.clearList();
        descriptionBox.clearList();
        startingStats.addTextItem(classStats[CharacterData::ClassType::Thief].getStatsAsString(), sf::Color::Black);
        descriptionBox.addTextItem(thiefDesc, sf::Color::Black);
    }
    else if(choice == CharacterData::ClassType::Mage)
    {
        currentClass = CharacterData::ClassType::Mage;
        startingStats.clearList();
        descriptionBox.clearList();
        startingStats.addTextItem(classStats[CharacterData::ClassType::Mage].getStatsAsString(), sf::Color::Black);
        descriptionBox.addTextItem(mageDesc, sf::Color::Black);
    }
    else if(choice == CharacterData::ClassType::Paladin)
    {
        currentClass = CharacterData::ClassType::Paladin;
        startingStats.clearList();
        descriptionBox.clearList();
        startingStats.addTextItem(classStats[CharacterData::ClassType::Paladin].getStatsAsString(), sf::Color::Black);
        descriptionBox.addTextItem(palaDesc, sf::Color::Black);
    }
    else if(choice == CharacterData::ClassType::Necromancer)
    {
        currentClass = CharacterData::ClassType::Necromancer;
        startingStats.clearList();
        descriptionBox.clearList();
        startingStats.addTextItem(classStats[CharacterData::ClassType::Necromancer].getStatsAsString(), sf::Color::Black);
        descriptionBox.addTextItem(necroDesc, sf::Color::Black);
    }

    else if(choice == 7)
        setAction(States::stateCodes::SingleplayerMenu);

    else if(choice == 8)
    {
        //If there is a name entered and a class chosen
        if(!nameBox.isEmpty() && !checkForExistingName(nameBox.getString()) && currentClass != -1)
        {

            std::ofstream out;
            out.open(createdNamesFile, ios::app);
            //Fix the name format, save the character and start the game
            menu.setErrorTextString("");
            characterName = nameBox.getString();
            fixNameFormat(characterName);

            //Add the character name to the created characters list to avoid creating multipel characters with the same name.
            if(out.is_open())
            {
                out << characterName << "\n";
                out.close();

                classStats[currentClass].setName(characterName);
                std::string characterFile = saveDestination + characterName + ".txt";
                std::cout << "Character File: " << characterFile << std::endl;
                classStats[currentClass].saveCharacterData(characterFile);

                setAction(States::stateCodes::SinglePlayer, characterFile);
                characterName.clear();
                characterFile.clear();
            }
            else
                std::cout << "Warning: Could not add character name to character names file. Creating another character with the same name will overwrite save.\n";

        }
        else
        {
            std::string errorString("");
            if(nameBox.isEmpty())
                errorString += "Please enter a character name. ";
            if(currentClass == -1)
                errorString += "Please choose a class. ";
            if(checkForExistingName(nameBox.getString()))
                errorString += "Character name already exists. ";

            menu.setErrorTextString(errorString);
            menu.setErrorTextPosition(sf::Vector2f(resources.window.getSize().x /2, 5), true);
        }
    }

        //setAction(States::stateCodes::ExitGame);
}
