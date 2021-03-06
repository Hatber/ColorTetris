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
    void forceDropFigure();
    void fixFigure();
    bool removeMonochromeRegion();
    void gravity();

    bool setNewFigureIsPossible();
    bool dropFigureIsPossible();
    bool gravityIsNeeded();

    void moveRight();
    void moveLeft();
    void rotate();
    void transposeForward();
    void transposeBackward();

    int calcDifficultyLevel() const;

    //Getters
    const Board& getBoard() const { return _board; }
    const Figure& getFigure() const { return currentFigure; }
    const Figure& getNextFigure() const { return nextFigure; }
    const rll::Point& getFigurePosition() const { return figurePosition; }
    int getScore() const { return score; }
    bool isFixed() const { return figureIsFixed; }


private:
    int getCenterXBoard();
    void renewFigurePosition();
    bool isMoved(rll::Point way);

    bool isOverlap(rll::Point coordinate, bool isVertical);
    bool figureCoordinateInBorders(rll::Point coordinate);

    bool regionContainFreeSpace(const rll::Area& regions, int regionId) const;
    int  calculateRegionSize(const rll::Area &regions, int regionId) const;
    void cleanRegion(const rll::Area& regions, int regionId);

    int calcScore(int regionSize);

    int _colorCount;
    Figure currentFigure, nextFigure;
    Board _board;

    int score;
    rll::Point figurePosition;

    bool figureIsFixed;
};

} // gct

#endif //COLORTETRIS_COLORTETRIS_H
