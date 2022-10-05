# Simple C++ Noise Generator

## How to run
```c++
#include "noise.h"

// Seed 123, 6 octaves, initial frequency of 4,
// initial amplitude of 2, persistence of 0.5
NoiseGenerator ng(123, 6, 4, 2, 0.5);

// Evaluate noise at (1.0, 1.2, 5.2)
double n1 = ng.simpleNoise(1.0, 1.2, 5.2);

// Set linear and exponential scaling factors for fractal noise
// noise = (noise * 2)^1.2
ng.setScaling(2, 1.2);

// Calculate fractal noise using simpleNoise
// and the parameters the generator was constructed with
double n2 = ng.noise(1.0, 1.2, 5.2);

// Load a map of 256 colors from a file
FileColorLoader cl(256, "colormap.txt");

// Load RGB string ("R G B") for noise value n2 from above
// Keep in mind that we have to map the value from [-1, 1]
// to 0 - 255
double height = floor(((n2 * 0.5) + 0.5) * 255);
std::string color = cl.getColorRGB(height);
```

```make && ./main``` will spit out a 400x400 colored noise image in the [Netpbm format](https://en.wikipedia.org/wiki/Netpbm).

![example of a generated image](https://github.com/darius1702/color_noise/blob/main/example.png)
## TODO
- Color map generation
- Code cleanup

Based on the [original Java implementation by Ken Perlin](https://mrl.cs.nyu.edu/~perlin/noise/).
