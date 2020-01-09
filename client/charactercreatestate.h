#ifndef CHARACTERCREATESTATE_H
#define CHARACTERCREATESTATE_H

#include <vector>
#include <fstream>
#include "state.h"
#include "characterdata.h"
#include "inputbox.h"
#include "textitemlist.h"
#include "menu.h"
#include "button.h"


class CharacterCreateState : public State
{
    public:
        CharacterCreateState(ResourceManager&);
        ~CharacterCreateState();

        void fixNameFormat(std::string&);

        void loadCharacterNames(const std::string&);
        bool checkForExistingName(const std::string&);

        void prepareState(std::string);
        void cleanUp();

        StateAction handleEvents();
        void update();
        void draw();

        void processChoice(int);

        void saveCharacter();

    private:

        std::string characterName;

        std::vector<CharacterData> classStats;
        int currentClass;

        std::string warriorDesc;
        std::string rangerDesc;
        std::string thiefDesc;
        std::string mageDesc;
        std::string palaDesc;
        std::string necroDesc;

        //Until I fix sticky buttons in the menu class
        std::vector<Button> classButtons;
        std::vector<std::string> createdCharacterNames;

        TextItemList descriptionBox;
        TextItemList startingStats;
        InputBox nameBox;

        Menu menu;
};

#endif // CHARACTERCREATESTATE_H
