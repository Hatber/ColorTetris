#ifndef COLORTETRIS_BOARD_H
#define COLORTETRIS_BOARD_H

#include "rll/TArea.hpp"

#include <vector>

namespace gct {

    using rll::Area;

    using std::vector;
    using std::size_t;

    class Board : public Area {
    public:
        Board(size_t xSize, size_t ySize) : Area(xSize, ySize) { }

    private:

    };

} //gct

#endif //COLORTETRIS_BOARD_H
