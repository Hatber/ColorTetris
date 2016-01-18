#ifndef RLL_BORDERDRAFTER_HPP
#define RLL_BORDERDRAFTER_HPP

#include "libtcod.hpp"

namespace rll {

const TCODColor defaultActiveBorderColor(200,160,30);

class BorderDrafter {
public:
    BorderDrafter() : _activeBorderColor(defaultActiveBorderColor) { }

    void SetActiveBorderColor(TCODColor color) { _activeBorderColor = color; }

    void DrawActiveBorder (int startX, int endX, int startY, int endY, TCODConsole* console);

    void DrawPassiveBorder(TCODConsole* console);
    void DrawPassiveBorder(int startX, int endX, int startY, int endY, TCODConsole* console);

private:
    TCODColor _activeBorderColor;

private:
    static const int rightUpCorner   = TCOD_CHAR_DNE;
    static const int leftUpCorner    = TCOD_CHAR_DNW;
    static const int rightDownCorner = TCOD_CHAR_DSE;
    static const int leftDownCorner  = TCOD_CHAR_DSW;

    static const int horizontalLine  = TCOD_CHAR_DHLINE;
    static const int verticalLine    = TCOD_CHAR_DVLINE;
};

    void BorderDrafter::DrawActiveBorder (int startX, int endX, int startY, int endY, TCODConsole* console) {
        console->setDefaultBackground(_activeBorderColor);

        for(int i = startX; i < endX; i++) {
            console->putChar(i, startY, ' ', TCOD_BKGND_SET);
            console->putChar(i, endY - 1,   ' ', TCOD_BKGND_SET);
        }

        for(int i = startY; i < endY; i++) {
            console->putChar(startX, i, ' ', TCOD_BKGND_SET);
            console->putChar(endX - 1,   i, ' ', TCOD_BKGND_SET);
        }
    }


    void BorderDrafter::DrawPassiveBorder(TCODConsole* console) {
        DrawPassiveBorder(0, console->getWidth(), 0, console->getHeight(), console);
    }

    void BorderDrafter::DrawPassiveBorder(int startX, int endX, int startY, int endY, TCODConsole* console) {
        console->setDefaultBackground(TCODColor::black);

        console->putChar(startX,   startY,   leftUpCorner, TCOD_BKGND_SET);
        console->putChar(endX - 1, startY,   rightUpCorner, TCOD_BKGND_SET);
        console->putChar(startX,   endY - 1, leftDownCorner, TCOD_BKGND_SET);
        console->putChar(endX - 1, endY - 1, rightDownCorner, TCOD_BKGND_SET);

        for(int i = startX + 1; i < endX - 1; i++) {
            console->putChar(i, startY,   horizontalLine, TCOD_BKGND_SET);
            console->putChar(i, endY - 1, horizontalLine, TCOD_BKGND_SET);
        }

        for(int i = startY + 1; i < endY - 1; i++) {
            console->putChar(startX,   i, verticalLine, TCOD_BKGND_SET);
            console->putChar(endX - 1, i, verticalLine, TCOD_BKGND_SET);
        }
    }

} //rll

#endif // RLL_BORDERDRAFTER_HPP
