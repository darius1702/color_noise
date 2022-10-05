#include <string>
#include <array>
#include <map>
#include <ostream>

#include "noise.h"
#include "colors.h"

#define SIZE 400

int main() {

    std::ofstream img("test.pbm");
    img << "P3" << std::endl;
    img << SIZE << " " << SIZE << std::endl;
    img << "255" << std::endl;


    // Noise generation
    NoiseGenerator ng(time(NULL), 24, 2, 2, 0.5);
    ng.setScaling(2, 1);

    std::array<std::array<double, SIZE>, SIZE> arr = {};
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            double dx = x * 0.02;
            double dy = y * 0.02;

            double value = ng.noise(dx, dy, 0.0);

            double height = (value * 0.5) + 0.5;
            arr[x][y] = height;
        }
    }

    // Color
    FileColorLoader colors(256, "colormap.txt");

    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            int height = floor(arr[x][y] * 255);
            Color color = colors.getColorRGB(height);
            img << color.r << " " << color.g << " " << color.b << " " <<  std::endl;
        }
        img << std::endl;
    }

    img.close();
    return 0;
}


