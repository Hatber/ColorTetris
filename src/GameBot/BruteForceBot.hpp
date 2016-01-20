#ifndef COLORTETRIS_BRUTEFORCEBOT_HPP
#define COLORTETRIS_BRUTEFORCEBOT_HPP

#include "AGameBot.hpp"

namespace gct {

    class BruteForceBot : public AGameBot {
    public:
        BruteForceBot(const ColorTetris& ct) : AGameBot(ct) { }
        void findWay();

    private:
        struct bestOptions {
            rll::Point position;
            int transposeCount;
            bool isVertical;
        };

        void constructWay(const bestOptions& opt);
    };

}

#endif //COLORTETRIS_BRUTEFORCEBOT_HPP
