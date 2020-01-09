#include "player.h"
#include <cmath>
#include <iostream>


const std::string nUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/nUnarmedStanding.png");
const std::string eUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/eUnarmedStanding.png");
const std::string sUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/sUnarmedStanding.png");
const std::string wUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/wUnarmedStanding.png");
const std::string nwUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/nwUnarmedStanding.png");
const std::string neUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/neUnarmedStanding.png");
const std::string seUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/seUnarmedStanding.png");
const std::string swUnarmedStandingAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedStanding/swUnarmedStanding.png");

const std::string nUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/nUnarmedWalk.png");
const std::string eUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/eUnarmedWalk.png");
const std::string sUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/sUnarmedWalk.png");
const std::string wUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/wUnarmedWalk.png");
const std::string nwUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/nwUnarmedWalk.png");
const std::string neUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/neUnarmedWalk.png");
const std::string seUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/seUnarmedWalk.png");
const std::string swUnarmedWalkAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedWalking/swUnarmedWalk.png");

const std::string nUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/nUnarmedRunning.png");
const std::string eUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/eUnarmedRunning.png");
const std::string sUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/sUnarmedRunning.png");
const std::string wUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/wUnarmedRunning.png");
const std::string nwUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/nwUnarmedRunning.png");
const std::string neUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/neUnarmedRunning.png");
const std::string seUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/seUnarmedRunning.png");
const std::string swUnarmedRunAnim("resources/images/Characters/Player/UnarmedAnimations/unarmedRunning/swUnarmedRunning.png");

const std::string nBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/nBowAttack.png");
const std::string eBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/eBowAttack.png");
const std::string sBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/sBowAttack.png");
const std::string wBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/wBowAttack.png");
const std::string nwBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/nwBowAttack.png");
const std::string neBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/neBowAttack.png");
const std::string seBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/seBowAttack.png");
const std::string swBowAttackAnim("resources/images/Characters/Player/BowAnimations/BowAttacking/swBowAttack.png");


Player::Player()
{
    std::string name("Player");


    loadAnimations();

    cAnimation.changeAnimationSet("UnarmedStanding", 0);

    //Offset of the sprite's origin compared to the top left corner.
    cAnimation.setSpriteBoundsOffset(sf::Vector2f(40, 60));

    color = sf::Color::White;

    entityType = Entity::Type::Mobile;
    subType = Entity::MobileSubType::Player;

    data.setPos(sf::Vector2f(1500, 1500));
    sprite.setPosition(data.getPos());
    name = "Player";


    setBoundingBox(sprite.getGlobalBounds());



}

Player::~Player()
{
    std::cout << "Player destructor called\n";
}


void Player::loadCharacterData(std::string& file)
{
    std::cout << "Loading character...\n";
    saveFile = file;
    data.loadCharacterData(file);
    //Only needs to be set once. The move component will keep track of the entities origin
    cMove.setPosition(sf::Vector2f(data.getPos().x, data.getPos().y));
    cMove.setMaxSpeed(data.getRunSpeed());

    updateBoundingBox();

    name = data.getName();
  //  std::cout << "Player pos " << data.getPos().x << ', ' << data.getPos().y << std::endl;
    std::cout << "Character loaded successfully\n";
}


void Player::saveCharacterData(std::string& file)
{
    std::cout << "Saving character...\n";
    data.saveCharacterData(file);
    std::cout << "Character saved successfully\n";
}

void Player::onEntityCollision(Entity* otherEntity)
{
    std::cout << name << " colliding with " << otherEntity->getName() << std::endl << std::endl;;

    int otherEntType = otherEntity->getEntityType();
    int otherEntSubType = otherEntity->getSubType();


    if(otherEntType == Entity::Type::Static || (otherEntType == Entity::Type::Mobile && otherEntSubType == Entity::MobileSubType::Npc))
    {

        if(otherEntSubType == Entity::StaticSubType::Scenery || (otherEntType == Entity::Type::Mobile && otherEntSubType == Entity::MobileSubType::Npc))
        {
            std::cout << "Colliding with scenery or npc\n";

            cMove.stopMoving();
            cMove.setPosition(sf::Vector2f(cMove.getPosition().x - cMove.getMoveAmount().x, cMove.getPosition().y - cMove.getMoveAmount().y));
            cAnimation.setPosition(cMove.getPosition());
            data.setPos(cMove.getPosition());
        }
    }

}

void Player::handleEvents()
{
    //std::cout << "number of events: " << events.getNumberOfEvents() << std::endl;
    while(!events.isEventListEmpty())
    {
        std::cout << "Handling events\n";
        //Get the next event

        int type = events.getNextEventType();
        std::cout << "Event Type " << type << "\n";
        int value = events.getNextEventValue();
        std::cout << "Event value " << value << "\n";
        std::string args = events.getNextEventArgs();

        std::cout << "Event arguments " << args << "\n";

        //Handle the specified event
        if(type == EntityEvents::InterEntityEvents::ModifyStat)
        {
            if(args == "Health")
                data.modifyHealth(value);
            else if(args == "Focus")
                data.modifyFocus(value);
            else if(args == "Experience")
                data.addExperience(value);
            else if(args == "Defense")
                data.modifyDefense(value);
            else if(args == "Strength")
                data.modifyStrength(value);
            else if(args == "Dexterity")
                data.modifyDexterity(value);
            else if(args == "Intelligence")
                data.modifyIntelligence(value);
            else if(args == "Speed")
                data.modifySpeed(value);
        }

        else if(type == EntityEvents::InterEntityEvents::PermModifyStat)
        {
            if(args == "Health")
                data.setMaxHealth(data.getMaxHealth() + value);
            else if(args == "Focus")
                data.setMaxFocus(data.getMaxFocus() + value);
            else if(args == "Defense")
                data.setMaxDefense(data.getMaxStrength() + value);
            else if(args == "Strength")
                data.setMaxStrength(data.getMaxStrength() + value);
            else if(args == "Dexterity")
                data.setMaxDexterity(data.getMaxDexterity() + value);
            else if(args == "Intelligence")
                data.setmaxIntelligence(data.getmaxIntelligence() + value);
            else if(args == "Speed")
                data.setMaxSpeed(data.getMaxSpeed() + value);
        }


        events.removeEvent();

    }
}

void Player::update(float elapsedTime, IsometricMap* world)
{

  //  std::cout << "Elapsed Time " << elapsedTime << std::endl;

    //Start/Update the appropriate animation

    cMove.updateMovement(elapsedTime);
    data.setDirection(cMove.getDirection());
    data.setPos(cMove.getPosition());


    //Check for world collision. Undo the movement if there is
    if(world->isOnCollidableTile(data.getPos()))
    {
        cMove.stopMoving();
        cMove.setPosition(sf::Vector2f(cMove.getPosition().x - cMove.getMoveAmount().x, cMove.getPosition().y - cMove.getMoveAmount().y));
        cAnimation.setPosition(cMove.getPosition());
        data.setPos(cMove.getPosition());

    }

    if(cMove.isMoving())
    {

        if(cMove.isRunning())
        {
            cAnimation.changeAnimationSet("UnarmedRunning", data.getDirection());
        }
        else
        {
            cAnimation.changeAnimationSet("UnarmedWalking", data.getDirection());
        }

    }
    else if(cAttack.isAttacking())
    {
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && cAnimation.isCurrentAnimationSetFinished())
        {
            cAttack.stopAttack();
        }
    }
    else
    {
        cAnimation.changeAnimationSet("UnarmedStanding", data.getDirection());
    }
    handleEvents();
    updateBoundingBox();
    depthValue = getEntityOrigin().y;

    cAnimation.updateCurrentAnimationSet(elapsedTime, getEntityOrigin());

}

void Player::updateBoundingBox()
{
    setBoundingBox(sf::FloatRect(cAnimation.getSpritePosition().x + 35, cAnimation.getSpritePosition().y + 37, 26, 40));
}

void Player::loadAnimations()
{
    std::vector<std::string> unarmedWalkTextureFiles;
    unarmedWalkTextureFiles.push_back(nUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(eUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(sUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(wUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(nwUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(neUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(seUnarmedWalkAnim);
    unarmedWalkTextureFiles.push_back(swUnarmedWalkAnim);

    std::vector<std::string> unarmedStandingTextureFiles;
    unarmedStandingTextureFiles.push_back(nUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(eUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(sUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(wUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(nwUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(neUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(seUnarmedStandingAnim);
    unarmedStandingTextureFiles.push_back(swUnarmedStandingAnim);

    std::vector<std::string> unarmedRunningTextureFiles;
    unarmedRunningTextureFiles.push_back(nUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(eUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(sUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(wUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(nwUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(neUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(seUnarmedRunAnim);
    unarmedRunningTextureFiles.push_back(swUnarmedRunAnim);

    std::vector<std::string> bowAttackTextureFiles;
    bowAttackTextureFiles.push_back(nBowAttackAnim);
    bowAttackTextureFiles.push_back(eBowAttackAnim);
    bowAttackTextureFiles.push_back(sBowAttackAnim);
    bowAttackTextureFiles.push_back(wBowAttackAnim);
    bowAttackTextureFiles.push_back(nwBowAttackAnim);
    bowAttackTextureFiles.push_back(neBowAttackAnim);
    bowAttackTextureFiles.push_back(seBowAttackAnim);
    bowAttackTextureFiles.push_back(swBowAttackAnim);

    AnimationComponent::addAnimationSet("UnarmedWalking", unarmedWalkTextureFiles, .1, true, 9, sf::Vector2f(96, 96));
    AnimationComponent::addAnimationSet("UnarmedStanding", unarmedStandingTextureFiles, 0, false, 1, sf::Vector2f(96, 96));
    AnimationComponent::addAnimationSet("UnarmedRunning", unarmedRunningTextureFiles, .07, true, 9, sf::Vector2f(96, 96));
    AnimationComponent::addAnimationSet("BowAttack", bowAttackTextureFiles, .04, true, 11, sf::Vector2f(96, 96));

}


sf::Vector2f Player::getEntityOrigin()
{
    //Needs to be adjusted for character sprite
    //The foot position will be different depending on the direction that the sprite is facing
    sf::Vector2f feetPos;
    feetPos = sf::Vector2f(cMove.getPosition().x, cMove.getPosition().y);
    return feetPos;

}

void Player::moveTo(sf::Vector2f destPos)
{
    cMove.moveTo(destPos);
}

void Player::attack(sf::Vector2f target)
{
    cAttack.startAttack(target);
}

void Player::toggleRunning()
{
    cMove.toggleRunning();
}

int Player::retrieveStatValue(int current_Max, const std::string& statName) const
{
    return data.retrieveValue(current_Max, statName);
}

void Player::draw(sf::RenderWindow& window)
{
  /*  int color = rand() % 10;

    if(color == 0)
        cAnimation.setSpriteColor(sf::Color::Red);
    else if(color == 1)
        cAnimation.setSpriteColor(sf::Color::Blue);
    else if(color == 2)
        cAnimation.setSpriteColor(sf::Color::Green);
    else if(color == 3)
        cAnimation.setSpriteColor(sf::Color::Cyan);
    else if(color == 4)
        cAnimation.setSpriteColor(sf::Color::Transparent);
    else if(color == 5)
        cAnimation.setSpriteColor(sf::Color::Magenta);
    else if(color == 6)
        cAnimation.setSpriteColor(sf::Color::Black);
    else if(color == 7)
        cAnimation.setSpriteColor(sf::Color::Yellow);
    else if(color == 8)
        cAnimation.setSpriteColor(sf::Color(34, 34, 50, 75));
    else if(color == 9)
        cAnimation.setSpriteColor(sf::Color::White);

*/
    cAnimation.drawCurrentFrame(window);

    if(boundingBoxVisible)
        window.draw(visibleBoundingBox);
}


