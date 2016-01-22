#include "ColorTetris.h"
#include "rll/ConnectedRegionSearcher.hpp"

#include <iostream>
using std::cout;
using std::endl;

gct::ColorTetris::ColorTetris(int colorCount, int xSize, int ySize) :
        _colorCount(colorCount),
        currentFigure(Figure(2)), nextFigure(Figure(2)),
        _board(xSize, ySize), score(0), figureIsFixed(false)
{
    renewFigurePosition();
}

void gct::ColorTetris::generateNewFigure() {
    currentFigure = nextFigure;
    nextFigure = Figure(calcDifficultyLevel() + 2);

    renewFigurePosition();
}

void gct::ColorTetris::dropFigure() { figurePosition.y() += 1; }
void gct::ColorTetris::forceDropFigure() {
    while(dropFigureIsPossible()) { dropFigure(); }
}


void gct::ColorTetris::fixFigure() {
    _board.setElement(figurePosition, currentFigure[1]);
    if(currentFigure.isVertical) {
        _board.setElement(figurePosition.shift(0, -1), currentFigure[0]);
        _board.setElement(figurePosition.shift(0,  1), currentFigure[2]);
    } else {
        _board.setElement(figurePosition.shift(-1, 0), currentFigure[0]);
        _board.setElement(figurePosition.shift( 1, 0), currentFigure[2]);
    }

    figureIsFixed = true;
}

bool gct::ColorTetris::removeMonochromeRegion() {
    bool regionIsRemoved = false;

    rll::ConnectedRegionSearcher< int > searcher;
    rll::Area regions(searcher.search(_board));

    int regionCount = searcher.regionCount();
    for(int regionId = 0; regionId < regionCount; regionId++) {
        if(regionContainFreeSpace(regions, regionId)) { continue; }

        int regionSize = calculateRegionSize(regions, regionId);
        if(regionSize < 3) { continue; }

        score += calcScore(regionSize);
        cleanRegion(regions, regionId);

        regionIsRemoved = true;
    }

    return regionIsRemoved;
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


bool gct::ColorTetris::setNewFigureIsPossible() {
    int borderXCenterPoint = getCenterXBoard();

    return
        _board.freeSpace(borderXCenterPoint, 0) &&
        _board.freeSpace(borderXCenterPoint, 1) &&
        _board.freeSpace(borderXCenterPoint, 2);
}

bool gct::ColorTetris::dropFigureIsPossible() {
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
    figureIsFixed = false;
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


bool gct::ColorTetris::regionContainFreeSpace(const rll::Area &regions, int regionId) const {
    for(int y = 0; y < _board.getYSize(); y++) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(regions.getElement(x, y) == regionId) {
                return _board.freeSpace(x, y);
            }
        }
    }
    return false;
}

int gct::ColorTetris::calculateRegionSize(const rll::Area &regions, int regionId) const {
    int size = 0;
    for(int y = 0; y < _board.getYSize(); y++) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(regions.getElement(x, y) == regionId) {
                size++;
            }
        }
    }
    return size;
}

void gct::ColorTetris::cleanRegion(const rll::Area &regions, int regionId) {
    for(int y = 0; y < _board.getYSize(); y++) {
        for(int x = 0; x < _board.getXSize(); x++) {
            if(regions.getElement(x, y) == regionId) {
                _board.setElement(x, y, -1);
            }
        }
    }
}

int gct::ColorTetris::calcScore(int regionSize) {
    return regionSize*regionSize/3;
}

int gct::ColorTetris::calcDifficultyLevel() const {
    return score / 100;
}
