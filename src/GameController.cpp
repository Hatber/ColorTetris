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
            if(game.dropFigureIsPosible()) { game.dropFigure(); }
            else {
                game.fixFigure();

                if(game.setNewFigureIsPosible()) {
                    game.generateNewFigure();
                } else {
                    // end game //TODO
                }
            }
        }

        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, 0);
        switch (key.vk) {
            case TCODK_LEFT  : game.moveLeft();  break;
            case TCODK_RIGHT : game.moveRight(); break;
            case TCODK_UP    : game.transposeForward();  break;
            case TCODK_DOWN  : game.transposeBackward(); break;
            case TCODK_SPACE : game.rotate(); break;
            default          : break;
        }
    }
}
