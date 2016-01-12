#include "ColorTetris.h"

gct::ColorTetris::ColorTetris(int colorCount, int xSize, int ySize) :
        _colorCount(colorCount),
        currentFigure(Figure(colorCount)), nextFigure(Figure(colorCount)),
        _board(xSize, ySize), score(0)
{
    renewFigurePosition();
}

void gct::ColorTetris::GenerateNewFigure() {
    currentFigure = nextFigure;
    nextFigure = Figure(_colorCount);

    renewFigurePosition();
}

void gct::ColorTetris::DropFigure() {
    if(DropFigureIsPosible()) {
        figurePosition.y() += 1;
    }
}

void gct::ColorTetris::RemoveMonochromeRegion() {

}

void gct::ColorTetris::Gravity() {
    for(int y = _board.getYSize()-2; y>=0; y--) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(_board.freeSpace(x, y+1)) {
                std::swap(_board.at(x, y), _board.at(x, y+1));
            }
        }
    }
}


bool gct::ColorTetris::SetNewFigureIsPosible() {
    int borderXCenterPoint = getCenterXBoard();

    return
        _board.freeSpace(borderXCenterPoint, 0) &&
        _board.freeSpace(borderXCenterPoint, 1) &&
        _board.freeSpace(borderXCenterPoint, 2);
}

bool gct::ColorTetris::DropFigureIsPosible() {
    bool spaceUnderFigureIsFree;
    bool figureInBorders;
    if(currentFigure.isVertical) {
        figureInBorders = _board.getYSize() - 2 != figurePosition.y();
        spaceUnderFigureIsFree = _board.freeSpace(figurePosition.shift(0, 2));
    } else {
        figureInBorders = _board.getYSize() - 1 != figurePosition.y();
        spaceUnderFigureIsFree =
            _board.freeSpace(figurePosition.shift(-1, 1)) &&
            _board.freeSpace(figurePosition.shift( 0, 1)) &&
            _board.freeSpace(figurePosition.shift( 1, 1));
    }

    return spaceUnderFigureIsFree && figureInBorders;
}

bool gct::ColorTetris::GravityIsNeeded() {
    for(int y = _board.getYSize()-2; y>=0; y--) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(!_board.freeSpace(x, y) && _board.freeSpace(x, y+1)) {
                return true;
            }
        }
    }
    return false;
}


int gct::ColorTetris::getCenterXBoard() {
    return _board.getXSize()/2;
}

void gct::ColorTetris::renewFigurePosition() {
    figurePosition = rll::Point::makePoint(getCenterXBoard(), 1);
}

void gct::ColorTetris::fixFigure() {
    _board.setElement(figurePosition, currentFigure.colors[1]);
    if(currentFigure.isVertical) {
        _board.setElement(figurePosition.shift(0, -1), currentFigure.colors[0]);
        _board.setElement(figurePosition.shift(0,  1), currentFigure.colors[2]);
    } else {
        _board.setElement(figurePosition.shift(-1, 0), currentFigure.colors[0]);
        _board.setElement(figurePosition.shift( 1, 0), currentFigure.colors[2]);
    }
}
