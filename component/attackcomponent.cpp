#include "attackcomponent.h"

AttackComponent::AttackComponent()
{
    attacking = false;
}

AttackComponent::~AttackComponent()
{
    //dtor
}

bool AttackComponent::isAttacking() const
{
    return attacking;
}

void AttackComponent::startAttack(const sf::Vector2f& targetLoc)
{
    attacking = true;

   // angle = atan2((targetLoc.y  - data.getPos().y) , (targetLoc.x - data.getPos().x));

}

void AttackComponent::stopAttack()
{
    attacking = false;
}
