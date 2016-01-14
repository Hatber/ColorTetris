#ifndef COLORTETRIS_RENDER_H
#define COLORTETRIS_RENDER_H

#include "rll/ColorSet.hpp"
#include "Engine/ColorTetris.h"

#include "libtcod.hpp"

namespace gct {

class Render {
    const char cellSymbol = 0x8;

public:
    Render(ColorTetris &ct) : _ct(ct) {
        TCODSystem::setFps(10);
        TCODConsole::root->setCustomFont("terminal.png", TCOD_FONT_LAYOUT_ASCII_INROW);
        TCODConsole::initRoot(_ct._board.getXSize(), _ct._board.getYSize(), "Color Tetris");
    }

    void show() const;
    void showField() const;
    void showFigure() const;

private:
    const ColorTetris& _ct;
    rll::ColorSet colors;
};

} // gct

#endif //COLORTETRIS_RENDER_H
