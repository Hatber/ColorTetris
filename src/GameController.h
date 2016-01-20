#ifndef COLORTETRIS_GAMECONTROLLER_H
#define COLORTETRIS_GAMECONTROLLER_H

#include <GameBot/RandomBot.hpp>
#include "Render.h"
#include "GameBot/AGameBot.hpp"

namespace gct {

class GameController {
public:
    GameController(int colorCount, int xSize, int ySize);
    void loop();

private:
    void processingBoard();
    float calcTimeForStep();

    void waitToContinue();

    TCOD_keycode_t getUserInput();
    TCOD_keycode_t getBotInput();

    void processingInput(TCOD_keycode_t inputCode);

    ColorTetris game;
    Render render;

    AGameBot* bot;

    float timeForStep;
    float elapsedTime;
};

} // gct

#endif //COLORTETRIS_GAMECONTROLLER_H
