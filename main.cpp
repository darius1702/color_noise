#include <array>
#include <iostream>
#include <map>
#include <string>

#include <SDL2/SDL.h>

#include "colors.h"
#include "noise.h"

#define SIZE 400

int main() {

  std::ofstream img("test.pbm");
  img << "P3" << std::endl;
  img << SIZE << " " << SIZE << std::endl;
  img << "255" << std::endl;

  // Noise generation
  NoiseGenerator ng(time(NULL), 8, 4, 4, 0.5);
  ng.setScaling(1, 1);

  std::array<std::array<double, SIZE>, SIZE> arr = {};
  for (int y = 0; y < SIZE; ++y) {
    for (int x = 0; x < SIZE; ++x) {
      double dx = x / static_cast<double>(SIZE);
      double dy = y / static_cast<double>(SIZE);

      arr[x][y] = ng.noise(dx, dy, 0.0);
    }
  }

  // Color
  ColorMap colors("resources/colormap.txt");

  for (int y = 0; y < SIZE; ++y) {
    for (int x = 0; x < SIZE; ++x) {
      int height = round(arr[x][y] * (colors.size() - 1));
      Color color = colors.getColorStruct(height);
      img << (int)color.r << " " << (int)color.g << " " << (int)color.b << " "
          << std::endl;
    }
    img << std::endl;
  }

  img.close();
  return 0;
}
