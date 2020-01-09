
#include "statemanager.h"

std::string title("Isometric RPG v0.0.9");

int main()
{

    StateManager game(title);

    game.startGameLoop();
    return 0;
}
