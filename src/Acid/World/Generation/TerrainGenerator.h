#ifndef TERRAIN_GENERATOR_HDR
#define TERRAIN_GENERATOR_HDR

#include <array>

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"
#include "../../Util/Random.h"

#include "Biome.h"

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

        const IBoime& getBiome(int x, int z) const;

        static NoiseGenerator _biomeNoiseGen;

        Random<std::minstd_rand> _random;

        std::array<int, CHUNK_AREA> _heightMap;
        std::array<int, (CHUNK_SIZE + 1) * (CHUNK_SIZE + 1)> _biomeMap;

        GrasslandBiome _grassBiome;
        LightForestBiome _lightForest;
        DesertBoime _desertBiome;

        Chunk* _chunk = nullptr;
    };
}

#endif // !TERRAIN_GENERATOR_HDR
