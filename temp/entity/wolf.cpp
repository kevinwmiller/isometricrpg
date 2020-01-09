#include "wolf.h"
#include <iostream>
#include <sstream>
std::string nStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/nStanding.png");
std::string eStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/eStanding.png");
std::string sStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/sStanding.png");
std::string wStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/wStanding.png");
std::string nwStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/nwStanding.png");
std::string neStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/neStanding.png");
std::string seStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/seStanding.png");
std::string swStandingAnim("resources/images/Characters/Npcs/Wolf/Standing/swStanding.png");

std::string nWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/nWalking.png");
std::string eWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/eWalking.png");
std::string sWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/sWalking.png");
std::string wWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/wWalking.png");
std::string nwWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/nwWalking.png");
std::string neWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/neWalking.png");
std::string seWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/seWalking.png");
std::string swWalkAnim("resources/images/Characters/Npcs/Wolf/Walking/swWalking.png");

std::string nRunningAnim("resources/images/Characters/Npcs/Wolf/Running/nRunning.png");
std::string eRunningAnim("resources/images/Characters/Npcs/Wolf/Running/eRunning.png");
std::string sRunningAnim("resources/images/Characters/Npcs/Wolf/Running/sRunning.png");
std::string wRunningAnim("resources/images/Characters/Npcs/Wolf/Running/wRunning.png");
std::string nwRunningAnim("resources/images/Characters/Npcs/Wolf/Running/nwRunning.png");
std::string neRunningAnim("resources/images/Characters/Npcs/Wolf/Running/neRunning.png");
std::string seRunningAnim("resources/images/Characters/Npcs/Wolf/Running/seRunning.png");
std::string swRunningAnim("resources/images/Characters/Npcs/Wolf/Running/swRunning.png");

std::string nAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/nAttacking.png");
std::string eAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/eAttacking.png");
std::string sAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/sAttacking.png");
std::string wAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/wAttacking.png");
std::string nwAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/nwAttacking.png");
std::string neAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/neAttacking.png");
std::string seAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/seAttacking.png");
std::string swAttackingAnim("resources/images/Characters/Npcs/Wolf/Attacking/swAttacking.png");



int Wolf::numWolves = 0;
Wolf::Wolf()
{

    std::stringstream ss;


    color = sf::Color::White;



    /*runSpeed = 90;
    walkSpeed = 60;

    data.setMaxSpeed(walkSpeed);
    running = false;
    spawnLoc.x = rand() % 1000;
    spawnLoc.y = rand() % 1000;

    ss << numWolves;

    name = "Wolf " + ss.str();
    subType = Entity::MobileSubType::Npc;

    data.setPos(sf::Vector2f(spawnLoc.x, spawnLoc.y));
    sprite.setPosition(data.getPos());



    setBoundingBox(sprite.getGlobalBounds());

    numWolves++;*/
    //std::cout << data.getPos().x << ', ' << data.getPos().y << std::endl;
}

Wolf::~Wolf()
{
    //dtor
}

void Wolf::update(float elapsedTime, IsometricMap* world)
{
   /* float distanceFromSpawn = sqrt((getEntityOrigin().y  - spawnLoc.y) * (getEntityOrigin().y - spawnLoc.y) + (getEntityOrigin().x - spawnLoc.x) * (getEntityOrigin().x - spawnLoc.x));


//Start/Update the appropriate animation
    if(!moving && distanceFromSpawn < roamingDistance)
    {
   //     std::cout << "Random Direction\n";
    //    moveTo(sf::Vector2f(getEntityOrigin().x + (rand() % roamingDistance) + 1 , getEntityOrigin().y + (rand() % roamingDistance) + 1), getEntityOrigin());

    }
    else if(distanceFromSpawn > roamingDistance)
    {
      //  std::cout << "Spawn Location " << spawnLoc.x << ',' <<spawnLoc.y << '\n';
      //  std::cout << "Current Location " << getFeetPosition().x << ',' <<getFeetPosition().y << '\n';
      //  std::cout << "Distance " << distanceFromSpawn << '\n';
        int xDisplacement = (rand() % roamingDistance);

        if(xDisplacement % 2 == 0)
            xDisplacement *= -1;

        int yDisplacement = (rand() % roamingDistance);

        if(yDisplacement % 2 == 0)
            yDisplacement *= -1;

        moveTo(sf::Vector2f(spawnLoc.x + xDisplacement, spawnLoc.y + yDisplacement), getFeetPosition());
        //moveTo(sf::Vector2f(getFeetPosition().x + (rand() % roamingDistance) + 1 , getFeetPosition().y + (rand() % roamingDistance) + 1), getFeetPosition());
    }

    if(world->isOnCollidableTile(sf::Vector2f(getFeetPosition().x + moveAmount.x, getFeetPosition().y + moveAmount.y)))
    {
        //std::cout << "Colliding with Tile\n";

       moveTo(sf::Vector2f(spawnLoc.x, spawnLoc.y), getFeetPosition());
    }

    //Use distance formula to determine if the entity is going out of its roaming range. If it is. Send it back towards its spawn


    if(moving)
    {
        stopAttack();

        if(running == false && currentAnimation != &walkAnimation && !walkAnimation.isAnimFinished())
        {
            changeAnimation(walkAnimation);
            currentTexture = walkingTextures;
        }
        else if(running == true && currentAnimation != &runningAnimation && !runningAnimation.isAnimFinished())
        {
            changeAnimation(runningAnimation);
            currentTexture = runningTextures;
        }


        //sprite.move(moveAmount);
        //data.setPos(sprite.getPosition());


    }
    else if(attacking)
    {

    }

    else
    {
        changeAnimation(standingAnimation);
        currentTexture = standingTextures;
    }

    //std::cout << currentAnimation <<std::endl;

    depthValue = getFeetPosition().y;


    sprite.setTexture(currentTexture[data.getDirection()]);
    sf::IntRect frame = currentAnimation->update(elapsedTime);

    updateBoundingBox();

    sprite.setTextureRect(frame);
    sprite.setColor(color);*/
}

void Wolf::startAttack(sf::Vector2f targetLoc)
{
 /*   attacking = true;
    moving = false;

    angle = atan2((targetLoc.y  - data.getPos().y) , (targetLoc.x - data.getPos().x));

    data.setDirection(determineDirection(angle));
    currentAnimation->changeDirection(data.getDirection());

    if(currentAnimation != &attackAnimation)
    {
        changeAnimation(attackAnimation);
        currentTexture = attackingTextures;
    }*/
}

void Wolf::stopAttack()
{
   // attacking = false;
  //  currentAnimation->resetAllAnimations();
}

void Wolf::onEntityCollision(Entity* otherEntity)
{
 //   std::cout << name << " colliding with " << otherEntity->getName() << std::endl;

 /*   int otherEntType = otherEntity->getEntityType();
    int otherEntSubType = otherEntity->getSubType();

    if(otherEntType == Entity::Type::Static || otherEntType == Entity::Type::Mobile && otherEntSubType == Entity::MobileSubType::Npc || otherEntSubType == Entity::MobileSubType::Player)
    {
        if(otherEntSubType == Entity::StaticSubType::Scenery || otherEntType == Entity::Type::Mobile && otherEntSubType == Entity::MobileSubType::Npc || otherEntSubType == Entity::MobileSubType::Player)
        {
          //  std::cout << "Colliding with scenery or npc\n";

           // std::cout << "Colliding with scenery or npc\n";
            //Just stop moving until path finding is added
            if(moving)
            {
                moving = false;
                sprite.setPosition(sprite.getPosition().x - moveAmount.x, sprite.getPosition().y - moveAmount.y);
                data.setPos(sprite.getPosition());
            }

        }
    }*/
}

//The wolves bounding box changes based on the direction it is facing
void Wolf::updateBoundingBox()
{
  /*  if(data.getDirection() == north || data.getDirection() == south)
        setBoundingBox(sf::FloatRect(sprite.getPosition().x + 40, sprite.getPosition().y + 30, 18, 53));

    else if(data.getDirection() == east || data.getDirection() == west)
        setBoundingBox(sf::FloatRect(sprite.getPosition().x + 8, sprite.getPosition().y + 41, 74, 16));

    else
        setBoundingBox(sf::FloatRect(sprite.getPosition().x + 34, sprite.getPosition().y + 38, 38, 27));*/
}

void Wolf::loadAnimations()
{
  /*  if (!walkingTextures[north].loadFromFile(nWalkAnim))
        exit(100);
    if (!walkingTextures[east].loadFromFile(eWalkAnim))
        exit(101);
    if (!walkingTextures[south].loadFromFile(sWalkAnim))
        exit(102);
    if (!walkingTextures[west].loadFromFile(wWalkAnim))
        exit(103);
    if (!walkingTextures[northwest].loadFromFile(nwWalkAnim))
        exit(104);
    if (!walkingTextures[northeast].loadFromFile(neWalkAnim))
        exit(105);
    if (!walkingTextures[southeast].loadFromFile(seWalkAnim))
        exit(106);
    if (!walkingTextures[southwest].loadFromFile(swWalkAnim))
        exit(107);

    if(!standingTextures[north].loadFromFile(nStandingAnim))
        exit(100);
    if(!standingTextures[east].loadFromFile(eStandingAnim))
        exit(101);
    if(!standingTextures[south].loadFromFile(sStandingAnim))
        exit(102);
    if(!standingTextures[west].loadFromFile(wStandingAnim))
        exit(103);
    if(!standingTextures[northwest].loadFromFile(nwStandingAnim))
        exit(104);
    if(!standingTextures[northeast].loadFromFile(neStandingAnim))
        exit(105);
    if(!standingTextures[southeast].loadFromFile(seStandingAnim))
        exit(106);
    if(!standingTextures[southwest].loadFromFile(swStandingAnim))
        exit(107);

    if(!runningTextures[north].loadFromFile(nRunningAnim))
        exit(100);
    if(!runningTextures[east].loadFromFile(eRunningAnim))
        exit(101);
    if(!runningTextures[south].loadFromFile(sRunningAnim))
        exit(102);
    if(!runningTextures[west].loadFromFile(wRunningAnim))
        exit(103);
    if(!runningTextures[northwest].loadFromFile(nwRunningAnim))
        exit(104);
    if(!runningTextures[northeast].loadFromFile(neRunningAnim))
        exit(105);
    if(!runningTextures[southeast].loadFromFile(seRunningAnim))
        exit(106);
    if(!runningTextures[southwest].loadFromFile(swRunningAnim))
        exit(107);

    if(!attackingTextures[north].loadFromFile(nAttackingAnim))
        exit(100);
    if(!attackingTextures[east].loadFromFile(eAttackingAnim))
        exit(101);
    if(!attackingTextures[south].loadFromFile(sAttackingAnim))
        exit(102);
    if(!attackingTextures[west].loadFromFile(wAttackingAnim))
        exit(103);
    if(!attackingTextures[northwest].loadFromFile(nwAttackingAnim))
        exit(104);
    if(!attackingTextures[northeast].loadFromFile(neAttackingAnim))
        exit(105);
    if(!attackingTextures[southeast].loadFromFile(seAttackingAnim))
        exit(106);
    if(!attackingTextures[southwest].loadFromFile(swAttackingAnim))
        exit(107);

    walkAnimation.loadAnimations(1, true, 8, sf::Vector2f(96, 96), walkingTextures[north], walkingTextures[east], walkingTextures[south], walkingTextures[west], walkingTextures[northwest], walkingTextures[northeast], walkingTextures[southeast], walkingTextures[southwest]);
    standingAnimation.loadAnimations(0, false, 1, sf::Vector2f(96, 96), standingTextures[north], standingTextures[east], standingTextures[south], standingTextures[west], standingTextures[northwest], standingTextures[northeast], standingTextures[southeast], standingTextures[southwest]);
    runningAnimation.loadAnimations(.04, true, 8, sf::Vector2f(96, 96), runningTextures[north], runningTextures[east], runningTextures[south], runningTextures[west], runningTextures[northwest], runningTextures[northeast], runningTextures[southeast], runningTextures[southwest]);
    attackAnimation.loadAnimations(.04, true, 9, sf::Vector2f(96, 96), attackingTextures[north], attackingTextures[east], attackingTextures[south], attackingTextures[west], attackingTextures[northwest], attackingTextures[northeast], attackingTextures[southeast], attackingTextures[southwest]);
*/
}

void Wolf::handleEvents()
{
    while(!events.isEventListEmpty())
        {
            //Get the next event
            int type = events.getNextEventType();
            int value = events.getNextEventValue();
            std::string args = events.getNextEventArgs();

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
sf::Vector2f Wolf::getEntityOrigin()
{
    return sf::Vector2f(sprite.getPosition().x + 47, sprite.getPosition().y + 56);
}

void Wolf::draw(sf::RenderWindow& window)
{

    window.draw(sprite);

    if(boundingBoxVisible)
        window.draw(visibleBoundingBox);
}
