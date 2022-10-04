# Simple C++ Noise Generator

## How to run
```c++
#include "noise.h"

// New noise generator with random seed and default parameters
NoiseGenerator ng;

// Noise generator with seed 123
NoiseGenerator ng2(123);

// Random seed, 6 octaves, initial frequency of 4,
// initial amplitude of 2, persistence of 0.5
NoiseGenerator ng3(6, 4, 2, 0.5);

// Same as ng3 but with seed 123
NoiseGenerator ng4(123, 6, 4, 2, 0.5);

// Evaluate noise at (1.0, 1.2, 5.2)
double n1 = ng.simpleNoise(1.0, 1.2, 5.2);

// Calculate fractal noise using simpleNoise
// and the parameters the generator was constructed with
double n2 = ng.noise(1.0, 1.2, 5.2);

// Map a noise value in [-1, 1] to a grayscale value from 0 to 255
int color = NoiseGenerator::norm(-0.23);
```

```make && ./main``` will spit out a 400x400 grayscale noise image in the [Netpbm format](https://en.wikipedia.org/wiki/Netpbm).

![example of a generated image](https://github.com/darius1702/color_noise/blob/main/example.png)
## TODO
- Color parameters to make the noise look nice
- Code cleanup

Based on the [original Java implementation by Ken Perlin](https://mrl.cs.nyu.edu/~perlin/noise/).
