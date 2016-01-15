#ifndef RLL_CONNECTEDREGIONSEARCHER_HPP
#define RLL_CONNECTEDREGIONSEARCHER_HPP

#include <algorithm>
#include "NeighborhoodSearcher.hpp"

namespace rll {

    template< typename T >
    class ConnectedRegionSearcher {
    public:
        ConnectedRegionSearcher() : regionMaxId(0) { };

        TArea< T > search(const TArea< T >& field);
        int regionCount() { return regionMaxId; }

    private:
        void searchRecursive(const TArea< T > &field, TArea< T >& regions, int x, int y, int id);

        int regionMaxId;
    };

    template< typename T >
    TArea< T > ConnectedRegionSearcher<T>::search(const TArea< T > &field) {
        TArea< T > result(field.getXSize(), field.getYSize(), -1);

        for(int y = 0; y < field.getYSize(); y++) {
            for (int x = 0; x < field.getXSize(); x++) {
                if(result.getElement(x, y) == -1) {
                    searchRecursive(field, result, x, y, regionMaxId++);
                }
            }
        }

        return result;
    }

    template< typename T >
    void ConnectedRegionSearcher<T>::searchRecursive(
        const TArea< T > &field, TArea< T >& regions, int x, int y, int id
    ) {
        NeighborhoodSearcher< T > searcher(field);
        typename NeighborhoodSearcher< T >::neighborSetT neighbors;

        regions.setElement(x, y, id);
        neighbors = searcher.FindNeumann({ x, y });

        T originElement = field.getElement(x, y);
        for(int i = 0; i < neighbors.size(); i++) {
            if(neighbors[i]._data == originElement && regions.getElement(neighbors[i]) == -1) {
                searchRecursive(field, regions, neighbors[i].x(), neighbors[i].y(), id);
            }
        }
    }

} // rll

#endif //RLL_CONNECTEDREGIONSEARCHER_HPP
