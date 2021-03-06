#ifndef COLORTETRIS_FIGURE_H
#define COLORTETRIS_FIGURE_H

#include <cstdlib> // rand
#include <utility> // swap

namespace gct {

    struct Figure {
        Figure(int maxColors) {
            isVertical = false;

            colors[0] = rand()%maxColors;
            colors[1] = rand()%maxColors;
            colors[2] = rand()%maxColors;
        }

        void rotate() {
            isVertical = !isVertical;
        }

        void transposeForward() {
            std::swap(colors[0], colors[2]);
            std::swap(colors[1], colors[2]);
        }
        void transposeBackward() {
            std::swap(colors[1], colors[2]);
            std::swap(colors[0], colors[2]);
        }

        int operator [] (int elementNum) const { return colors[elementNum]; }

        bool isVertical;
        int colors[3];
    };

} // gct

#endif //COLORTETRIS_FIGURE_H
