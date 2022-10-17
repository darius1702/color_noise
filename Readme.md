# Simple C++ Noise Generator

## How to run
```c++
#include "noise.h"
#include "color.h"

// Seed 123, 6 octaves, initial frequency of 4,
// initial amplitude of 2, persistence of 0.5
NoiseGenerator ng(123, 6, 4, 2, 0.5);

// Set linear and exponential scaling factors for fractal noise
// noise = (noise * 2)^1.2
ng.setScaling(2, 1.2);

// Calculate fractal noise using the parameters
// the generator was constructed with
double n = ng.noise(1.0, 1.2, 5.2);

// Load a list of colors from a file
Colormap cl("resources/colormap.txt");

// Load RGB Color for noise value n from above
// Keep in mind that we have to map the value from [0, 1]
// to an index into the colormap
int height = round(n * (cl.size() - 1);
Color color = cl.getColorRGB(height);
```

```make && ./main``` will spit out a 400x400 colored noise image in the [Netpbm format](https://en.wikipedia.org/wiki/Netpbm).

![example of a generated image](https://github.com/darius1702/color_noise/blob/main/resources/example.png)
## TODO
- Color map generation
- Code cleanup

Based on the [original Java implementation by Ken Perlin](https://mrl.cs.nyu.edu/~perlin/noise/).
