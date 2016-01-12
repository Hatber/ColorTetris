#ifndef COLORTETRIS_COLORTETRIS_H
#define COLORTETRIS_COLORTETRIS_H

#include "Engine/Figure.h"
#include "Engine/Board.h"

namespace gct {

class ColorTetris {
public:
    ColorTetris(int colorCount, int xSize, int ySize);

    void GenerateNewFigure();
    void DropFigure();
    void RemoveMonochromeRegion();
    void Gravity();

    bool SetNewFigureIsPosible();
    bool DropFigureIsPosible();
    bool GravityIsNeeded();

//private:
    int getCenterXBoard();
    void renewFigurePosition();
    void fixFigure();

    int _colorCount;
    Figure currentFigure, nextFigure;
    Board _board;

    int score;
    rll::Point figurePosition;

    friend class Render;
};

} // gct

#endif //COLORTETRIS_COLORTETRIS_H
