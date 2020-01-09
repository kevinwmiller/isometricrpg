#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H

#include <SFML/Graphics.hpp>
#include <fstream>

class CharacterData
{
    public:

        enum Stats
        {
            Strength = 0,
            Dexterity,
            Intelligence,
            Unspecified
        };

        enum ClassType
        {
            Warrior = 1,
            Ranger,
            Thief,
            Mage,
            Paladin,
            Necromancer,
            Unknown,
            TotalClasses
        };

        CharacterData();
        CharacterData(const std::string&, int, int, int, int, int, int, int, int, int, int);
        ~CharacterData();

        void setUpCharacter(const std::string&, int, int, int, int, int, int, int, int, int, int);

        void copyCharacterData(CharacterData&);
        void loadCharacterData(std::string);
        std::string saveCharacterData(std::string);

        int retrieveValue(int, const std::string&) const;

        void modifyHealth(int);
        void modifyMagic(int);
        void modifyStrength(int);
        void modifyDexterity(int);
        void modifyIntelligence(int);
        void modifyDefense(int);
        void modifyVitality(int);
        void modifyFocus(int);
        void modifyLightRadius(int);
        void modifySpeed(int);

        void setName(const std::string&);
        void setMaxHealth(int);
        void setMaxMagic(int);
        void setMaxStrength(int);
        void setMaxDexterity(int);
        void setmaxIntelligence(int);
        void setMaxDefense(int);
        void setMaxVitality(int);
        void setMaxFocus(int);
        void setMaxLightRadius(int);
        void setMaxSpeed(int);

        std::string getName() const {return name;}
        int getHealth() const {return health;}
        int getMagic() const {return magic;}
        int getStrength() const {return strength;}
        int getDexterity() const {return dexterity;}
        int getintelligence() const {return intelligence;}
        int getDefense() const {return defense;}
        int getVitality() const {return vitality;}
        int getFocus() const {return focus;}
        int getLightRadius() const {return lightRadius;}
        int getSpeed() const {return speed;}
        int getRunSpeed() const {return runSpeed;}
        int getWalkSpeed() const {return walkSpeed;}
        bool isAlive() const {return alive;}

        int getMaxHealth() const {return maxHealth;}
        int getMaxMagic() const {return maxMagic;}
        int getMaxStrength() const {return maxStrength;}
        int getMaxDexterity() const {return maxDexterity;}
        int getmaxIntelligence() const {return maxIntelligence;}
        int getMaxDefense() const {return maxDefense;}
        int getMaxVitality() const {return maxVitality;}
        int getMaxFocus() const {return maxFocus;}
        int getMaxLightRadius() const {return maxLightRadius;}
        int getMaxSpeed() const {return maxSpeed;}

        int getExperience() const {return experience;}
        int getExperienceNeeded() const {return experienceNeeded;}
        int getLevel() const {return level;}

        int determineExpNeeded(int);
        void addExperience(int);
        void levelUp();

        void resetStats();

        void setPos(sf::Vector2f);
        sf::Vector2f getPos();

        void setDirection(int);
        int getDirection();


        void separateValues(char, std::string&, std::string&, std::string&);
        std::string getStatsAsString();
        void debugPrintData();

    private:

        void determineSpecialization();

        std::string name;

        int health;
        int magic;
        int strength;
        int dexterity;
        int intelligence;
        int defense;
        int vitality;
        int focus;
        int lightRadius;
        int speed;

        int maxHealth;
        int maxMagic;
        int maxStrength;
        int maxDexterity;
        int maxIntelligence;
        int maxDefense;
        int maxVitality;
        int maxFocus;
        int maxLightRadius;
        int maxSpeed;

        int runSpeed;
        int walkSpeed;

        int experience;
        int experienceNeeded;
        int level;

        sf::Vector2f pos;
        int direction;

        bool alive;

        int classType;
        int specialization;


};

#endif // CHARACTERDATA_H
