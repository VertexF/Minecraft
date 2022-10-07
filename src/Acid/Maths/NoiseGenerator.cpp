#include "NoiseGenerator.h"

#include <cmath>

#include "../World/WorldConstants.h"

namespace acid 
{
    NoiseGenerator::NoiseGenerator(int seed) :
        _seed(seed)
    {
        _noiseParameters.octaves = 7;
        _noiseParameters.amplitude = 85;
        _noiseParameters.smoothness = 235;
        _noiseParameters.heightOffset = -10;
        _noiseParameters.roughness = 0.51;
    }

    double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ) const 
    {
        auto newX = (x + (chunkX * CHUNK_SIZE));
        auto newZ = (z + (chunkZ * CHUNK_SIZE));

        auto totalValue = 0.0;

        //This loop through the octaves.
        for (int a = 0; a < _noiseParameters.octaves - 1; a++) 
        {
            //This increases the frequency with every loop of the octave.
            auto frequency = std::pow(2.0, a);
            //This decreases the amplitude with every loop of the octave.
            auto amplitude = std::pow(_noiseParameters.roughness, a);
            totalValue += noise(static_cast<double>(newX) * frequency / _noiseParameters.smoothness, 
                               (static_cast<double>(newZ) * frequency / _noiseParameters.smoothness)) * amplitude;
        }

        auto value = (((totalValue / 2.1) + 1.2) * _noiseParameters.amplitude) + _noiseParameters.heightOffset;

        return value > 0 ? value : 1;
    }

    double NoiseGenerator::getNoise(int n) const 
    {
        n += _seed;
        n = (n << 13) ^ n;
        auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7FFFFFFF;

        return 1.0 - (static_cast<double>(newN) / 1073741824.0);
    }

    double NoiseGenerator::getNoise(double x, double z) const 
    {
        return getNoise(x * z + 57);
    }

    double NoiseGenerator::lerp(double a, double b, double z) const 
    {
        double mu2 = (1 - std::cos(z * 3.14)) / 2;
        return (a * (1 - mu2) + b * mu2);
    }

    double NoiseGenerator::noise(double x, double z) const 
    {
        //This is a cheap way to get the follow of a double.
        auto floorX = static_cast<double>(static_cast<int>(x));
        auto floorZ = static_cast<double>(static_cast<int>(z));

        //Make these ints?
        double s = 0.0;
        double t = 0.0;
        double u = 0.0;
        double v = 0.0;

        //Get the surrounding values to calculate the transitions.
        s = getNoise(floorX, floorZ);
        t = getNoise(floorX + 1, floorZ);
        u = getNoise(floorX, floorZ + 1);
        v = getNoise(floorX + 1, floorZ + 1);

        //Interpolate between values.
        auto rec1 = lerp(s, t, x - floorX);
        //Here we use x-floorX, to get 1st dimension. Don't mind the x-floorX thingie, it's part of the cosine formula.
        auto rec2 = lerp(u, v, x - floorX);
        //Here we use y-floorZ, to get 2nd dimension.
        auto rec3 = lerp(rec1, rec2, z - floorZ);

        return rec3;
    }
}