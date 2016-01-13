#ifndef RLL_COLOR_HPP
#define RLL_COLOR_HPP

namespace rll {

    class Color {
    public:
        typedef unsigned char channelT;

        Color() : Color(0, 0, 0) { }
        Color(channelT r, channelT g, channelT b) : _r(r), _g(g), _b(b) { }

        channelT& r() { return _r; }
        channelT& g() { return _g; }
        channelT& b() { return _b; }

    private:
        channelT _r, _g, _b;
    };

} // rll

#endif //RLL_COLOR_HPP
