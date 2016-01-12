#include <iostream>

#include "Engine/ColorTetris.h"
#include "Render.h"

using namespace std;

const int xSize = 10;
const int ySize = 20;
const int colorCount = 3;

int main() {
    srand(time(0));

    gct::ColorTetris ct(colorCount, xSize, ySize);
    gct::Render render(ct);

    while(true) {
        render.show();

        cin.get();
        ct.Gravity();
    }

    return 0;
}