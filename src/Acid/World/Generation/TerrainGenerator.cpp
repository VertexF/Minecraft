#include "TerrainGenerator.h"

#include <functional>

#include "../Chunk/Chunk.h"
#include "../../Util/Random.h"

#include "TreeGenerator.h"
#include "Biome.h"
#include "../../Maths/GeneralMaths.h"
#include "../../Source/Global.h"

namespace acid 
{
    namespace
    {
        int seed = RANDOM_GENERATOR.intInRange(424, 325322);
    }

    NoiseGenerator TerrianGenerator::_biomeNoiseGen(seed * 2);

    TerrianGenerator::TerrianGenerator() : _grassBiome(seed), _lightForest(seed), _desertBiome(seed), _oceanBiome(seed)
    {
        setUpNoise();
    }

    void TerrianGenerator::generateTerrianFor(Chunk& chunk) 
    {
        _chunk = &chunk;

        auto location = chunk.getLocation();
        _random.setSeed((location.x ^ location.y) << 2);

        getBiomeMap();
        getHeightMap();

        auto maxHeight = _heightMap.getMaxValue();
        maxHeight = std::max(maxHeight, WATER_LEVEL);
        setBlock(maxHeight);
    }

    void TerrianGenerator::getHeightIn(int xMin, int zMin, int xMax, int zMax)
    {
        auto getHeightAt = [&](int x, int z)
        {
            const Biome& biome = getBiome(x, z);

            return biome.getHeight(x, z, _chunk->getLocation().x, _chunk->getLocation().y);
        };

        int bottomLeft = getHeightAt(xMin, zMin);
        int bottomRight = getHeightAt(xMax, zMin);
        int topLeft = getHeightAt(xMin, zMax);
        int topRight = getHeightAt(xMax, zMax);

        for (int x = xMin; x < xMax; ++x) 
        {
            for (int z = zMin; z < zMax; ++z)
            {
                if (x == CHUNK_SIZE) 
                {
                    continue;
                }
                if (z == CHUNK_SIZE) 
                {
                    continue;
                }

                int height = bilinearInterpolation(bottomLeft, topLeft, bottomRight, topRight,
                                                   xMin, xMax, zMin, zMax, x, z);

                _heightMap.get(x, z) = height;
            }
        }
    }

    void TerrianGenerator::setBlock(int height) 
    {
        std::vector<sf::Vector3i> trees;
        std::vector<sf::Vector3i> plants;

        for (int y = 0; y < height + 1; y++)
        {
            for (int x = 0; x < CHUNK_SIZE; x++) 
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    int height = _heightMap.get(x, z);
                    auto& biome = getBiome(x, z);

                    if (y > height) 
                    {
                        if (y <= WATER_LEVEL) 
                        {
                            _chunk->setBlock(x, y, z, BlockID::WATER);
                        }
                        continue;
                    }
                    else if (y == height) 
                    {
                        if (y >= WATER_LEVEL) 
                        {
                            if (y < WATER_LEVEL + 5) 
                            {
                                _chunk->setBlock(x, y, z, BlockID::SAND);
                                continue;
                            }

                            if (_random.intInRange(0, biome.getTreeFrequency()) == 5)
                            {
                                trees.emplace_back(x, y + 1, z);
                            }
                            if (_random.intInRange(0, biome.getPlantFrequency()) == 5)
                            {
                                plants.emplace_back(x, y + 1, z);
                            }
                            setTopBlock(x, y, z);
                        }
                        else 
                        {
                            _chunk->setBlock(x, y, z, _random.intInRange(0, 10) < 5 ? BlockID::SAND : BlockID::DIRT);
                        }
                    }
                    else if (y > height - 3) 
                    {
                        _chunk->setBlock(x, y, z, BlockID::DIRT);
                    }
                    else 
                    {
                        _chunk->setBlock(x, y, z, BlockID::STONE);
                    }
                }
            }
        }

        for (auto& tree : trees) 
        {
            int x = tree.x;
            int z = tree.z;

            getBiome(x, z).makeTree(_random, *_chunk, x, tree.y, z);
        }

        for (auto& plant : plants)
        {
            int x = plant.x;
            int z = plant.z;

            auto block = getBiome(x, z).getPlant(_random);
            _chunk->setBlock(x, plant.y, z, block);
        }
    }

    const Biome& TerrianGenerator::getBiome(int x, int z) const
    {
        int biomeValue = _biomeMap.get(x, z);

        if(biomeValue > 155)
        {
            return _oceanBiome;
        }
        else if (biomeValue > 145) 
        {
            return _lightForest;
        }
        else if (biomeValue > 110)
        {
            return _grassBiome;
        }
        else 
        {
            return _desertBiome;
        }
    }

    void TerrianGenerator::setTopBlock(int x, int y, int z) 
    {
        _chunk->setBlock(x, y, z, getBiome(x, z).getTopBlock(_random));
    }

    void TerrianGenerator::getHeightMap() 
    {
        constexpr static auto HALF_CHUNK = CHUNK_SIZE / 2;
        constexpr static auto CHUNK = CHUNK_SIZE;

        getHeightIn(0, 0, HALF_CHUNK, HALF_CHUNK);
        getHeightIn(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
        getHeightIn(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
        getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
    }

    void TerrianGenerator::getBiomeMap() 
    {
        auto location = _chunk->getLocation();

        for (int x = 0; x < CHUNK_SIZE + 1; x++)
        {
            for (int z = 0; z < CHUNK_SIZE + 1; z++)
            {
                int height = _biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
                _biomeMap.get(x, z) = height;
            }
        }
    }

    void TerrianGenerator::setUpNoise() 
    {
        static bool noiseGen = false;
        if (noiseGen == false) 
        {
            noiseGen = true;

            NoiseParameters biomeParams;
            biomeParams.octaves = 5;
            biomeParams.amplitude = 125;
            biomeParams.smoothness = 735;
            biomeParams.heightOffset = -5;
            biomeParams.roughness = 0.6;

            _biomeNoiseGen.setParameters(biomeParams);
        }
    }
}