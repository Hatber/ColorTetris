#ifndef COLORTETRIS_GAMECONTROLLER_H
#define COLORTETRIS_GAMECONTROLLER_H

#include "Render.h"
#include "GameBot/GameBot.hpp"

namespace gct {

class GameController {
public:
    GameController(int colorCount, int xSize, int ySize) :
        game(colorCount, xSize, ySize),
        render(game),
        bot(game),
        timeForStep(0.1),
        elapsedTime(0)
    {
        render.show();
    }

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

    GameBot bot;

    float timeForStep;
    float elapsedTime;
};

} // gct

#endif //COLORTETRIS_GAMECONTROLLER_H
