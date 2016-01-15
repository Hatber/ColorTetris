#include <console_types.h>
#include "GameController.h"

void gct::GameController::loop() {
    TCOD_key_t key;
    TCOD_mouse_t mouse;
    while(!TCODConsole::isWindowClosed()) {
        render.show();

        elapsedTime += TCODSystem::getLastFrameLength();
        if(elapsedTime - timeForStep > 0) {
            elapsedTime -= timeForStep;
            if(game.dropFigureIsPossible()) { game.dropFigure(); }
            else {
                processingBoard();
            }
        }

        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, 0);
        switch (key.vk) {
            case TCODK_LEFT  : game.moveLeft();  break;
            case TCODK_RIGHT : game.moveRight(); break;
            case TCODK_UP    : game.transposeForward();  break;
            case TCODK_DOWN  : game.forceDropFigure(); processingBoard(); break;
            case TCODK_SPACE : game.rotate(); break;
            default          : break;
        }
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
    } else {
        // end game //TODO
        TCODSystem::sleepMilli(100000);
        //break;
    }
}
