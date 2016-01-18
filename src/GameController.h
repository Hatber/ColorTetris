#ifndef COLORTETRIS_GAMECONTROLLER_H
#define COLORTETRIS_GAMECONTROLLER_H

#include "Render.h"

namespace gct {

class GameController {
public:
    GameController(int colorCount, int xSize, int ySize) :
        game(colorCount, xSize, ySize),
        render(game),
        timeForStep(0.5),
        elapsedTime(0)
    {
        render.show();
    }

    void loop();

private:
    void processingBoard();
    float calcTimeForStep();

    ColorTetris game;
    Render render;
    float timeForStep;

    float elapsedTime;
};

} // gct

#endif //COLORTETRIS_GAMECONTROLLER_H
