#ifndef SINGLEPLAYERSTATE_H
#define SINGLEPLAYERSTATE_H

#include "IsometricMap.h"
#include "state.h"
#include "player.h"
#include "wolf.h"
#include "hud.h"
#include "scenery.h"
#include "entitylist.h"
#include "mousecursor.h"
#include "isometricconversions.h"


class SinglePlayerState : public State
{
    public:
        SinglePlayerState(ResourceManager&);
        ~SinglePlayerState();

        void prepareState(std::string);
        void cleanUp();

        StateAction handleEvents();
        void update();
        void draw();

        void toggleZoomedOut();
        void takeScreenShot();


        //Maps for Entities. In the future, use a script to set the location of each entity/groups of entities
        void loadSceneryMap(const std::string);

        void handleInput();

    private:
        std::string playerSaveFile;
        bool hasFocus;
        sf::Clock clock;
        float elapsedTime;
        sf::View gameView;

        bool zoomedOut;

        Player* player;
        IsometricMap gameMap;

        MouseCursor* cursor;

        IsometricConversions isoConversions;

        std::vector<std::vector<int>> sceneryMap;
        EntityList entityList;
        Hud hud;

};

#endif // SINGLEPLAYERSTATE_H
