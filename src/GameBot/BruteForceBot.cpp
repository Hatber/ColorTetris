#include <iostream>
#include <algorithm>

#include "BruteForceBot.hpp"

void gct::BruteForceBot::findWay() {
    way.clear();

    bestOptions opt;
    opt.isVertical = false;
    opt.transposeCount = 0;
    opt.position = rll::Point::makePoint(game.getBoard().getXSize()/2, 0);

    int maxScore = 0;

    //Test All Vertical Options
    ColorTetris preparedVGame(game);

    //- Bring the game to start state
    preparedVGame.dropFigure();
    preparedVGame.rotate();
    for(int x = 0; x < game.getBoard().getXSize()/2; x++) {
        preparedVGame.moveLeft();
    }

    //Test vertical states
    for(int x = 0; x < game.getBoard().getXSize(); x++) {
        for(int colorsCount = 0; colorsCount < 3; colorsCount++) {
            ColorTetris gameToTest(preparedVGame);
            for(int transposeCount = 0; transposeCount <= colorsCount; transposeCount++) {
                gameToTest.transposeForward();
            }
            for(int moveCount = 0; moveCount <= x; moveCount++) {
                gameToTest.moveRight();
            }

            gameToTest.forceDropFigure();
            gameToTest.fixFigure();

            do {
                while (gameToTest.gravityIsNeeded()) {
                    gameToTest.gravity();
                }
            } while(gameToTest.removeMonochromeRegion());

            if(maxScore < gameToTest.getScore()) {
                maxScore = gameToTest.getScore();

                opt.isVertical = gameToTest.getFigure().isVertical;
                opt.position = gameToTest.getFigurePosition();
                opt.transposeCount = colorsCount;
            }
        }
    }

    //- Bring the game to horizontal start state
    ColorTetris preparedHGame(game);
    for(int x = 0; x < game.getBoard().getXSize()/2; x++) {
        preparedHGame.moveLeft();
    }

    //Test horizontal states
    for(int x = 0; x < game.getBoard().getXSize()-2; x++) {
        for(int colorsCount = 0; colorsCount < 3; colorsCount++) {
            ColorTetris gameToTest(preparedHGame);
            for(int transposeCount = 0; transposeCount <= colorsCount; transposeCount++) {
                gameToTest.transposeForward();
            }
            for(int moveCount = 0; moveCount <= x; moveCount++) {
                gameToTest.moveRight();
            }

            gameToTest.forceDropFigure();
            gameToTest.fixFigure();

            do {
                while (gameToTest.gravityIsNeeded()) {
                    gameToTest.gravity();
                }
            } while(gameToTest.removeMonochromeRegion());

            if(maxScore < gameToTest.getScore()) {
                maxScore = gameToTest.getScore();

                opt.isVertical = gameToTest.getFigure().isVertical;
                opt.position = gameToTest.getFigurePosition();
                opt.transposeCount = colorsCount;
            }
        }
    }

    std::cout << "maxScore: " << maxScore << std::endl;
    constructWay(opt);
}

void gct::BruteForceBot::constructWay(const gct::BruteForceBot::bestOptions &opt) {
    rll::Point optimalPosition = opt.position;
    const rll::Point currentPosition = game.getFigurePosition();

    std::cout << "currentPosition: " << currentPosition.x() << std::endl;
    std::cout << opt.transposeCount << std::endl;
    std::cout << opt.isVertical << std::endl;

    int shift = std::abs(currentPosition.x() - optimalPosition.x());
    TCOD_keycode_t move;

    if(currentPosition.x() < optimalPosition.x()) { move = TCODK_RIGHT; }
    else { move = TCODK_LEFT; }

    for(int x = 0; x < shift; x++) {
        way.push_back(move);
    }

    for(int transposeCount = 0; transposeCount <= opt.transposeCount; transposeCount++) {
        way.push_back(TCODK_UP);
    }

    //std::random_shuffle(way.begin(), way.end());

    if(opt.isVertical) { way.push_back(TCODK_SPACE); }


    way.push_back(TCODK_DOWN);

    std::reverse(way.begin(), way.end());

    std::cout << "Constructed: " << way.size() << std::endl;
}
