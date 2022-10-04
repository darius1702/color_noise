// Thank god for https://stackoverflow.com/questions/29711668/perlin-noise-generation, adapted for 'modern' C++

// Two-dimensional value noise based on Hugo Elias's description:
//   http://freespace.virgin.net/hugo.elias/models/m_perlin.htm

#include <iostream>
#include <fstream>
#include <cmath>
#include <array>

#include "noise.h"
#define SIZE 400

int primeIndex = 0;

int main() {
    std::ofstream img("test.pbm");
    img << "P2" << std::endl;
    img << SIZE << " " << SIZE << std::endl;
    img << "255" << std::endl;

    NoiseGenerator ng(4, 10, 1, 0.5);

    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            img << ng.getNoiseNorm(x, y) << " ";
        }
        img << std::endl;
    }

    img.close();
    return 0;
}

NoiseGenerator::NoiseGenerator() {
    m_octaves = 7;
    m_frequency = pow(2, m_octaves);
    m_amplitude = 1;
    m_persistence = 0.5;
}

NoiseGenerator::NoiseGenerator(int octaves, int frequency, int amplitude, double persistence) {
    m_octaves = octaves;
    m_frequency = frequency;
    m_amplitude = amplitude;
    m_persistence = persistence;
}

double NoiseGenerator::getNoise(double x, double y) {
    double total = 0;
    double frequency = m_frequency;
    double amplitude = m_amplitude;
    for (int i = 0; i < m_octaves; ++i) {
        frequency /= 2;
        amplitude *= m_persistence;
        total += interpolatedNoise((primeIndex + i) % maxPrimeIndex,
                x / frequency, y / frequency) * amplitude;
    }
    return total / frequency;
}

int NoiseGenerator::getNoiseNorm(double x, double y) {
    return floor(((getNoise(x, y) * 0.5) + 0.5) * 255);
}

std::array<std::array<int, 3>, maxPrimeIndex> NoiseGenerator::m_primes = {
    std::array<int,3>{ 995615039, 600173719, 701464987 },
    std::array<int,3>{ 831731269, 162318869, 136250887 },
    std::array<int,3>{ 174329291, 946737083, 245679977 },
    std::array<int,3>{ 362489573, 795918041, 350777237 },
    std::array<int,3>{ 457025711, 880830799, 909678923 },
    std::array<int,3>{ 787070341, 177340217, 593320781 },
    std::array<int,3>{ 405493717, 291031019, 391950901 },
    std::array<int,3>{ 458904767, 676625681, 424452397 },
    std::array<int,3>{ 531736441, 939683957, 810651871 },
    std::array<int,3>{ 997169939, 842027887, 423882827 }
};

double NoiseGenerator::noise(int i, int x, int y) {
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int a = m_primes[i][0], b = m_primes[i][1], c = m_primes[i][2];
    int t = (n * (n * n * a + b) + c) & 0x7fffffff;
    return 1.0 - (double)(t)/1073741824.0;
}

double NoiseGenerator::smoothedNoise(int i, int x, int y) {
    double corners = (noise(i, x-1, y-1) + noise(i, x+1, y-1) +
            noise(i, x-1, y+1) + noise(i, x+1, y+1)) / 16,
           sides = (noise(i, x-1, y) + noise(i, x+1, y) + noise(i, x, y-1) +
                   noise(i, x, y+1)) / 8,
           center = noise(i, x, y) / 4;
    return corners + sides + center;
}

double NoiseGenerator::interpolate(double a, double b, double x) {
    double ft = x * 3.1415927,
           f = (1 - cos(ft)) * 0.5;
    return  a*(1-f) + b*f;
}

double NoiseGenerator::interpolatedNoise(int i, double x, double y) {
    int integer_X = x;
    double fractional_X = x - integer_X;
    int integer_Y = y;
    double fractional_Y = y - integer_Y;

    double v1 = smoothedNoise(i, integer_X, integer_Y),
           v2 = smoothedNoise(i, integer_X + 1, integer_Y),
           v3 = smoothedNoise(i, integer_X, integer_Y + 1),
           v4 = smoothedNoise(i, integer_X + 1, integer_Y + 1),
           i1 = interpolate(v1, v2, fractional_X),
           i2 = interpolate(v3, v4, fractional_X);
    return interpolate(i1, i2, fractional_Y);
}


