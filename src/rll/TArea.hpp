#ifndef AREA_HPP
#define AREA_HPP

#include "TPoint.hpp"

#include <vector>

namespace rll {

    typedef int CoordinateT;

    template< typename T >
    class TArea {
    public:
        TArea() : xSize(0), ySize(0) { }
        TArea(const Point& p) : TArea(p.x(), p.y()) { }
        TArea(const Point& p, const T& initValue) : TArea(p.x(), p.y(), initValue) { }
        TArea(CoordinateT x, CoordinateT y) : TArea(x, y, T()) { }
        TArea(CoordinateT x, CoordinateT y, const T& initValue) : field(y, std::vector< T >(x, initValue)) {
            xSize = computeXSize();
            ySize = computeYSize();
        }
        TArea(const TArea& a) : field(a.field), xSize(a.xSize), ySize(a.ySize) { }

        std::size_t getYSize() const { return ySize; }
        std::size_t getXSize() const { return xSize; }

        Point getSize()  const { return Point::makePoint(getXSize(), getYSize()); }
        std::size_t getElementCount() const { return getYSize() * getXSize(); }

        T& at(const Point& p) { return at(p.x(), p.y()); }
        T& at(CoordinateT x, CoordinateT y) { return field/*[y][x]*/.at(y).at(x); }

        T& at(CoordinateT id) { return at(id%getXSize(), id/getXSize()); }

        T& operator [] (CoordinateT id) { return at(id); }
        T& operator [] (const Point& p) { return at(p); }

        T getElement(const Point& p) const { return getElement(p.x(), p.y()); }
        T getElement(CoordinateT x, CoordinateT y) const { return field/*[y][x]*/.at(y).at(x); }

        void setElement(const Point& p, const T& element) { setElement(p.x(), p.y(), element); }
        void setElement(CoordinateT x, CoordinateT y, const T& element) { at(x, y) = element; }

        bool borders(const Point& p) { return borders(p.x(), p.y()); }
        bool borders(CoordinateT x, CoordinateT y) { return (x>=0 && x < getXSize()) && (y>=0 && y < getYSize()); }

        void resize(const Point& size) { resize(size.x(), size.y()); }
        void resize(CoordinateT x, CoordinateT y) {
            field.resize(y);
            for(CoordinateT c = 0; c < y; c++) {
                field[c].resize(x);
            }

            xSize = computeXSize();
            ySize = computeYSize();
        }

        void fill(const T& fillingValue)
        { std::fill(field.begin(), field.end(), std::vector< T >(getXSize(), fillingValue)); }

        bool isEmpty() const { return getYSize() == 0; }

    protected:
        std::vector< std::vector< T > > field;
        std::size_t xSize, ySize;

    private:
        std::size_t computeYSize() const { return field.size(); }
        std::size_t computeXSize() const { return field.size() ? field.front().size() : 0; }
    };

    typedef TArea< CoordinateT > Area;

} // rll

#endif //AREA_HPP
