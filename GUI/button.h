#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
/*
    Button class that uses a texture containing 3 button images: Default, highlighted, and pressed down

    Supports optional hotkeys

    Will eventually add optional button description that will show on hover
*/
class Button: public sf::Drawable
{
    public:
        Button();
        ~Button();

        //The texture contains the default texture, highlighed texture, and pressed Texture
        void setUpButton(const std::string&, sf::Font&, short,  sf::Texture&, sf::Vector2f, sf::Vector2f,bool);

        void handleMouseMovement(sf::Event&, sf::RenderWindow&);
        bool handleMouseReleased(sf::Event&, sf::RenderWindow&);
        bool handleMousePressed(sf::Event&, sf::RenderWindow&);
        bool handleKeyPressed(sf::Event&);
        bool handleKeyReleased(sf::Event&);

        void setButtonName(const std::string& bName);
        void setTextures(sf::Texture&);
        void setHotkey(sf::Keyboard::Key key);
        void toggleSelected();
        void releaseButton();

        std::string getButtonName() const;
        bool getSelected() const;
        bool isHighlighted();
        bool isPressedDown();
        bool doesStayPressed();

        void updateButton();
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;


    private:
        std::string buttonDescription;
        sf::Text buttonName;
        sf::Vector2f buttonNamePos;

        bool highlighted;
        bool pressedDown;
        bool staysOn;
        bool selected;
        bool hotkeySet;

        sf::IntRect defaultTextureRect;
        sf::IntRect highlightedTextureRect;
        sf::IntRect pressedTextureRect;

        sf::Font font;
        short fontSize;

        sf::Texture buttonTexture;

        sf::Keyboard::Key hotKey;
        sf::IntRect buttonBox;
        sf::RectangleShape button;


};

#endif // BUTTON_H
