#ifndef COLORTETRIS_GAMEBOT_HPP
#define COLORTETRIS_GAMEBOT_HPP

#include "libtcod.hpp"
#include "Engine/ColorTetris.h"

namespace gct {

    class GameBot {
    public:
        GameBot(const ColorTetris& ct) : game(ct), timeForStep(0.1), elapsedTime(0) { }

        void findWay();
        void randomWay();
        TCOD_keycode_t getAction();

    private:
        std::vector< int > findOpenRegions(const Area& regions);
        std::vector< int > findRegionsWithColors(const Area& regions, int colorId);

        void filterToUnique(std::vector< int >& v);

        vector< TCOD_keycode_t > way;

        float timeForStep;
        float elapsedTime;

        const ColorTetris& game;
    };

}

#endif //COLORTETRIS_GAMEBOT_HPP
