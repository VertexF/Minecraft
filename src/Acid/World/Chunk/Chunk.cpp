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
        if (outOfBound(x, y, z))
        {
            return;
        }

        int bY = y % CHUNK_SIZE;
        _chunkSections.at(y / CHUNK_SIZE)->setBlock(x, bY, z, block);
    }

    void Chunk::drawChunks(RenderMaster& renderer) const
    {
        for (int i = 0; i < _chunkSections.size(); i++)
        {
            if (_chunkSections.at(i)->hasMesh())
            {
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
        static Random<std::minstd_rand> rand(500);
        NoiseGenerator temp_noiseGen(6345);
        std::array<int, CHUNK_AREA> heightMap;
        std::vector<sf::Vector3i> treeLocation;

        int maxValue = 0;
        for (int x = 0; x < CHUNK_SIZE; x++) 
        {
            for (int z = 0; z < CHUNK_SIZE; z++) 
            {
                int h = temp_noiseGen.getHeight(x, z, _location.x, _location.y);
                heightMap[x * CHUNK_SIZE + z] = h;

                maxValue = std::max(maxValue, h);
            }
        }

        for (int y = 0; y < maxValue / CHUNK_SIZE + 1; y++)
        {
            _chunkSections.emplace_back(std::make_unique<ChunkSection>(sf::Vector3i(_location.x, _chunkSections.size(), _location.y), *_world));
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
                        setBlock(x, y, z, BlockID::AIR);
                    }
                    else if (y == h)
                    {
                        setBlock(x, y, z, BlockID::GRASS);
                        if (rand.intInRange(0, 100) == 10) 
                        {
                            treeLocation.emplace_back(x, y, z);
                        }
                    }
                    else
                    {
                        setBlock(x, y, z, BlockID::DIRT);
                    }
                }
            }
        }

        //tree
        //for (auto& tree : treeLocation) 
        //{
        //    
        //}

        _isLoaded = true;
    }

    ChunkSection& Chunk::getSection(int index) 
    {
        while (index >= static_cast<int>(_chunkSections.size()))
        {
            _chunkSections.emplace_back(std::make_unique<ChunkSection>(sf::Vector3i(_location.x, _chunkSections.size(), _location.y), *_world));
        }

        return *_chunkSections.at(index);
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

        if (y >= static_cast<int>(_chunkSections.size() * CHUNK_SIZE)) 
        {
            return true;
        }

        return false;
    }
}