#ifndef NOISE_H
#define NOISE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <random>
#include <time.h>

#define PERMUTATION_SIZE 512

class NoiseGenerator {
    private:
        // Array used by the Perlin Noise algorithm
        std::array<int, PERMUTATION_SIZE> m_permutation;

        // Fractal noise parameters
        int m_octaves, m_frequency, m_amplitude;
        double m_persistence;

        // Scaling parameters
        double m_factor, m_exponent;

        // Smoothstep fade function
        static double fade(double t);

        // Linear interpolation
        static double lerp(double t, double a, double b);

        // Perlin Noise gradient function
        double grad(int hash, double x, double y, double z);

        // Get single octave noise in [-1 ,1]
        double simpleNoise(double x, double y, double z);

    public:
        NoiseGenerator(
                int seed,
                int octaves,
                int frequency,
                int amplitude,
                double persistence);

        // Get fractal noise in [0, 1]
        double noise(double x, double y, double z);

        // Set scaling factor end exponent for noise values
        void setScaling(double factor, double exponent);
};

#endif // !NOISE_H
