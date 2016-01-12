#ifndef COLORTETRIS_RENDER_H
#define COLORTETRIS_RENDER_H

#include "Engine/ColorTetris.h"

#include <iostream>
using std::cout;
using std::endl;

namespace gct {

class Render {
public:
    Render(ColorTetris &ct) : _ct(ct) { }

    void show() const {
        const rll::Area &b = _ct._board;
        for (int y = 0; y < _ct._board.getYSize(); y++) {
            for (int x = 0; x < _ct._board.getXSize(); x++) {
                cout.width(2);
                cout << _ct._board.getElement(x, y);
            }
            cout << endl;
        }
        cout << "Current Figure: " << _ct.currentFigure.colors[0]
             << " " << _ct.currentFigure.colors[1]
             << " " << _ct.currentFigure.colors[2] <<endl;
        cout << endl;
    }

private:
    const ColorTetris& _ct;
};

} // gct

#endif //COLORTETRIS_RENDER_H
