#ifndef ATTACKCOMPONENT_H
#define ATTACKCOMPONENT_H

#include <SFML/Graphics.hpp>

class AttackComponent
{
    public:
        AttackComponent();
        ~AttackComponent();


        bool isAttacking() const;

        void startAttack(const sf::Vector2f&);
        void stopAttack();

    private:

        bool attacking;
};

#endif // ATTACKCOMPONENT_H
