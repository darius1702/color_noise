#include "colors.h"

FileColorLoader::FileColorLoader(int num_colors, std::string filename) :
    ColorLoader(num_colors) {
    m_colormap = std::vector<Color>();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Can't open file: " + filename);
    }

    std::string line;
    while (getline(file, line)) {

        int r, g, b;
        std::sscanf(line.c_str(), "#%02x%02x%02x", &r, &g, &b);

        m_colormap.push_back({r, g, b});
    }

    file.close();
}

Color FileColorLoader::getColorRGB(int index) {
    if (index >= static_cast<int>(m_colormap.size()) || index < 0) {
        throw std::invalid_argument("Invalid index: " + std::to_string(index));
    }

    return m_colormap[index];
}

