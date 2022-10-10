#ifndef TERRAIN_GENERATOR_HDR
#define TERRAIN_GENERATOR_HDR

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"

#include "../../Util/Array2D.h"
#include "../../Util/Random.h"

#include "Biome.h"
#include "GrasslandBiome.h"
#include "DesertBiome.h"
#include "TemperateForestBiome.h"
#include "OceanBiome.h"

namespace acid 
{
    class Chunk;

    class TerrianGenerator 
    {
    public:
        TerrianGenerator();

        void generateTerrianFor(Chunk& chunk);
    private:
        static void setUpNoise();

        void setBlock(int height);
        void setTopBlock(int x, int y, int z);

        void getHeightIn(int xMin, int zMin, int xMax, int zMax);
        void getHeightMap();
        void getBiomeMap();

        const Biome& getBiome(int x, int z) const;

        static NoiseGenerator _biomeNoiseGen;

        Random<std::minstd_rand> _random;

        Array2D<int, CHUNK_SIZE> _heightMap;
        Array2D<int, CHUNK_SIZE + 1> _biomeMap;

        GrasslandBiome _grassBiome;
        TemperateForestBiome _lightForest;
        DesertBoime _desertBiome;
        OceanBiome _oceanBiome;

        Chunk* _chunk = nullptr;
    };
}

#endif // !TERRAIN_GENERATOR_HDR
