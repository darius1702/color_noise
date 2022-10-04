#include "noise.h"

#define SIZE 400

int main() {
    std::ofstream img("test.pbm");
    img << "P2" << std::endl;
    img << SIZE << " " << SIZE << std::endl;
    img << "255" << std::endl;

    NoiseGenerator ng(16, 16, 4, 0.75);

    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            double dx = x / (double)SIZE;
            double dy = y / (double)SIZE;
            img << NoiseGenerator::norm(ng.noise(dx, dy, 0.0)) << " ";
        }
        img << std::endl;
    }

    img.close();
    return 0;
}


