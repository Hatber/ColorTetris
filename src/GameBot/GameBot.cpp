#include "GameBot.hpp"
#include "rll/ConnectedRegionSearcher.hpp"

#include <iostream> //TODO: remove

using namespace gct;

void GameBot::findWay() {
    rll::ConnectedRegionSearcher< int > searcher;
    rll::Area regions(searcher.search(game._board));

    int regionCount = searcher.regionCount();
    for(int regionId = 0; regionId < regionCount; regionId++) {
        if(game.regionContainFreeSpace(regions, regionId)) { continue; }
    }
    //Find open regions

    vector< int > openRegions = findOpenRegions(regions);

    //Find regions with colors
    vector< int > colorRegions = findRegionsWithColors(regions, 0);


    //Find regions with max size from set

    //Calculate figure path
    //Add force drop at end
}

void GameBot::randomWay() {
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

TCOD_keycode_t GameBot::getAction() {
    elapsedTime += TCODSystem::getLastFrameLength();
    if(elapsedTime - timeForStep < 0) { return TCODK_NONE; }
    elapsedTime = 0;

    if(way.size() == 0) { return TCODK_NONE; }

    TCOD_keycode_t code = way.back();
    way.pop_back();
    return code;
}

std::vector< int > GameBot::findOpenRegions(const Area& regions) {
    vector< int > openRegions;

    rll::NeighborhoodSearcher< int > searcher(game._board);
    typename rll::NeighborhoodSearcher< int >::neighborSetT neighbors;

    for(int y = 0; y < regions.getYSize(); y++) {
        for(int x = 0; x < regions.getXSize(); x++) {

            if(game._board.borders(x, y - 1) && game._board.getElement(x, y-1) == -1) {
                openRegions.push_back(regions.getElement(x, y));
            }
//            neighbors = searcher.FindNeumann({x, y});
//            for(int i = 0; i < neighbors.size(); i++) {
//                if(neighbors[i]._data == -1) {
//                    openRegions.push_back(regions.getElement(x, y));
//                }
//            }
        }
    }

    filterToUnique(openRegions);

    return openRegions;
}

std::vector< int > GameBot::findRegionsWithColors(const Area& regions, int colorId) {
    vector< int > colorRegions;

    for(int y = 0; y < regions.getYSize(); y++) {
        for(int x = 0; x < regions.getXSize(); x++) {
            if(game._board.getElement(x, y) == colorId) {
                colorRegions.push_back(regions.getElement(x, y));
            }
        }
    }

    filterToUnique(colorRegions);

    return colorRegions;
}


void GameBot::filterToUnique(std::vector< int >& v) {
    std::sort(v.begin(), v.end());
    v.resize(std::distance(v.begin(), std::unique(v.begin(), v.end())));
}

