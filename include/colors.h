#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

struct Color {
    int r, g, b;
};

class ColorLoader {

    protected:
        int m_num_colors;

        std::vector<Color> m_colormap;

    public:
        ColorLoader(int num_colors) : m_num_colors (num_colors) {}

        virtual Color getColorRGB(int index) = 0;
};

class FileColorLoader: public ColorLoader {
    public:
        FileColorLoader(int num_colors, std::string filename);
        Color getColorRGB(int index) override;
};

#endif // !COLORS_H
