#include <cmath>
#include "GameController.h"

gct::GameController::GameController(int colorCount, int xSize, int ySize) :
        game(colorCount, xSize, ySize),
        render(game),
        bot(new RandomBot(game)),
        timeForStep(0.1),
        elapsedTime(0)
{
    render.show();
    bot->findWay();
}

void gct::GameController::loop() {
    TCOD_key_t key;
    TCOD_mouse_t mouse;

    render.showStartMessege();
    waitToContinue();

    while(!TCODConsole::isWindowClosed()) {
        render.show();

        elapsedTime += TCODSystem::getLastFrameLength();
        if(elapsedTime - calcTimeForStep() > 0) {
            elapsedTime = 0;
            if(game.dropFigureIsPossible()) { game.dropFigure(); }
            else {
                processingBoard();
            }
        }

        processingInput(getBotInput());
    }
}

void gct::GameController::processingBoard() {
    render.show();

    game.fixFigure();

    do {
        while (game.gravityIsNeeded()) {
            game.gravity();
            render.show();
            TCODSystem::sleepMilli(10);
        }
    } while(game.removeMonochromeRegion());

    if(game.setNewFigureIsPossible()) {
        game.generateNewFigure();
        bot->findWay();
    } else {
        render.showEndMessege();
        waitToContinue();
    }
}

float gct::GameController::calcTimeForStep() {
    return timeForStep * std::pow(0.9, game.calcDifficultyLevel());
}

void gct::GameController::waitToContinue() {
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE_PRESS, 0, 0, true);
}

TCOD_keycode_t gct::GameController::getUserInput() {
    TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, 0);
    return key.vk;
}

TCOD_keycode_t gct::GameController::getBotInput() {
    return bot->getAction();
}

void gct::GameController::processingInput(TCOD_keycode_t inputCode) {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, 0, 0);

    switch (inputCode) {
        case TCODK_LEFT  : game.moveLeft();  break;
        case TCODK_RIGHT : game.moveRight(); break;
        case TCODK_UP    : game.transposeForward();  break;
        case TCODK_DOWN  : game.forceDropFigure(); processingBoard(); break;
        case TCODK_SPACE : game.rotate(); break;
        default          : break;
    }
}
