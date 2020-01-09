#include "characterdata.h"
#include <cmath>
#include <sstream>
#include <iostream>

CharacterData::CharacterData()
{
    maxHealth = 100;
    maxMagic = 100;
    maxStrength = 10;
    maxDexterity = 10;
    maxIntelligence = 10;
    maxDefense = 50;
    maxVitality = 10;
    maxLightRadius = 5;
    maxSpeed = 100;

    runSpeed = maxSpeed;
    walkSpeed = runSpeed / 1.5;
    resetStats();

    experience = 0;
    level = 1;
    experienceNeeded = determineExpNeeded(level);
    direction = 0;
    pos.x = 100;
    pos.y = 100;

    specialization = Stats::Unspecified;
    classType = ClassType::Unknown;
    name = "Unknown";


}

CharacterData::CharacterData(const std::string& charName, int mStrength, int mDexterity, int mintelligence, int mDefense, int mVitality, int mFocus, int mLightRad, int mSpeed, int mLevel, int mClassType)
{
   if(mStrength > 0)
        maxStrength = mStrength;
    else
        maxStrength = 10;

    if(mDexterity > 0)
        maxDexterity = mDexterity;
    else
        maxDexterity = 10;

    if(mintelligence > 0)
        maxIntelligence = mintelligence;
    else
        maxIntelligence = 10;

    if(mDefense > 0)
        maxDefense = mDefense;
    else
        maxDefense = 50;

    if(mVitality > 0)
        setMaxVitality(mVitality);
    else
        maxVitality = 10;

    if(mFocus > 0)
        setMaxFocus(mFocus);
    else
        maxFocus = 10;

    if(mLightRad > 0)
        maxLightRadius = mLightRad;
    else
        maxLightRadius = 5;

    if(mSpeed > 0)
        maxSpeed = mSpeed;
    else
        maxSpeed = 100;

    runSpeed = maxSpeed;
    walkSpeed = runSpeed / 1.5;

    experience = 0;

    level = mLevel;

    experienceNeeded = determineExpNeeded(level);
    experience = 0;

    classType = mClassType;

    alive = true;

    name = charName;

    resetStats();
}

void CharacterData::setUpCharacter(const std::string& charName, int mStrength, int mDexterity, int mintelligence, int mDefense, int mVitality, int mFocus, int mLightRad, int mSpeed, int mLevel, int mClassType)
{

    if(mStrength > 0)
        maxStrength = mStrength;
    else
        maxStrength = 10;

    if(mDexterity > 0)
        maxDexterity = mDexterity;
    else
        maxDexterity = 10;

    if(mintelligence > 0)
        maxIntelligence = mintelligence;
    else
        maxIntelligence = 10;

    if(mDefense > 0)
        maxDefense = mDefense;
    else
        maxDefense = 50;

    if(mVitality > 0)
        setMaxVitality(mVitality);
    else
        maxVitality = 10;

    if(mFocus > 0)
        setMaxFocus(mFocus);
    else
        maxFocus = 10;

    if(mLightRad > 0)
        maxLightRadius = mLightRad;
    else
        maxLightRadius = 5;

    if(mSpeed > 0)
        setMaxSpeed(mSpeed);
    else
        maxSpeed = 25;
    runSpeed = maxSpeed;
    walkSpeed = runSpeed / 1.5;

    experience = 0;

    level = mLevel;

    experienceNeeded = determineExpNeeded(level);
    experience = 0;

    alive = true;

    classType = mClassType;

    name = charName;

    resetStats();
}

CharacterData::~CharacterData()
{
    //dtor
}

///Positive for max value / Zero or Negative for current value
int CharacterData::retrieveValue(int current_Max, const std::string& stat) const
{
    int value = 0;

    if(current_Max > 0)
    {
        if(stat == "Health")
            value = maxHealth;
        else if(stat == "Magic")
            value = maxMagic;
        else if(stat == "Strength")
            value = maxStrength;
        else if(stat == "Experience")
            value = experienceNeeded;
        else if(stat == "Level")
            value = level;
        else if(stat == "Dexterity")
            value = maxDexterity;
        else if(stat == "Intelligence")
            value = maxIntelligence;
        else if(stat == "Speed")
            value = maxSpeed;
        else if(stat == "Defense")
            value = maxDefense;
        else if(stat == "Focus")
            value = maxFocus;
        else if(stat == "Vitality")
            value = maxVitality;
        else if(stat == "Light Radius")
            value = maxLightRadius;
    }
    else
    {
        if(stat == "Health")
            value = health;
        else if(stat == "Magic")
            value = magic;
        else if(stat == "Strength")
            value = strength;
        else if(stat == "Experience")
            value = experience;
        else if(stat == "Level")
            value = level;
        else if(stat == "Dexterity")
            value = dexterity;
        else if(stat == "Intelligence")
            value = intelligence;
        else if(stat == "Speed")
            value = speed;
        else if(stat == "Defense")
            value = defense;
        else if(stat == "Focus")
            value = focus;
        else if(stat == "Vitality")
            value = vitality;
        else if(stat == "Light Radius")
            value = lightRadius;
    }

    return value;
}

void CharacterData::copyCharacterData(CharacterData& other)
{
    name = other.name;
    maxHealth = other.maxHealth;
    maxMagic = other.maxMagic;
    maxStrength = other.maxStrength;
    maxDexterity = other.maxDexterity;
    maxIntelligence = other.maxIntelligence;
    maxDefense = other.maxDefense;
    maxVitality = other.maxVitality;
    maxFocus = other.maxFocus;
    maxLightRadius = other.maxLightRadius;
    maxSpeed = other.maxSpeed;
    level = other.level;
    alive = other.alive;

    classType = other.classType;

    resetStats();
}

void CharacterData::loadCharacterData(std::string dir)
{
    std::ifstream in;
    std::string minValue;
    std::string maxValue;
    std::string directory(dir);
    std::string category;
    std::string temp;
    std::string values;

    in.open(directory);
    if(in.is_open())
    {
        //File is in the format Label: Value for name, class type, and level. Format is Label: currValue/maxValue for all others
        in >> category >> name;

        in  >> category >> pos.x;

        in  >> category >> pos.y;

        in  >> category >> direction;

        //Determine what class the character is
        in >> category >> temp;

        if(temp == "Warrior")
            classType = ClassType::Warrior;
        else if(temp == "Ranger")
            classType = ClassType::Ranger;
        else if(temp == "Thief")
            classType = ClassType::Thief;
        else if(temp == "Mage")
            classType = ClassType::Mage;
        else if(temp == "Paladin")
            classType = ClassType::Paladin;
        else if(temp == "Necromancer")
            classType = ClassType::Necromancer;
        else
            classType = ClassType::Unknown;

        determineSpecialization();

        in >> category >> values;
        level = atoi(values.c_str());
        values.clear();

        //Experience
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        values.clear();
        minValue.clear();
        maxValue.clear();
        //Convert the min and max values to a number
        experience = atoi(minValue.c_str());
        experienceNeeded = atoi(maxValue.c_str());

        //Health
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        health = atoi(minValue.c_str());
        maxHealth = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Magic
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        magic = atoi(minValue.c_str());
        maxMagic = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Strength
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        strength = atoi(minValue.c_str());
        maxStrength = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Dexterity
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        dexterity = atoi(minValue.c_str());
        maxDexterity = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Intelligence
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        intelligence = atoi(minValue.c_str());
        maxIntelligence = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Defense
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        defense = atoi(minValue.c_str());
        maxDefense = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Light Radius
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        lightRadius = atoi(minValue.c_str());
        maxLightRadius = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Speed
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        speed = atoi(minValue.c_str());
        maxSpeed = atoi(maxValue.c_str());
        runSpeed = maxSpeed;
        walkSpeed = runSpeed / 1.5;
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Vitality
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        vitality = atoi(minValue.c_str());
        maxVitality = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        //Focus
        //Read in the combined values
        in >> category >> values;
        separateValues('/', values, minValue, maxValue);
        //Convert the min and max values to a number
        focus = atoi(minValue.c_str());
        maxFocus = atoi(maxValue.c_str());
        values.clear();
        minValue.clear();
        maxValue.clear();

        experienceNeeded = determineExpNeeded(level);
        alive = true;

        in.close();
    }
    else
    {
        std::cout << "Could not open " << dir << " Exiting program.\n";
        exit(301);
    }
}


//The directory should end with the folder to be saved in. The file saved will be named the same as the name of the character
std::string CharacterData::saveCharacterData(std::string dir)
{
    std::ofstream out;
    std::string directory(dir);
   // directory += "/" + name + ".txt";
    out.open(directory);
    if(out.is_open())
    {
        out << "Name: " << name;
        out << "\nX-Pos: " << pos.x;
        out << "\nY-Pos: " << pos.y;
        out << "\nDirection: " << direction;
        out << getStatsAsString();

        out.close();
    }
    else
    {
        std::cout << "Could not save character data to " << dir << " Exiting program.\n";
        exit(300);
    }

    return directory;
}

void CharacterData::separateValues(char separator, std::string& combinedValues, std::string& minValue, std::string& maxValue)
{
    int separatorIndex = 0;

    //Create a substring from the beginning to the / and the / to the end
    separatorIndex = combinedValues.find('/');
    minValue = combinedValues.substr(0, separatorIndex);
    maxValue = combinedValues.substr(separatorIndex + 1);
    //std::cout << "Min value: " << minValue <<std::endl;
    //std::cout << "Max value: " << maxValue <<std::endl;
}


void CharacterData::modifyHealth(int amount)
{
    health += amount;

    if (health < 0)
    {
        health = 0;
        alive = false;
    }
    if (health > maxHealth)
        health = maxHealth;
}

void CharacterData::modifyMagic(int amount)
{
    magic += amount;

    if (magic < 0)
        magic = 0;
    if (magic > maxMagic)
        magic = maxMagic;
}

void CharacterData::modifyStrength(int amount)
{
    strength += amount;

    if (strength < 0)
        strength = 0;
    if (strength > maxStrength)
        strength = maxStrength;
}

void CharacterData::modifyDexterity(int amount)
{
    dexterity += amount;

    if (dexterity < 0)
        dexterity = 0;
    if (dexterity > maxDexterity)
        dexterity = maxDexterity;
}

void CharacterData::modifyIntelligence(int amount)
{
    intelligence += amount;

    if (intelligence < 0)
        intelligence = 0;
    if (intelligence > maxIntelligence)
        intelligence = maxIntelligence;
}

void CharacterData::modifyDefense(int amount)
{
    defense += amount;

    if (defense < 0)
        defense = 0;
    if (defense > maxDefense)
        defense = maxDefense;
}

void CharacterData::modifyVitality(int amount)
{
    vitality += amount;

    if (vitality < 1)
        vitality = 1;
    if (vitality > maxVitality)
        vitality = maxVitality;
}

void CharacterData::modifyFocus(int amount)
{
    focus += amount;

    if (focus < 1)
        focus = 1;
    if (focus > maxFocus)
        focus = maxFocus;
}

void CharacterData::modifyLightRadius(int amount)
{
    lightRadius += amount;

    if (lightRadius < 0)
        lightRadius = 0;
    if (lightRadius > maxLightRadius)
        lightRadius = maxLightRadius;
}

void CharacterData::modifySpeed(int amount)
{
    speed += amount;
    runSpeed = speed;
    walkSpeed = runSpeed / 1.5;
    if(speed < 0)
    {
        speed = 0;
        runSpeed = 0;
        walkSpeed = 0;
    }
    if(speed > maxSpeed)
        speed = maxSpeed;


}

void CharacterData::setMaxHealth(int mHealth)
{
    if(mHealth > 0)
    {
        maxHealth = mHealth;
        alive = true;
    }
    health = maxHealth;
}

void CharacterData::setMaxMagic(int mMagic)
{
    if(mMagic > 0)
        maxMagic = mMagic;
    magic = maxMagic;
}

void CharacterData::setMaxStrength(int mStrength)
{
    if(mStrength > 0)
        maxStrength = mStrength;
    strength = maxStrength;
}

void CharacterData::setMaxDexterity(int mDexterity)
{
    if(mDexterity > 0)
        maxDexterity = mDexterity;
    dexterity = maxDexterity;
}


void CharacterData::setmaxIntelligence(int mIntelligence)
{
    if(mIntelligence > 0)
        maxIntelligence = mIntelligence;
    intelligence = maxIntelligence;
}

void CharacterData::setMaxDefense(int mDefense)
{
    if(mDefense > 0)
        maxDefense = mDefense;
    defense = maxDefense;
}

void CharacterData::setMaxVitality(int mVitality)
{
    if(mVitality > 0)
        maxVitality = mVitality;
    vitality = maxVitality;

    maxHealth = vitality + log(vitality * 100000);
}

void CharacterData::setMaxFocus(int mFocus)
{
    if(mFocus > 0)
        maxFocus = mFocus;
    focus = maxFocus;

    maxMagic = focus + log(focus * 100000);
}

void CharacterData::setMaxLightRadius(int mLightRad)
{
    if(mLightRad > 0)
        maxLightRadius = mLightRad;
    lightRadius = maxLightRadius;
}

void CharacterData::setMaxSpeed(int mSpeed)
{
    if(mSpeed > 0)
    {
        maxSpeed = mSpeed;
        speed = maxSpeed;
    }
}

void CharacterData::setName(const std::string& charName)
{
    name = charName;
}

int CharacterData::determineExpNeeded(int mLevel)
{
    int expNeeded = -1;

    if(mLevel > 0)
        expNeeded = mLevel * log(50000 * mLevel) / .108;

    return expNeeded;
}

void CharacterData::addExperience(int amount)
{
    if(amount > 0)
    {
        experience += amount;

        if(experience >= experienceNeeded)
            levelUp();
    }
}

void CharacterData::levelUp()
{
    resetStats();

    while(experience >= experienceNeeded)
    {
        level++;
        experience -= experienceNeeded;

        if(specialization == Stats::Strength)
        {
            maxStrength += 5;
            maxDexterity += 2;
            maxIntelligence += 2;
            defense += 10;
            vitality += 5;
            focus += 3;
        }

        else if(specialization == Stats::Dexterity)
        {
            maxStrength += 2;
            maxDexterity += 5;
            maxIntelligence += 2;
            defense += 8;
            vitality += 4;
            focus += 3;
        }

        else if(specialization == Stats::Intelligence)
        {
            maxStrength += 2;
            maxDexterity += 2;
            maxIntelligence += 5;
            defense += 7;
            vitality += 3;
            focus += 5;
        }

        else
        {
            maxStrength += 2;
            maxDexterity += 2;
            maxIntelligence += 2;
            defense += 6;
            vitality += 2;
            focus += 2;
        }

    }

    maxHealth += log(vitality * 100000);
    maxMagic += log(focus * 100000);
    resetStats();
}

void CharacterData::setPos(sf::Vector2f position)
{
    pos.x = position.x;
    pos.y = position.y;
   // std::cout << pos.x << ", " << pos.y << std::endl;
}

sf::Vector2f CharacterData::getPos()
{
    return pos;
}

void CharacterData::setDirection(int dir)
{
    if(dir >= 0 && dir <= 7)
        direction = dir;
}

int CharacterData::getDirection()
{
    return direction;
}


void CharacterData::resetStats()
{
    health = maxHealth;
    magic = maxMagic;
    strength = maxStrength;
    dexterity = maxDexterity;
    intelligence = maxIntelligence;
    defense = maxDefense;
    lightRadius = maxLightRadius;
    speed = maxSpeed;

    determineSpecialization();
}

void CharacterData::determineSpecialization()
{
    if(classType == ClassType::Warrior || classType == ClassType::Paladin)
        specialization = Stats::Strength;
    else if(classType == ClassType::Ranger || classType == ClassType::Thief)
        specialization = Stats::Dexterity;
    else if(classType == ClassType::Mage || classType == ClassType::Necromancer)
        specialization = Stats::Intelligence;
    else
        specialization = Stats::Unspecified;
}

std::string CharacterData::getStatsAsString()
{
    std::ostringstream temp;
    std::string stats("");

    if(classType == ClassType::Warrior)
        stats += "\nClass: Warrior ";
    else if(classType == ClassType::Ranger)
        stats += "\nClass: Ranger ";
    else if(classType == ClassType::Thief)
        stats += "\nClass: Thief ";
    else if(classType == ClassType::Mage)
        stats += "\nClass: Mage ";
    else if(classType == ClassType::Paladin)
        stats += "\nClass: Paladin ";
    else if(classType == ClassType::Necromancer)
        stats += "\nClass: Necromancer ";
    else
        stats += "\nClass: Unspecified ";

    stats += "\nLevel: ";
    temp << level;
    stats += temp.str();
    temp.str(std::string());

    stats += "\nExperience: ";
    temp << experience << "/" << experienceNeeded;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nHealth: ";
    temp << health << "/" << maxHealth;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nMagic: ";
    temp << magic << "/" << maxMagic;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nStrength: ";
    temp << strength << "/" << maxStrength;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nDexterity: ";
    temp << dexterity << "/" << maxDexterity;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nIntelligence: ";
    temp << intelligence << "/" << maxIntelligence;
    stats += temp.str();
    temp.str(std::string());

    stats += "\nDefense: ";
    temp << defense << "/" << maxDefense;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nLight-Radius: ";
    temp << lightRadius << "/" << maxLightRadius;
    stats += temp.str();
    temp.str(std::string());

    stats += "\nSpeed: ";
    temp << speed << "/" << maxSpeed;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nVitality: ";
    temp << vitality << "/" << maxVitality;
    stats += temp.str();
    temp.str(std::string());

    stats+= "\nFocus: ";
    temp << focus << "/" << maxFocus;
    stats += temp.str();
    temp.str(std::string());

    stats += "\nMain Stat: ";
    if (specialization == Stats::Strength)
        temp << "Strength\n";
    else if(specialization == Stats::Dexterity)
        temp << "Dexterity\n";
    else if(specialization == Stats::Intelligence)
        temp << "Intelligence\n";
    else
        temp << "Unspecified\n";
    stats += temp.str();
    temp.str(std::string());

    return stats;

}

void CharacterData::debugPrintData()
{
    std::cout << "Current Health: " << health << std::endl;
    std::cout << "Max Health: " << maxHealth << std::endl;

    std::cout << "Current Magic: " << magic << std::endl;
    std::cout << "Max Magic: " << maxMagic << std::endl;

    std::cout << "Current Strength: " << strength << std::endl;
    std::cout << "Max Strength: " << maxStrength << std::endl;

    std::cout << "Current Dexterity: " << dexterity << std::endl;
    std::cout << "Max Dexterity: " << maxDexterity << std::endl;

    std::cout << "Current intelligence: " << intelligence << std::endl;
    std::cout << "Max intelligence: " << maxIntelligence << std::endl;

    std::cout << "Current Vitality: " << vitality << std::endl;
    std::cout << "Max Vitality: " << maxVitality << std::endl;

    std::cout << "Current Focus: " << focus << std::endl;
    std::cout << "Max Focus: " << maxFocus << std::endl;

}
