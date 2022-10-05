// simple noise algorithm adapted from https://mrl.cs.nyu.edu/~perlin/noise/

#include "noise.h"

NoiseGenerator::NoiseGenerator(
        int seed,
        int octaves,
        int frequency,
        int amplitude,
        double persistence) {
    m_factor = 1;
    m_exponent = 1;

    m_octaves = octaves;
    m_frequency = frequency;
    m_amplitude = amplitude;
    m_persistence = persistence;
    srand(seed);
    for (int i = 0; i < PERMUTATION_SIZE / 2; ++i) {
        m_permutation[i] = rand() % 256;
        m_permutation[256 + i] = m_permutation[i];
    }
}

double NoiseGenerator::simpleNoise(double x, double y, double z) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;

    double fx = x - floor(x);
    double fy = y - floor(y);
    double fz = z - floor(z);

    double u = fade(fx);
    double v = fade(fy);
    double w = fade(fz);

    int A  = m_permutation[X  ]+Y;
    int AA = m_permutation[A  ]+Z;
    int AB = m_permutation[A+1]+Z;
    int B  = m_permutation[X+1]+Y;
    int BA = m_permutation[B  ]+Z;
    int BB = m_permutation[B+1]+Z;

    return lerp(w, lerp(v, lerp(u, grad(m_permutation[AA  ], fx  , fy  , fz   ),
                                   grad(m_permutation[BA  ], fx-1, fy  , fz   )),
                           lerp(u, grad(m_permutation[AB  ], fx  , fy-1, fz   ),
                                   grad(m_permutation[BB  ], fx-1, fy-1, fz   ))),
                   lerp(v, lerp(u, grad(m_permutation[AA+1], fx  , fy  , fz-1 ),
                                   grad(m_permutation[BA+1], fx-1, fy  , fz-1 )),
                           lerp(u, grad(m_permutation[AB+1], fx  , fy-1, fz-1 ),
                                   grad(m_permutation[BB+1], fx-1, fy-1, fz-1 ))));
}

double NoiseGenerator::noise(double x, double y, double z) {
    int oct = m_octaves;
    int freq = m_frequency;
    int amp = m_amplitude;
    double persistence = m_persistence;
    double sum = 0.0;
    double maxValue = 0.0;
    for (int o = 0; o < oct; ++o) {
        sum += simpleNoise(x * freq, y * freq, z * freq) * amp;
        maxValue += amp;
        amp *= persistence;
        freq *= 2;
    }

    double value =  sum / maxValue;
    double scaled = value * m_factor;

    if (scaled < -1) {
        scaled = -1;
    } else if (scaled > 1) {
        scaled = 1;
    }

    return pow(scaled, m_exponent);
}

void NoiseGenerator::setScaling(int factor, int exponent) {
    if (factor < 0  || exponent < 0) {
         throw std::invalid_argument("invalid noise factor/exponent: " + std::to_string(factor) + " / " + std::to_string(exponent));
    }
    m_factor = factor;
    m_exponent = exponent;
}

double NoiseGenerator::grad(int hash, double x, double y, double z) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h<4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double NoiseGenerator::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double NoiseGenerator::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}
