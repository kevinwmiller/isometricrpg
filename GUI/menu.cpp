// See the file COPYRIGHT.txt for authors and copyright information.
// See the file LICENSE.txt for copying conditions.

#include <sstream>
#include "menu.h"

Menu::Menu()
{

}


Menu::~Menu()
{
    clearButtons();
}

void Menu::setUpMenu(const std::string& backgroundFile, sf::Color buttonSelectColor, short fontSize, sf::Vector2f topButtonPosition, sf::RenderWindow& window, sf::Font& menuFont, const std::string& buttonTextureFile)
{

    if(buttonTextureFile != "")
    {
        if(!buttonTextures.loadFromFile(buttonTextureFile))
           exit(200);

        buttonTexturesSet = true;
    }
    else
        buttonTexturesSet = false;

    font = &menuFont;

    windowSize.x = window.getSize().x;
    windowSize.y = window.getSize().y;
    menuView.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

    buttonWidthFactor = windowSize.x / topButtonPosition.x;
    buttonHeightFactor = windowSize.y / topButtonPosition.y;

    //Load background and font
    if (!bgTexture.loadFromFile(backgroundFile))
        exit(104);

    buttonFont = font;

    bgImageSize = bgTexture.getSize();

    bgTexture.setSmooth(true);
    bgSprite.setTexture(bgTexture);

    //Button settings
    buttonFontSize = fontSize;
    topButtonPos.x = topButtonPosition.x;
    topButtonPos.y = topButtonPosition.y;

    //Error Text
    errorText.setFont(*font);
    errorText.setCharacterSize(fontSize);
    errorText.setString("");
    errorText.setStyle(1);


    //scale take a factor amount so  newSize/oldSize.
    //Resize image to fit the window.  Move the origin because scaling the image moves it.
    bgSprite.setScale(windowSize.x / bgImageSize.x, windowSize.y / bgImageSize.y);
    bgSprite.setOrigin(0, 0);

    setButtonColors(buttonSelectColor);

    selection = 1;
    lastSelection = 1;
    selectionMade = false;

}

void Menu::setBackground(const std::string& backgroundFile)
{
     //Load background and font
    if (!bgTexture.loadFromFile(backgroundFile))
        exit(105);

    bgTexture.setSmooth(true);
    bgSprite.setTexture(bgTexture);
}

void Menu::setFont(const std::string& fontFile)
{
     if (!buttonFont->loadFromFile(fontFile))
        exit(305);
}

void Menu::setFontSize(short fontSize)
{
    buttonFontSize = fontSize;
}

void Menu::setErrorTextString(const std::string& str, sf::Color color)
{
    errorText.setString(str);
    errorText.setColor(color);
}

void Menu::setErrorTextPosition(sf::Vector2f pos, bool centeredOnPos)
{
    errorText.setPosition(pos);

    if(centeredOnPos)
    {
        errorText.setPosition(pos.x - errorText.getGlobalBounds().width / 2, pos.y + errorText.getGlobalBounds().height / 2);
    }
}


void Menu::setTopButtonLocation(sf::Vector2f topButtonPosition)
{
    topButtonPos.x = topButtonPosition.x;
    topButtonPos.y = topButtonPosition.y;
}

void Menu::setButtonColors(sf::Color pressedColor)
{

    //Will be the darkest
    buttonPressedColor = pressedColor;
    buttonUnselectedColor = pressedColor + sf::Color(25, 25, 25, 0);
    buttonSelectedColor = buttonUnselectedColor + sf::Color(25, 25, 25, 0);
}

void Menu::handleMouseMovement(sf::Event& event, sf::RenderWindow& window)
{
    unsigned int i = 0;
    if(!buttonTexturesSet)
    {
        while(menuOptions.size() >  i)
        {
            //First Menu Choice
            if(menuOptions[i]->rect.contains(event.mouseMove.x, event.mouseMove.y))
                selection = i + 1;
            i++;
        }
    }
    else
    {
        for(unsigned int i = 0; i < menuButtons.size(); i++)
        {
            menuButtons[i]->handleMouseMovement(event, window);
            if(menuButtons[i]->isHighlighted())
                selection = i + 1;
        }
    }
}

void Menu::handleMousePressed(sf::Event& event, sf::RenderWindow& window)
{
    unsigned int i = 0;
    if(!buttonTexturesSet)
    {
        while(i < menuOptions.size())
        {
            if(menuOptions[i]->rect.contains(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)
            {
                menuOptions[i]->buttonBackground.setFillColor(buttonPressedColor);
                menuOptions[i]->buttonBackground.setOutlineColor(sf::Color::Black);
            }
            i++;
        }
    }
    else
    {
        for(unsigned int i = 0; i < menuButtons.size(); i++)
        {
            menuButtons[i]->handleMousePressed(event, window);
        }
    }
}

int Menu::handleMouseReleased(sf::Event& event, sf::RenderWindow& window)
{
    unsigned int i = 0;
    if(!buttonTexturesSet)
    {
        while(i < menuOptions.size())
        {
            menuOptions[i]->buttonBackground.setOutlineColor(sf::Color::White);
            if(menuOptions[i]->rect.contains(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)
            {
                selection = i + 1;
                return selection;
            }
            i++;
        }
    }
    else
    {
        while(i < menuButtons.size())
        {
            if(menuButtons[i]->handleMouseReleased(event, window))
            {
                selection = i + 1;
               // std::cout << "Selection: " << selection << std::endl;
                if(menuButtons[selection - 1]->doesStayPressed())
                {
                    if(selection != lastSelection && menuButtons[lastSelection - 1]->isPressedDown())
                    {
                        //std::cout << "Releasing button: " << lastSelection << std::endl;
                        menuButtons[lastSelection - 1]->releaseButton();

                    }
                }
                lastSelection = selection;
                return selection;
            }
            i++;
        }
    }

    return 0;

}

int Menu::handleKeyPressed(sf::Event& event, sf::RenderWindow& window)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Return:
            return selection;
        break;

    case sf::Keyboard::Down:
        if(selection < (int)menuOptions.size())
            selection++;
        else
            selection = 1;
        break;

    case sf::Keyboard::Up:
        if(selection > 1)
            selection--;
        else
            selection = menuOptions.size();
        break;

    case sf::Keyboard::Key::F1:
    {
        std::cout << "Taking Screenshot\n";
        //Get the current system time.
        time_t currTime = time(0);
        std::string fileName = "resources/screenshots/";
        std::stringstream ss;
        ss << currTime;

        //Add the time.png to the end of the file name and save it.
        fileName += ss.str() + ".png";
        sf::Image scrShot = window.capture();
        scrShot.saveToFile(fileName);
        break;
    }

    default:
        break;
    }
    return 0;
}

void Menu::handleResize(sf::Event& event, sf::RenderWindow& window)
{
    sf::Vector2f windowSize;
    windowSize.x = window.getSize().x;
    windowSize.y = window.getSize().y;
    menuView.setSize(windowSize);
    //Resize the background image
    bgSprite.setScale(windowSize.x / bgImageSize.x, windowSize.y / bgImageSize.y);
    bgSprite.setOrigin(0, 0);


    //Adjust selection rectangles
    fixRectangles(float(event.size.width), event.size.height);
}

void Menu::updateMenu()
{
    if(!buttonTexturesSet)
    {
        for(int i = 0; i < (int)menuOptions.size(); i++)
        {
            if(selection == i + 1)
            {
                menuOptions[i]->buttonBackground.setFillColor(buttonSelectedColor);
            }
            else
                menuOptions[i]->buttonBackground.setFillColor(buttonUnselectedColor);
        }
    }
    else
    {
        for(int i = 0; i < (int)menuButtons.size(); i++)
        {
            menuButtons[i]->updateButton();
        }
    }

}

void Menu::clearButtons()
{
    if(menuOptions.size() > 0)
    {
        for(auto& menuItem: menuOptions)
            delete menuItem;
    }

    if(menuButtons.size() > 0)
    {
        for(auto& i: menuButtons)
            delete i;
    }

    labels.clear();

    //Make sure there is nothing in the vector.
    menuOptions.clear();
    menuButtons.clear();
}

/*
    Function to fix menu items when resizing occurs
*/
void Menu::fixRectangles(float width, float height)
{

    if(buttonWidthFactor != 0)
        topButtonPos.x = width / buttonWidthFactor;        //Smaller numbers puts text further to the right. Larger goes left.

    if(buttonHeightFactor != 0)
        topButtonPos.y = height / buttonHeightFactor;

    for(unsigned int i = 0; i < menuOptions.size(); i++)
    {
        //menuOptions[i]->buttonName.setOrigin(0,0);
        //menuOptions[i]->buttonName.setPosition(topButtonPos.x, topButtonPos.y + (i * (buttonFontSize + 75)));
        menuOptions[i]->rect.left = topButtonPos.x;
        menuOptions[i]->rect.top = topButtonPos.y + i * (buttonFontSize + buttonPadding);
    }

}

void Menu::addMenuButton(const std::string& itemName, bool sticky, short fontSize)
{

    if(fontSize < 0)
        fontSize = buttonFontSize;

    std::string tmpText(itemName);

    if(!buttonTexturesSet)
    {
        int i = menuOptions.size();
        MenuButton* menuItem = new MenuButton();

        menuItem->buttonName.setString(itemName);
        menuItem->buttonName.setCharacterSize(fontSize);
        menuItem->buttonName.setColor(sf::Color::White);
        menuItem->buttonName.setFont(*buttonFont);


        menuItem->rect.left = topButtonPos.x;
        menuItem->rect.top = topButtonPos.y + i * (fontSize + buttonPadding);       //Multiply (fontsize + 75) by however many menu options come before it.
        menuItem->rect.width = (tmpText.length() * fontSize / 1.5);            //Adjust rectangles width based on the text
        menuItem->rect.height = fontSize * 1.3;

        menuItem->buttonBackground.setPosition(menuItem->rect.left, menuItem->rect.top);
        menuItem->buttonBackground.setSize( sf::Vector2f(menuItem->rect.width, menuItem->rect.height));
        menuItem->buttonBackground.setFillColor(buttonUnselectedColor);
        menuItem->buttonBackground.setOutlineColor(sf::Color::White);
        menuItem->buttonBackground.setOutlineThickness(1);

        menuItem->buttonName.setPosition(topButtonPos.x + (menuItem->buttonBackground.getSize().x - menuItem->buttonName.getGlobalBounds().width) / 2, topButtonPos.y + i * (fontSize + buttonPadding));   //Extra pixels of space

        menuOptions.push_back(menuItem);
    }
    else
    {
        int i = menuButtons.size();
        Button* menuItem = new Button();
        //Button textures are set up in a way where the width can be stretched, but the height must line up with the actual textures
        menuItem->setUpButton(itemName, *buttonFont, fontSize, buttonTextures, sf::Vector2f(topButtonPos.x, topButtonPos.y + i * (fontSize + buttonPadding)), sf::Vector2f(tmpText.length() * (buttonFontSize / 1.5),fontSize * 1.7), sticky);
        //buttonTextures.getSize().x, buttonTextures.getSize().y / 3
        menuButtons.push_back(menuItem);
    }
}

void Menu::addMenuButton(const std::string& itemName, sf::Vector2f position, bool sticky, short fontSize)
{
    if(fontSize < 0)
        fontSize = buttonFontSize;

    std::string tmpText(itemName);
    if(!buttonTexturesSet)
    {


        MenuButton* menuItem = new MenuButton();

        menuItem->buttonName.setString(itemName);
        menuItem->buttonName.setCharacterSize(fontSize);
        menuItem->buttonName.setColor(sf::Color::White);
        menuItem->buttonName.setFont(*buttonFont);

        menuItem->rect.left = position.x;
        menuItem->rect.top = position.y;
        menuItem->rect.width = (tmpText.length() * fontSize / 1.5);            //Adjust rectangles width based on the text
        menuItem->rect.height = fontSize * 1.3;

        menuItem->buttonBackground.setPosition(sf::Vector2f(menuItem->rect.left, menuItem->rect.top));
        menuItem->buttonBackground.setSize(sf::Vector2f(menuItem->rect.width, menuItem->rect.height));
        menuItem->buttonBackground.setFillColor(buttonUnselectedColor);
        menuItem->buttonBackground.setOutlineColor(sf::Color::White);
        menuItem->buttonBackground.setOutlineThickness(1);

        menuItem->buttonName.setPosition(position.x + (menuItem->buttonBackground.getSize().x - menuItem->buttonName.getGlobalBounds().width) / 2, position.y);

        menuOptions.push_back(menuItem);
    }
    else
    {
        Button* menuItem = new Button();
        //Button textures are set up in a way where the width can be stretched, but the height must line up with the actual textures
        menuItem->setUpButton(itemName, *buttonFont, fontSize, buttonTextures, sf::Vector2f(position), sf::Vector2f(tmpText.length() * (fontSize / 1.5), fontSize * 1.7), sticky);
        menuButtons.push_back(menuItem);
    }
}

void Menu::createLabel(const std::string& labelName, sf::Vector2f position)
{
    sf::Text label;
    label.setString(labelName);
    label.setFont(*buttonFont);
    label.setCharacterSize(buttonFontSize);
    label.setPosition(position);

    labels.push_back(label);


}

void Menu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.setView(menuView);
    // Draw the background
    window.draw(bgSprite);

    // Draw menu choices
    for(auto& i: menuOptions)
    {
        window.draw(i->buttonBackground);
        window.draw(i->buttonName);
    }

    for(auto& i: menuButtons)
        window.draw(*i);

    for(auto i: labels)
    {
        window.draw(i);
    }

    window.draw(errorText);


}
