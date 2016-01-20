#include "RandomBot.hpp"
#include "rll/ConnectedRegionSearcher.hpp"

using namespace gct;

void RandomBot::findWay() {
    way.clear();

    for(int i = 0; i < 5; i++) {
        switch (rand()%4) {
            case 0 : way.push_back(TCODK_LEFT);  break;
            case 1 : way.push_back(TCODK_RIGHT); break;
            case 2 : way.push_back(TCODK_UP);  break;
            case 3 : way.push_back(TCODK_SPACE); break;
            default: break;
        }
    }
    way.push_back(TCODK_DOWN);

    std::reverse(way.begin(), way.end());
}
