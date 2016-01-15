#include "Render.h"

using namespace gct;

Render::Render(ColorTetris &ct) : _ct(ct) {
    TCODSystem::setFps(10);
    TCODConsole::root->setCustomFont("terminal.png", TCOD_FONT_LAYOUT_ASCII_INROW);

    int boardXSize = _ct._board.getXSize();
    int boardYSize = _ct._board.getYSize();

    TCODConsole::initRoot(boardXSize + 2 + 6, boardYSize + 1, "Color Tetris");

    glassWindow = new TCODConsole(boardXSize, boardYSize);
    scoreWindow = new TCODConsole(5, 2);
    nextFigureWindow = new TCODConsole(3, 3);
}

Render::~Render() {
    delete glassWindow;
    delete nextFigureWindow;
    delete scoreWindow;
}


void gct::Render::show() const {
    int rootXSize = TCODConsole::root->getWidth();
    int rootYSize = TCODConsole::root->getHeight();
    for (int y = 0; y < rootYSize; y++) {
        for (int x = 0; x < rootXSize; x++) {
            TCODConsole::root->putCharEx(x, y, wallSymbol, TCODColor::black, TCODColor::white);
        }
    }

    showField();
    showScore();
    showNextFigure();

    TCODConsole::flush();
}

void gct::Render::showField() const {
    const Board &b = _ct._board;
    rll::Color c;

    for (int y = 0; y < _ct._board.getYSize(); y++) {
        for (int x = 0; x < _ct._board.getXSize(); x++) {
            if(b.freeSpace(x, y)) {
                glassWindow->putCharEx(x, y, freeCellSymbol, TCODColor::black, TCODColor::white);
            } else {
                c = colors.getColorByIndex(b.getElement(x, y));
                glassWindow->putCharEx(x, y, cellSymbol,
                                             TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
            }
        }
    }

    if(!_ct.figureIsFixed) { showFigure(); }

    TCODConsole::blit(glassWindow, 0, 0, b.getXSize(), b.getYSize(), TCODConsole::root, 1, 0);
}
void gct::Render::showFigure() const {
    int x = _ct.figurePosition.x();
    int y = _ct.figurePosition.y();

    rll::Color c;

    c = colors.getColorByIndex(_ct.currentFigure.colors[1]);
    glassWindow->putCharEx(x, y, cellSymbol,
                                 TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    if(_ct.currentFigure.isVertical) {
        c = colors.getColorByIndex(_ct.currentFigure.colors[0]);
        glassWindow->putCharEx(x, y-1, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
        c = colors.getColorByIndex(_ct.currentFigure.colors[2]);
        glassWindow->putCharEx(x, y+1, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    } else {
        c = colors.getColorByIndex(_ct.currentFigure.colors[0]);
        glassWindow->putCharEx(x-1, y, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
        c = colors.getColorByIndex(_ct.currentFigure.colors[2]);
        glassWindow->putCharEx(x+1, y, cellSymbol,
                                     TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    }
}

void gct::Render::showScore() const {
    const Board &b = _ct._board;

    std::string strScore = std::to_string(_ct.score);
    scoreWindow->print(0, 0, "Score" );
    scoreWindow->print((5-strScore.size())/2, 1, strScore.c_str());

    TCODConsole::blit(scoreWindow, 0, 0, 5, 2, TCODConsole::root, b.getXSize()+2, 1);
}

void Render::showNextFigure() const {
    const Board &b = _ct._board;

    rll::Color c;

    c = colors.getColorByIndex(_ct.nextFigure.colors[1]);
    nextFigureWindow->putCharEx(1, 1, cellSymbol,
                           TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    c = colors.getColorByIndex(_ct.nextFigure.colors[0]);
    nextFigureWindow->putCharEx(1, 0, cellSymbol,
                           TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    c = colors.getColorByIndex(_ct.nextFigure.colors[2]);
    nextFigureWindow->putCharEx(1, 2, cellSymbol,
                           TCODColor::black, TCODColor(c.r(), c.g(), c.b()));

    TCODConsole::blit(nextFigureWindow, 0, 0, 3, 3, TCODConsole::root, b.getXSize()+3, 1 + 2 + 1);
}
