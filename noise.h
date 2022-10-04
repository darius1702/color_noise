#ifndef NOISE_H
#define NOISE_H

#define maxPrimeIndex 10

class NoiseGenerator {
    private:
        static std::array<std::array<int, 3>, maxPrimeIndex> m_primes;

        int m_octaves, m_frequency, m_amplitude;
        double m_persistence;

        double noise(int i, int x, int y);
        double interpolatedNoise(int i, double x, double y);
        double smoothedNoise(int i, int x, int y);
        double interpolate(double a, double b, double x);
    public:
        NoiseGenerator();
        NoiseGenerator(int octaves, int frequency, int amplitude, double persistence);

        // between -1 and 1
        double getNoise(double x, double y);

        // between 0 and 255
        int getNoiseNorm(double x, double y);
};

#endif // !NOISE_H
