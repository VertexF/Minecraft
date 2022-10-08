#include "Chunk.h"

#include <array>

#include "../../Renderer/RenderMaster.h"
#include "../World.h"
#include "../../Source/Global.h"
#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"

namespace acid 
{
    Chunk::Chunk(World& world, const sf::Vector2i& location) : 
        _world(&world), _location(location), _isLoaded(false)
    {
    }

    bool Chunk::makeMesh()
    {
        for (int i = 0; i < _chunkSections.size(); i++)
        {
            if (_chunkSections.at(i)->hasMesh() == false)
            {
                _chunkSections.at(i)->makeMesh();
                return true;
            }
        }

        return false;
    }

    ChunkBlock Chunk::getBlock(int x, int y, int z) const
    {
        if (outOfBound(x, y, z))
        {
            return BlockID::AIR;
        }

        int bY = y % CHUNK_SIZE;

        return _chunkSections.at(y / CHUNK_SIZE)->getBlock(x, bY, z);
    }

    void Chunk::setBlock(int x, int y, int z, const ChunkBlock& block)
    {
        addSectionsBlockTarget(y);
        if (outOfBound(x, y, z))
        {
            return;
        }

        int bY = y % CHUNK_SIZE;
        _chunkSections.at(y / CHUNK_SIZE)->setBlock(x, bY, z, block);
    }

    void Chunk::drawChunks(RenderMaster& renderer)
    {
        for (int i = 0; i < _chunkSections.size(); i++)
        {
            if (_chunkSections.at(i)->hasMesh())
            {
                if (_chunkSections.at(i)->hasBuffered() == false) 
                {
                    _chunkSections.at(i)->bufferMesh();
                }

                renderer.drawChunk(_chunkSections.at(i)->getMesh());
            }
        }
    }

    bool Chunk::hasLoaded() const 
    {
        return _isLoaded;
    }

    void Chunk::load() 
    {
        static int seed = RANDOM_GENERATOR.intInRange(444, 444444);
        if (hasLoaded()) 
        {
            return;
        }

        Random<std::minstd_rand> rand((_location.x ^ _location.y) << 2);
        NoiseGenerator temp_noiseGen(seed);
        std::array<int, CHUNK_AREA> heightMap;
        std::vector<sf::Vector3i> treeLocation;

        int maxValue = 0;
        for (int x = 0; x < CHUNK_SIZE; x++) 
        {
            for (int z = 0; z < CHUNK_SIZE; z++) 
            {
                int h = temp_noiseGen.getHeight(x, z, _location.x + 10, _location.y + 10);
                heightMap[x * CHUNK_SIZE + z] = h;

                maxValue = std::max(maxValue, h);
            }
        }

        for (int y = 0; y < maxValue + 1; y++)
        {
            for (int x = 0; x < CHUNK_SIZE; x++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    int h = heightMap[x * CHUNK_SIZE + z];

                    if (y > h)
                    {
                        continue;
                    }
                    else if (y == h)
                    {
                        if (y > WATER_LEVEL) 
                        {
                            setBlock(x, y, z, BlockID::GRASS);
                            if (rand.intInRange(0, 150) == 0) 
                            {
                                treeLocation.emplace_back(x, y, z);
                            }
                        }
                        else 
                        {
                            setBlock(x, y, z, BlockID::GRASS);
                        }
                    }
                    else if(y > h - 3)
                    {
                        setBlock(x, y, z, BlockID::DIRT);
                    }
                    else 
                    {
                        setBlock(x, y, z, BlockID::STONE);
                    }
                }
            }
        }

        //tree
        for (auto& tree : treeLocation) 
        {
            int h = rand.intInRange(5, 9);
            for (int y = 0; y < h; y++)
            {
                setBlock(tree.x, tree.y + y, tree.z, BlockID::OAK_BARK);

                for (int x = -2; x < 2; x++) 
                {
                    for (int z = -2; z < 2; z++)
                    {
                        for (int y = 0; y < 3; y++)
                        {
                            setBlock(tree.x + x, tree.y + h + y, tree.z + z, BlockID::OAK_LEAF);
                        }
                    }
                }
            }
        }

        _isLoaded = true;
    }

    ChunkSection& Chunk::getSection(int index) 
    {
        return *_chunkSections.at(index);
    }

    void Chunk::addSection() 
    {
        int y = _chunkSections.size();
        _chunkSections.emplace_back(std::make_unique<ChunkSection>(sf::Vector3i(_location.x, y, _location.y), *_world));
    }

    void Chunk::addSectionsBlockTarget(int blockY) 
    {
        int index = blockY / CHUNK_SIZE;
        addSectionsIndexTarget(index);
    }

    void Chunk::addSectionsIndexTarget(int index) 
    {
        while (_chunkSections.size() < index + 1) 
        {
            addSection();
        }
    }

    bool Chunk::outOfBound(int x, int y, int z) const noexcept 
    {
        if (x >= CHUNK_SIZE)
        {
            return true;
        }
        if (z >= CHUNK_SIZE)
        {
            return true;
        }

        if (x < 0) 
        {
            return true;
        }
        if (y < 0)
        {
            return true;
        }
        if (z < 0)
        {
            return true;
        }

        if (y >= static_cast<int>(_chunkSections.size()) * CHUNK_SIZE) 
        {
            return true;
        }

        return false;
    }
}