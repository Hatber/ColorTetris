#ifndef COLORTETRIS_AGAMEBOT_HPP
#define COLORTETRIS_AGAMEBOT_HPP

#include <iostream>

#include "libtcod.hpp"
#include "Engine/ColorTetris.h"

namespace gct {

    class AGameBot {
    public:
        AGameBot(const ColorTetris& ct) : game(ct), timeForStep(0.5), elapsedTime(0) { }

        virtual void findWay() = 0;

        TCOD_keycode_t getAction() {
            if(!nextActionIsPrepared()) { return TCODK_NONE; }
            if(way.size() == 0) { return TCODK_NONE; }

            TCOD_keycode_t code = way.back();
            way.pop_back();
            std::cout << way.size() << std::endl;
            return code;
        }

    protected:
        bool nextActionIsPrepared() {
            elapsedTime += TCODSystem::getLastFrameLength();
            if(elapsedTime - timeForStep < 0) { return false; }
            else {
                elapsedTime = 0;
                return true;
            }
        }

        const ColorTetris& game;
        float timeForStep;
        float elapsedTime;
        vector< TCOD_keycode_t > way;
    };

}

#endif //COLORTETRIS_AGAMEBOT_HPP
