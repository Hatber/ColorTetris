#ifndef COLORTETRIS_RENDER_H
#define COLORTETRIS_RENDER_H

#include "rll/ColorSet.hpp"
#include "Engine/ColorTetris.h"

#include "libtcod.hpp"

namespace gct {

class Render {
    const char wallSymbol = 0x0;
    const char cellSymbol = 0x1;
    const char freeCellSymbol = 0x2;

public:
    Render(ColorTetris &ct);
    ~Render();

    void show() const;

    void showField() const;
    void showFigure() const;

    void showScore() const;

    void showNextFigure() const;

private:
    const ColorTetris& _ct;
    rll::ColorSet colors;

    TCODConsole* glassWindow;
    TCODConsole* nextFigureWindow;
    TCODConsole* scoreWindow;
};

} // gct

#endif //COLORTETRIS_RENDER_H
