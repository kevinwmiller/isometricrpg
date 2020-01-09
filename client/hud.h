#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "resourcemanager.h"
#include "statusbar.h"
#include "player.h"

class Hud
{
    public:
        Hud();
        ~Hud();

        enum HudSize
        {
            Small = 1,
            Medium,
            Large
        };

        void setUp(ResourceManager&, Player*);
        void update(Player*);

        void handleMouseMoved(sf::Event&, sf::RenderWindow&);

        void draw(sf::RenderWindow&);

    private:



        int hudSize;

        StatusBar healthBar;
        StatusBar magicBar;
        StatusBar experienceBar;


        //Placeholders
        sf::RectangleShape leftAttack;
        sf::RectangleShape rightAttack;

        sf::RectangleShape infoBar;
        sf::RectangleShape consumableBar;

        sf::RectangleShape miniMap;

        sf::View hudView;
};

#endif // HUD_H
