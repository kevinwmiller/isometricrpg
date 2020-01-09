#include "hud.h"

Hud::Hud()
{
    hudSize = 2;
}

Hud::~Hud()
{
    //dtor
}

void Hud::setUp(ResourceManager& resources, Player* player)
{
    hudView.reset(sf::FloatRect(0, 0, resources.window.getSize().x, resources.window.getSize().y));

    sf::Color statusBarBackgroundCol(190, 190, 190, 75);

    //StatusBar placement and sizing is temporary
    sf::Vector2f healthBarPos(resources.window.getSize().x / 2.7, resources.window.getSize().y / 1.15);
    sf::Vector2f healthBarSize(resources.window.getSize().x / 8, resources.window.getSize().y / 54);
    sf::Color healthBarFillColor(250, 20, 20, 200);
    std::string healthBarName("Health");

    sf::Vector2f magicBarPos(resources.window.getSize().x / 1.98, resources.window.getSize().y / 1.15);
    sf::Vector2f magicBarSize(resources.window.getSize().x / 8, resources.window.getSize().y / 54);
    sf::Color magicBarFillColor(0, 0, 200, 200);
    std::string magicBarName("Magic");

    sf::Vector2f expBarSize(resources.window.getSize().x / 4, 5);
    sf::Vector2f expBarPos(resources.window.getSize().x / 2 - expBarSize.x / 2 , resources.window.getSize().y / 1.1);
    sf::Color expBarFillColor(255, 255, 200, 200);
    std::string expBarName("Experience");

    healthBar.setUp("Health", healthBarPos, healthBarSize, 0, player->retrieveStatValue(0, "Health"), player->retrieveStatValue(1, "Health"), 2, statusBarBackgroundCol, healthBarFillColor, resources.fontBold, sf::Color::Cyan, true, false);
    magicBar.setUp("Magic", magicBarPos, magicBarSize, 0, player->retrieveStatValue(0, "Health"), player->retrieveStatValue(1, "Magic"), 2, statusBarBackgroundCol, magicBarFillColor, resources.fontBold, sf::Color::Cyan, true, false);
    experienceBar.setUp("Experience", expBarPos, expBarSize, 0, player->retrieveStatValue(0, "Experience"), player->retrieveStatValue(1, "Experience"), 2, statusBarBackgroundCol, expBarFillColor, resources.fontBold, sf::Color::Black, false, false);

    leftAttack.setFillColor(sf::Color(255, 255, 200, 200));
    leftAttack.setSize(sf::Vector2f(resources.window.getSize().x / 25, resources.window.getSize().x / 25));
    leftAttack.setPosition(resources.window.getSize().x / 3.5, resources.window.getSize().y / 1.09);

    rightAttack.setFillColor(sf::Color(255, 255, 200, 200));
    rightAttack.setSize(sf::Vector2f(resources.window.getSize().x / 25, resources.window.getSize().x / 25));
    rightAttack.setPosition(resources.window.getSize().x / 1.48, resources.window.getSize().y / 1.09);

    infoBar.setFillColor(sf::Color(0, 0, 0, 175));
    infoBar.setSize(sf::Vector2f(resources.window.getSize().x / 6, resources.window.getSize().y / 30));
    infoBar.setPosition(resources.window.getSize().x / 2 -infoBar.getSize().x / 2 , resources.window.getSize().y / 1.05);

    consumableBar.setFillColor(sf::Color(0, 0, 0, 175));
    consumableBar.setSize(sf::Vector2f(resources.window.getSize().x / 6, resources.window.getSize().y / 30));
    consumableBar.setPosition(resources.window.getSize().x - (1.3 * infoBar.getSize().x)  , resources.window.getSize().y / 1.05);

    miniMap.setFillColor(sf::Color(0, 0, 0, 175));
    miniMap.setSize(sf::Vector2f(resources.window.getSize().x / 9, resources.window.getSize().x / 9));
    miniMap.setPosition(2, resources.window.getSize().y - miniMap.getSize().y - 2);

}

void Hud::update(Player* player)
{
    healthBar.setMaximumValue(player->retrieveStatValue(1, "Health"));
    healthBar.setCurrentValue(player->retrieveStatValue(0, "Health"));

    magicBar.setMaximumValue(player->retrieveStatValue(1, "Magic"));
    magicBar.setCurrentValue(player->retrieveStatValue(0, "Magic"));

    experienceBar.setMaximumValue(player->retrieveStatValue(1, "Experience"));
    experienceBar.setCurrentValue(player->retrieveStatValue(0, "Experience"));

    healthBar.updateBar();
    magicBar.updateBar();
    experienceBar.updateBar();
}

void Hud::handleMouseMoved(sf::Event& event, sf::RenderWindow& window)
{
    healthBar.isMousedOver(window);
    magicBar.isMousedOver(window);
    experienceBar.isMousedOver(window);
}

void Hud::draw(sf::RenderWindow& window)
{
    window.setView(hudView);

    window.draw(healthBar);
    window.draw(magicBar);
    window.draw(experienceBar);

    window.draw(leftAttack);
    window.draw(rightAttack);

    window.draw(infoBar);
   // window.draw(consumableBar);

    window.draw(miniMap);
}
