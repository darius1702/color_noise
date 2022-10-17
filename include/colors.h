#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

#define HEX_PATTERN "#%02x%02x%02x"

struct Color
{
  unsigned char r, g, b;
  unsigned char a = 0xFF;
  Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_ = 0xFF)
    : r(r_)
    , g(g_)
    , b(b_)
    , a(a_){};
};

class ColorMap {

    private:
        std::vector<Color> m_colors;

    public:
        ColorMap(const std::string& filename);
        int size();

        Color getColorStruct(int index);
};

#endif // !COLORS_H
