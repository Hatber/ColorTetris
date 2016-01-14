#include "Render.h"

void gct::Render::show() const {
    showField();
    if(!_ct.figureIsFixed) { showFigure(); }

    TCODConsole::root->flush();
}

void gct::Render::showField() const {
    const Board &b = _ct._board;
    rll::Color c;

    for (int y = 0; y < _ct._board.getYSize(); y++) {
        for (int x = 0; x < _ct._board.getXSize(); x++) {
            if(b.freeSpace(x, y)) {
                TCODConsole::root->putCharEx(x, y, ' ', TCODColor::black, TCODColor::black);
            } else {
                c = colors.getColorByIndex(b.getElement(x, y));
                TCODConsole::root->putCharEx(x, y, cellSymbol,
                                             TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
            }
        }
    }
}

void gct::Render::showFigure() const {
    int x = _ct.figurePosition.x();
    int y = _ct.figurePosition.y();

    rll::Color c;

    c = colors.getColorByIndex(_ct.currentFigure.colors[1]);
    TCODConsole::root->putCharEx(x, y, cellSymbol,
                                 TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    if(_ct.currentFigure.isVertical) {
        c = colors.getColorByIndex(_ct.currentFigure.colors[0]);
        TCODConsole::root->putCharEx(x, y-1, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
        c = colors.getColorByIndex(_ct.currentFigure.colors[2]);
        TCODConsole::root->putCharEx(x, y+1, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    } else {
        c = colors.getColorByIndex(_ct.currentFigure.colors[0]);
        TCODConsole::root->putCharEx(x-1, y, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
        c = colors.getColorByIndex(_ct.currentFigure.colors[2]);
        TCODConsole::root->putCharEx(x+1, y, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    }
}
