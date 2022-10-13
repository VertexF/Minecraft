#ifndef NOISE_GENERATOR_HDR
#define NOISE_GENERATOR_HDR

namespace acid 
{
    struct NoiseParameters 
    {
        int octaves;
        int amplitude;
        int smoothness;
        int heightOffset;

        double roughness;
    };

    class NoiseGenerator 
    {
    public:
        NoiseGenerator(int seed);

        double getHeight(int x, int z, int chunkX, int chunkZ) const noexcept;
        void setParameters(const NoiseParameters& params) noexcept;
    private:
        double getNoise(int n) const noexcept;
        double getNoise(double x, double z) const noexcept;

        double lerp(double a, double b, double z) const noexcept;

        double noise(double x, double z) const noexcept;

        NoiseParameters _noiseParameters;

        int _seed;
    };
}

#endif // !NOISE_GENERATOR_HDR
