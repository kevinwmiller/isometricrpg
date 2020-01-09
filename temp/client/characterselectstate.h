#ifndef CHARACTERSELECTSTATE_H
#define CHARACTERSELECTSTATE_H

#include <fstream>
#include "state.h"
#include "textitemlist.h"
#include "menu.h"

class CharacterSelectState : public State
{
    public:
        CharacterSelectState(ResourceManager&);
        ~CharacterSelectState();

        void prepareState(std::string);
        void cleanUp();

        StateAction handleEvents();
        void update();
        void draw();

        void processChoice(int);

        void loadCharacterNames();

    private:
        std::string characterFile;
        TextItemList availableCharacters;
        //TextItemList characterStats;
        Menu menu;
        std::string currentCharacter;
        std::vector<std::string> characterNames;
};

#endif // CHARACTERSELECTSTATE_H
