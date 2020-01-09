#ifndef MOUSECURSOR_H
#define MOUSECURSOR_H


#include <SFML/Graphics.hpp>
#include "entity.h"
#include "isometricmap.h"

//Class used to check collisions with the mouse cursor and entities.

class MouseCursor : public Entity
{
    public:
        MouseCursor();
        ~MouseCursor();


        void handleEvents();
        sf::Vector2f getEntityOrigin();
        void updateBoundingBox();
        void updateCursorPosition(sf::RenderWindow&, sf::View& view);
        void onEntityCollision(Entity*);
        void update(float, IsometricMap*);
        void draw(sf::RenderWindow&);

    private:

        sf::Vector2f cursorPos;

};

#endif // MOUSECURSOR_H
