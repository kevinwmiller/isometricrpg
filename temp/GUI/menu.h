// See the file COPYRIGHT.txt for authors and copyright information.
// See the file LICENSE.txt for copying conditions.

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <deque>
#include "button.h"

/*
    Menu class that can be used as a component for any type of menu screen.
    Need to fix sticky buttons
*/

//Clickable buttons
struct MenuButton
{
    //The name of the button
    sf::Text buttonName;
    sf::Rect<int> rect;
    sf::RectangleShape buttonBackground;
    sf::Color unselectedColor;
    sf::Color selectedColor;

    short fontSize;
    sf::Font font;
};

class Menu: public sf::Drawable
{
    public:

        Menu();
        ~Menu();

        //Background file, font file, font size, topButtonPos, the window, and the desired view
        void setUpMenu(const std::string&, sf::Color, short, sf::Vector2f, sf::RenderWindow&, sf::Font&, const std::string& = "");

        void updateMenu();
        void clearButtons();

        void setBackground(const std::string&);
        void setFont(const std::string&);
        void setFontSize(short);

        void setErrorTextString(const std::string&, sf::Color = sf::Color::White);
        void setErrorTextPosition(sf::Vector2f, bool = false);

        void setTopButtonLocation(sf::Vector2f);
        void setButtonColors(sf::Color);

        void addMenuButton(const std::string&, bool = false, short = -1);
        void addMenuButton(const std::string&, sf::Vector2f, bool = false, short = -1);
        void createLabel(const std::string&, sf::Vector2f);

        //Returns 1 if first button is pressed, 2 if second button is pressed, etc.
        //Returns -1 if window is closed.
        int handleEvents();

        void handleMouseMovement(sf::Event&, sf::RenderWindow&);
        int handleMouseReleased(sf::Event&, sf::RenderWindow&);
        void handleMousePressed(sf::Event&, sf::RenderWindow&);
        int handleKeyPressed(sf::Event&, sf::RenderWindow&);
        void handleResize(sf::Event&, sf::RenderWindow&);

        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;


    private:

        //Utility Functions
        void fixRectangles(float, float);

        //Formatting variables
        sf::Color buttonUnselectedColor;
        sf::Color buttonSelectedColor;
        sf::Color buttonPressedColor;
        sf::Color buttonStandardColor;
        sf::Color buttonHighlightedColor;
        sf::Font* buttonFont;
        short buttonFontSize;
        sf::Vector2f topButtonPos;

        //Background
        sf::Texture bgTexture;
        sf::Sprite bgSprite;
        sf::Vector2u bgImageSize;

        bool buttonTexturesSet;
        sf::Texture buttonTextures;

        //Used to keep track of the size of the window before resizing
        sf::Vector2f windowSize;
        sf::View menuView;

        //Used to reorientate the buttons on resize
        float buttonWidthFactor;
        float buttonHeightFactor;

        int selection;
        //Used for sticky buttons
        int lastSelection;
        bool selectionMade;

        const int buttonPadding = 20;

        sf::Text errorText;

        //Array of buttons that are on the screen
        //Generic menu buttons without a texture
        std::vector<MenuButton*> menuOptions;

        std::vector<Button*> menuButtons;
        std::vector<sf::Text> labels;
        std::deque<Button*> pressedButtons;

        sf::Font* font;
};

#endif // MENU_H
