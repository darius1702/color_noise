#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

class ColorLoader {

    protected:
        int m_num_colors;

        std::vector<std::string> m_colormap;

    public:
        ColorLoader(int num_colors) : m_num_colors (num_colors) {}

        virtual std::string getColorRGB(int index) = 0;
};

class FileColorLoader: public ColorLoader {
    public:
        FileColorLoader(int num_colors, std::string filename);
        std::string getColorRGB(int index) override;
};

#endif // !COLORS_H
