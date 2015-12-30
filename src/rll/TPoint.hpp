#ifndef POINT_HPP
#define POINT_HPP

namespace rll {

    template < typename T >
    class TPoint {
    public:
        TPoint() : TPoint(T(), T(), T()) { }
        TPoint(const T& x, const T& y, const T& z = T()) : _x(x), _y(y), _z(z) { }

        T x() const { return _x; }
        T y() const { return _y; }
        T z() const { return _z; }

        T& x() { return _x; }
        T& y() { return _y; }
        T& z() { return _z; }

        TPoint shift(const T& x, const T& y, const T& z = 0) const { return TPoint(_x + x, _y + y, _z + z); }

        bool operator == (const TPoint& p) const { return x()==p.x() and y()==p.y() and z()==p.z(); }
        bool operator != (const TPoint& p) const { return not (*this == p); }
        bool operator < (TPoint const& rhs) const {
            return x() < rhs.x() or (x() == rhs.x() and y() < rhs.y() or(y() == rhs.y() and z() < rhs.z()));
        }

        virtual ~TPoint() = default;

        static TPoint makePoint(const T& x, const T& y, const T& z = 0) { return TPoint(x, y, z); }
    private:
        T _x, _y, _z;
    };

    typedef TPoint< int > Point;

} // rll

#endif //POINT_HPP
