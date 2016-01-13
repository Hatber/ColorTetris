#include "ColorTetris.h"

gct::ColorTetris::ColorTetris(int colorCount, int xSize, int ySize) :
        _colorCount(colorCount),
        currentFigure(Figure(colorCount)), nextFigure(Figure(colorCount)),
        _board(xSize, ySize), score(0)
{
    renewFigurePosition();
}

void gct::ColorTetris::generateNewFigure() {
    currentFigure = nextFigure;
    nextFigure = Figure(_colorCount);

    renewFigurePosition();
}

void gct::ColorTetris::dropFigure() {
        figurePosition.y() += 1;
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

void gct::ColorTetris::removeMonochromeRegion() {

}

void gct::ColorTetris::gravity() {
    for(int y = _board.getYSize()-2; y>=0; y--) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(_board.freeSpace(x, y+1)) {
                std::swap(_board.at(x, y), _board.at(x, y+1));
            }
        }
    }
}


bool gct::ColorTetris::setNewFigureIsPosible() {
    int borderXCenterPoint = getCenterXBoard();

    return
        _board.freeSpace(borderXCenterPoint, 0) &&
        _board.freeSpace(borderXCenterPoint, 1) &&
        _board.freeSpace(borderXCenterPoint, 2);
}

bool gct::ColorTetris::dropFigureIsPosible() {
    if(!figureCoordinateInBorders(figurePosition.shift(0, 1))) { return false; }

    bool spaceUnderFigureIsFree;
    if(currentFigure.isVertical) {
        spaceUnderFigureIsFree = _board.freeSpace(figurePosition.shift(0, 2));
    } else {

        spaceUnderFigureIsFree =
            _board.freeSpace(figurePosition.shift(-1, 1)) &&
            _board.freeSpace(figurePosition.shift( 0, 1)) &&
            _board.freeSpace(figurePosition.shift( 1, 1));
    }

    return spaceUnderFigureIsFree;
}

bool gct::ColorTetris::gravityIsNeeded() {
    for(int y = _board.getYSize()-2; y>=0; y--) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(!_board.freeSpace(x, y) && _board.freeSpace(x, y+1)) {
                return true;
            }
        }
    }
    return false;
}


void gct::ColorTetris::moveRight() {
    rll::Point moveWay(1, 0);
    if(isMoved(moveWay)){
        figurePosition = figurePosition.shift(moveWay);
    }
}
void gct::ColorTetris::moveLeft() {
    rll::Point moveWay(-1, 0);
    if(isMoved(moveWay)){
        figurePosition = figurePosition.shift(moveWay);
    }
}

void gct::ColorTetris::rotate() {
    if(figurePosition.x() != 0 &&
       figurePosition.x() != _board.getXSize()-1 &&
       figurePosition.y() != _board.getYSize()-1 &&
       !isOverlap(figurePosition, !currentFigure.isVertical)
       ) {
          currentFigure.rotate();
    }
}

void gct::ColorTetris::transposeForward()  { currentFigure.transposeForward(); }
void gct::ColorTetris::transposeBackward() { currentFigure.transposeBackward(); }


int gct::ColorTetris::getCenterXBoard() {
    return _board.getXSize()/2;
}

void gct::ColorTetris::renewFigurePosition() {
    figurePosition = rll::Point::makePoint(getCenterXBoard(), 1);
}

bool gct::ColorTetris::isMoved(rll::Point way) {
    if(!figureCoordinateInBorders(figurePosition.shift(way))) { return false; }
    if(isOverlap(figurePosition.shift(way), currentFigure.isVertical)) { return false; }

    return true;
}

bool gct::ColorTetris::figureCoordinateInBorders(rll::Point coordinate) {
    bool figureInBorders;
    if(currentFigure.isVertical) {
        figureInBorders  =  _board.getYSize() - 1 != coordinate.y();
        figureInBorders &= coordinate.x() != -1;
        figureInBorders &= coordinate.x() != _board.getXSize();
    } else {
        figureInBorders = _board.getYSize() != coordinate.y();
        figureInBorders &= coordinate.x() != 0;
        figureInBorders &= coordinate.x() != _board.getXSize() - 1;
    }

    return figureInBorders;
}

bool gct::ColorTetris::isOverlap(rll::Point coordinate, bool isVertical) {
    bool overlap;

    overlap = !_board.freeSpace(coordinate);
    if(isVertical) {
        overlap |= !_board.freeSpace(coordinate.shift(0, -1));
        overlap |= !_board.freeSpace(coordinate.shift(0,  1));
    } else {
        overlap |= !_board.freeSpace(coordinate.shift(-1, 0));
        overlap |= !_board.freeSpace(coordinate.shift( 1, 0));
    }

    return overlap;
}
