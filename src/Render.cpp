#include <string>

#include "Render.h"
#include "rll/BorderDrafter.hpp"

using namespace gct;

Render::Render(ColorTetris &ct) : _ct(ct) {
    TCODSystem::setFps(60);
    TCODConsole::root->setCustomFont("terminal.png", TCOD_FONT_LAYOUT_ASCII_INROW);

    int boardXSize = _ct._board.getXSize();
    int boardYSize = _ct._board.getYSize();

    TCODConsole::initRoot(boardXSize + 2 + 6, boardYSize + 1, "Color Tetris");

    glassWindow = new TCODConsole(boardXSize, boardYSize);
    scoreWindow = new TCODConsole(5, 2);
    levelWindow = new TCODConsole(5, 2);
    nextFigureWindow = new TCODConsole(5, 5);
}

Render::~Render() {
    delete glassWindow;
    delete nextFigureWindow;
    delete scoreWindow;
    delete levelWindow;
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
    showLevel();
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
    scoreWindow->print(0, 0, "Score");
    scoreWindow->print((5-strScore.size())/2, 1, strScore.c_str());

    TCODConsole::blit(scoreWindow, 0, 0, 5, 2, TCODConsole::root, b.getXSize()+2, 1);
}

void Render::showNextFigure() const {
    rll::BorderDrafter drafter;
    drafter.DrawPassiveBorder(0, 5, 0, 5,nextFigureWindow);

    const Board &b = _ct._board;

    rll::Color c;

    c = colors.getColorByIndex(_ct.nextFigure.colors[1]);
    nextFigureWindow->putCharEx(2, 2, cellSymbol,
                           TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    c = colors.getColorByIndex(_ct.nextFigure.colors[0]);
    nextFigureWindow->putCharEx(2, 1, cellSymbol,
                           TCODColor::black, TCODColor(c.r(), c.g(), c.b()));
    c = colors.getColorByIndex(_ct.nextFigure.colors[2]);
    nextFigureWindow->putCharEx(2, 3, cellSymbol,
                           TCODColor::black, TCODColor(c.r(), c.g(), c.b()));

    TCODConsole::blit(nextFigureWindow, 0, 0, 5, 5, TCODConsole::root, b.getXSize()+2, 1 + 2 + 1);
}

void Render::showStartMessege() {
    int rootXSize = TCODConsole::root->getWidth();
    int rootYSize = TCODConsole::root->getHeight();

    TCODConsole startWindow(rootXSize - 4, rootYSize - 4);


    rll::BorderDrafter drafter;
    drafter.DrawPassiveBorder(&startWindow);

    int printPosition = 1;

    startWindow.print(2, printPosition++, "Welcome to");
    startWindow.print(1 , printPosition++, "Color Tetris");
    startWindow.hline(1, printPosition++, rootXSize - 6);

    startWindow.print(2, printPosition++, "Control:");
    printPosition++;

    startWindow.putChar(1, printPosition, TCOD_CHAR_ARROW_E);
    startWindow.putChar(2, printPosition, TCOD_CHAR_ARROW_W);
    startWindow.print(3, printPosition++, " - Move");

    startWindow.putChar(1, printPosition, TCOD_CHAR_ARROW_N);
    startWindow.print(2, printPosition++, " - Colors");

    startWindow.putChar(1, printPosition, TCOD_CHAR_ARROW_S);
    startWindow.print(2, printPosition++, " - Drop");

    printPosition++;
    startWindow.print(1, printPosition++, "SPACE-Rotate");

    startWindow.hline(1, startWindow.getHeight()-4, startWindow.getWidth()-2);
    startWindow.print(1, startWindow.getHeight()-3, " Press ANY");
    startWindow.print(1, startWindow.getHeight()-2, "key to start");

    TCODConsole::blit(&startWindow, 0, 0, rootXSize - 4, rootYSize - 4, TCODConsole::root, 2, 2);

    TCODConsole::flush();
}

void Render::showLevel() const {
    const Board &b = _ct._board;

    std::string levelNumber = std::to_string(_ct.calcDifficultyLevel());
    levelWindow->print(0, 0, "Level");
    levelWindow->print((5-levelNumber.size())/2, 1, levelNumber.c_str());

    TCODConsole::blit(levelWindow, 0, 0, 5, 2, TCODConsole::root, b.getXSize()+2, 1 + 2 + 1 + 5 + 1);
}

void Render::showEndMessege() {
    //Congratulation! You lose!
    int rootXSize = TCODConsole::root->getWidth();
    int rootYSize = TCODConsole::root->getHeight();

    int endWindowXSize = 17;
    int endWindowYSize = 4;
    TCODConsole endWindow(endWindowXSize, endWindowYSize);


    rll::BorderDrafter drafter;
    drafter.DrawPassiveBorder(&endWindow);

    endWindow.print(1, 1, "Congratulation!");
    endWindow.print(1, 2, "   You lose!");

    TCODConsole::blit(&endWindow, 0, 0, endWindowXSize, endWindowYSize, TCODConsole::root,
                      (rootXSize -endWindowXSize)/2, (rootYSize -endWindowYSize)/2);

    TCODConsole::flush();
}
