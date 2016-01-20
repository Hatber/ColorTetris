#ifndef COLORTETRIS_RANDOMBOT_HPP
#define COLORTETRIS_RANDOMBOT_HPP

#include "AGameBot.hpp"

namespace gct {

    class RandomBot : public AGameBot {
    public:
        RandomBot(const ColorTetris& ct) : AGameBot(ct) { }
        void findWay();
    };

}

#endif //COLORTETRIS_RANDOMBOT_HPP
