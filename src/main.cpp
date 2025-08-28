#include "Game.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>

Game* gamePtr {};

void mainLoop()
{
    gamePtr->webMainLoop();
}
#endif // __EMSCRIPTEN__

int main()
{
    Game game("Arkanoid");

#ifdef __EMSCRIPTEN__
    gamePtr = &game;
    emscripten_set_main_loop(mainLoop, 0, 1);
#else
    return game.run();
#endif
}
