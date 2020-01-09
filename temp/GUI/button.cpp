#include "button.h"
#include <iostream>
Button::Button()
{
    highlighted = false;
    selected = false;

    buttonName.setString("");
    pressedDown = false;
    selected = false;
    staysOn = false;

}

Button::~Button()
{
    //dtor
}

void Button::setUpButton(const std::string& bName, sf::Font& buttonFont, short buttonFontSize, sf::Texture& textures, sf::Vector2f position, sf::Vector2f size, bool buttonStaysOn)
{
    buttonTexture = textures;

    font = buttonFont;
    fontSize = buttonFontSize;

    buttonName.setString(bName);
    buttonName.setCharacterSize(fontSize);
    buttonName.setColor(sf::Color::White);
    buttonName.setFont(font);

    buttonBox.left = position.x;
    buttonBox.top = position.y;
    buttonBox.width = size.x;
    buttonBox.height = size.y;

    button.setPosition(position);
    button.setSize(size);

    button.setTexture(&buttonTexture, false);

    //Texture will have button textures vertically in the following order: Default, highlighted, pressed
    defaultTextureRect.left = 0;
    defaultTextureRect.top = 0;
    defaultTextureRect.width = textures.getSize().x;
    defaultTextureRect.height = textures.getSize().y / 3;

    highlightedTextureRect.left = 0;
    highlightedTextureRect.top = textures.getSize().y / 3;
    highlightedTextureRect.width = textures.getSize().x;
    highlightedTextureRect.height = textures.getSize().y / 3;

    pressedTextureRect.left = 0;
    pressedTextureRect.top = 2 * (textures.getSize().y / 3);
    pressedTextureRect.width = textures.getSize().x;
    pressedTextureRect.height = textures.getSize().y / 3;

    button.setTextureRect(defaultTextureRect);

    buttonNamePos = sf::Vector2f(button.getPosition().x + (button.getSize().x - buttonName.getGlobalBounds().width) / 2, button.getPosition().y + (button.getSize().y - buttonName.getGlobalBounds().height) / 2);
    buttonName.setPosition(buttonNamePos);


    staysOn = buttonStaysOn;



}
void Button::toggleSelected()
{
    selected = !selected;

}
void Button::releaseButton()
{
    pressedDown = false;
}

void Button::handleMouseMovement(sf::Event& event, sf::RenderWindow& window)
{
   if (buttonBox.contains(event.mouseMove.x, event.mouseMove.y) && !pressedDown && !highlighted)
   {
        //std::cout << "Highlighting button\n";
        highlighted = true;
   }
   else if(!buttonBox.contains(event.mouseMove.x, event.mouseMove.y))
   {
        highlighted = false;
   }


}

bool Button::handleMouseReleased(sf::Event& event, sf::RenderWindow& window)
{
    bool pressed = false;
    if(!staysOn)
        pressedDown = false;

    if (buttonBox.contains(sf::Mouse::getPosition(window)) && event.mouseButton.button == sf::Mouse::Left)
    {
        pressed = true;
      //  if(pressedDown)
        //    pressedDown = false;
     //   else
        //    pressedDown = true;
    }

    return pressed;
}

bool Button::handleMousePressed(sf::Event& event, sf::RenderWindow& window)
{
    if (buttonBox.contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
       //std::cout << "Pressing button\n";
        if(!pressedDown)
            pressedDown = true;
        else
            pressedDown = false;

    }
    return pressedDown;
}

bool Button::handleKeyPressed(sf::Event& event)
{
    if(event.key.code == hotKey)
        pressedDown = true;

    return pressedDown;
}

bool Button::handleKeyReleased(sf::Event& event)
{
    if(!staysOn)
        pressedDown = false;

    if (event.key.code == hotKey)
    {
        toggleSelected();
    }
    if(!selected)
        pressedDown = false;


    return selected;
}

void Button::setHotkey(sf::Keyboard::Key key)
{
    hotKey = key;
    hotkeySet = true;
}

void Button::setButtonName(const std::string& bName)
{
    buttonName.setString(bName);
    buttonName.setPosition(button.getPosition().x + (button.getSize().x - buttonName.getGlobalBounds().width) / 2, button.getPosition().y + (button.getSize().y - buttonName.getGlobalBounds().height) / 2);
}

void Button::setTextures(sf::Texture& textures)
{
    button.setTexture(&textures);
}



std::string Button::getButtonName() const
{
    return buttonName.getString();
}

bool Button::getSelected() const
{
    return selected;
}

bool Button::isHighlighted()
{
    return highlighted;
}

bool Button::isPressedDown()
{
    return pressedDown;
}

bool Button::doesStayPressed()
{
    return staysOn;
}

void Button::updateButton()
{
    if(pressedDown)
    {
        button.setTextureRect(pressedTextureRect);
        //Give the effect that the text is a part of the button
        buttonName.setPosition(buttonNamePos.x + 1, buttonNamePos.y + 1);
    }
    else if(highlighted)
    {
        button.setTextureRect(highlightedTextureRect);
        buttonName.setPosition(buttonNamePos);
    }
    else
    {
        button.setTextureRect(defaultTextureRect);
        buttonName.setPosition(buttonNamePos);
    }

    if(!staysOn)
        pressedDown = false;
}

void Button::draw(sf::RenderTarget& window, sf::RenderStates states) const
{

    window.draw(button);
    window.draw(buttonName);
}
