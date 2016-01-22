#include <iostream>

#include "GameController.h"

using namespace std;

const int xSize = 10;
const int ySize = 20;
const int colorCount = 7;

//TODO : Animated Text Window
//TODO : New Figure Type
int main() {
    srand(time(0));

    gct::GameController gameController(colorCount, xSize, ySize);
    gameController.loop();

    return 0;
}