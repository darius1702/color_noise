#include "colors.h"

FileColorLoader::FileColorLoader(int num_colors, std::string filename) :
    ColorLoader(num_colors) {
    m_colormap = std::vector<std::string>();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Can't open file: " + filename);
    }

    std::string line;
    while (getline(file, line)) {
        m_colormap.push_back(line);
    }

    file.close();
}

std::string FileColorLoader::getColorRGB(int index) {
    if (index >= static_cast<int>(m_colormap.size()) || index < 0) {
        throw std::invalid_argument("Invalid index: " + std::to_string(index));
    }
    std::string col = m_colormap[index];

    int r, g, b;
    std::sscanf(col.c_str(), "#%02x%02x%02x", &r, &g, &b);

    char result[100];
    std::sprintf(result, "%d %d %d", r, g, b);

    return std::string(result);
}


