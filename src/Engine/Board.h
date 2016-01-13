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
        Board(int xSize, int ySize) : Area(xSize, ySize, -1) {

        }

        bool freeSpace(rll::Point coord) const { return freeSpace(coord.x(), coord.y()); }
        bool freeSpace(int x, int y) const { return getElement(x, y) == -1; }

    private:

    };

} //gct

#endif //COLORTETRIS_BOARD_H
