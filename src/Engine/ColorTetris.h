#ifndef COLORTETRIS_COLORTETRIS_H
#define COLORTETRIS_COLORTETRIS_H

#include "Engine/Figure.h"
#include "Engine/Board.h"

namespace gct {

class ColorTetris {
public:
    ColorTetris(int colorCount, int xSize, int ySize);

    void generateNewFigure();
    void dropFigure();
    void fixFigure();
    void removeMonochromeRegion();
    void gravity();

    bool setNewFigureIsPosible();
    bool dropFigureIsPosible();
    bool gravityIsNeeded();

    void moveRight();
    void moveLeft();
    void rotate();
    void transposeForward();
    void transposeBackward();


private:
    int getCenterXBoard();
    void renewFigurePosition();
    bool isMoved(rll::Point way);

    bool isOverlap(rll::Point coordinate, bool isVertical);
    bool figureCoordinateInBorders(rll::Point coordinate);

    int _colorCount;
    Figure currentFigure, nextFigure;
    Board _board;

    int score;
    rll::Point figurePosition;

    friend class Render;
};

} // gct

#endif //COLORTETRIS_COLORTETRIS_H
