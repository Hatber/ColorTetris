#ifndef RLL_NEIGHBORHOODSEARCHER_HPP
#define RLL_NEIGHBORHOODSEARCHER_HPP

#include <vector>
#include "TArea.hpp"

namespace rll {

    template < typename T >
    struct Neighbor : public Point {
        Neighbor(const T data, const Point& p) : Point(p.x(), p.y(), p.z()), _data(data) { }
        Neighbor(const T data, int x, int y, int z = 0) : Point(x, y, z), _data(data) { }
        const T _data;

        bool operator == (const T& rhs) {
            return _data == rhs;
        }
    };

    template < typename T >
    class NeighborhoodSearcher {
    public:
        typedef std::vector< Neighbor< T > > neighborSetT;

    public:
        NeighborhoodSearcher(const TArea< T >& field) : _field(field) { }

        neighborSetT FindNeumann(const Point& source);
        neighborSetT FindMoore(const Point& source);

    private:
        const TArea< T >& _field;
    };

    template< typename T >
    typename NeighborhoodSearcher<T>::neighborSetT NeighborhoodSearcher<T>::FindNeumann(const Point& source) {
        neighborSetT neighbors;

        if(_field.borders(source.shift(-1, 0)))
            { neighbors.push_back( {_field.getElement(source.shift(-1, 0)), source.shift(-1, 0)} ); }
        if(_field.borders(source.shift( 0,-1)))
            { neighbors.push_back( {_field.getElement(source.shift( 0,-1)), source.shift( 0,-1)} ); }
        if(_field.borders(source.shift( 0, 1)))
            { neighbors.push_back( {_field.getElement(source.shift( 0, 1)), source.shift( 0, 1)} ); }
        if(_field.borders(source.shift( 1, 0)))
            { neighbors.push_back( {_field.getElement(source.shift( 1, 0)), source.shift( 1, 0)} ); }

        return neighbors;
    }

    template< typename T >
    typename NeighborhoodSearcher<T>::neighborSetT NeighborhoodSearcher< T >::FindMoore(const Point& source) {
        neighborSetT neighbors = FindNeumann(source);

        if(_field.borders(source.shift(-1, -1)))
            { neighbors.push_back( {_field.getElement(source.shift(-1, -1)), source.shift(-1, -1)} ); }
        if(_field.borders(source.shift(-1,  1)))
            { neighbors.push_back( {_field.getElement(source.shift(-1,  1)), source.shift(-1,  1)} ); }
        if(_field.borders(source.shift( 1, -1)))
            { neighbors.push_back( {_field.getElement(source.shift( 1, -1)), source.shift( 1, -1)} ); }
        if(_field.borders(source.shift( 1,  1)))
            { neighbors.push_back( {_field.getElement(source.shift( 1,  1)), source.shift( 1,  1)} ); }

        return neighbors;
    }

} //rll

#endif // RLL_NEIGHBORHOODSEARCHER_HPP
