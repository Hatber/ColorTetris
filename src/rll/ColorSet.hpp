#ifndef RLL_COLORSET_H
#define RLL_COLORSET_H

#include "Color.hpp"

#include <vector>

namespace rll {

class ColorSet {
public:
    ColorSet() {
        colorMap.push_back(Color(0,   0,   255));
        colorMap.push_back(Color(0,   255, 0));
        colorMap.push_back(Color(255, 0,   0));

        colorMap.push_back(Color(0,   255, 255));
        colorMap.push_back(Color(255, 255, 0));

        colorMap.push_back(Color(0,   127, 255));
        colorMap.push_back(Color(255, 127, 0));

        colorMap.push_back(Color(0,   255, 127));
        colorMap.push_back(Color(127, 255, 0));
    }

    const Color getColorByIndex(int id) const {
        return colorMap.at(id);
    }
private:
    std::vector< Color > colorMap;
};

} // rll

#endif //RLL_COLORSET_H
