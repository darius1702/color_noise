#include "colors.h"

ColorMap::ColorMap(const std::string& filename) {
    m_colors = std::vector<Color>();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Can't open file: " + filename);
    }

    std::string line;
    while (getline(file, line)) {

        unsigned int r, g, b;
        std::sscanf(line.c_str(), "#%02x%02x%02x", &r, &g, &b);

        m_colors.push_back({static_cast<unsigned char>(r & 0xff), static_cast<unsigned char>(g & 0xff), static_cast<unsigned char>(b & 0xff)});
    }

    file.close();
}

Color ColorMap::getColorStruct(int index) {
    if (index >= static_cast<int>(m_colors.size()) || index < 0) {
        throw std::invalid_argument("Invalid index: " + std::to_string(index));
    }

    return m_colors[index];
}

int ColorMap::size() {
    return m_colors.size();
}

