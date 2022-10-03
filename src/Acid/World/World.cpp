#include "World.h"

namespace 
{
    constexpr int TEMP_WORLD_SIZE = 8;
}

namespace acid
{
    World::World()
    {
        for (int x = 0; x < TEMP_WORLD_SIZE; x++) 
        {
            for (int z = 0; z < TEMP_WORLD_SIZE; z++) 
            {
                _chunks.emplace_back(std::make_unique<Chunk>(*this, sf::Vector2i(x, z)));
            }
        }

        for(int i = 0; i < _chunks.size(); i++)
        {
            _chunks.at(i)->makeAllMeshtemp();
        }
    }

    ChunkBlock World::getBlock(int x, int y, int z) const
    {
        int bX = x % CHUNK_SIZE;
        int bZ = z % CHUNK_SIZE;

        int cX = static_cast<int>(x / CHUNK_SIZE);
        int cZ = static_cast<int>(z / CHUNK_SIZE);

        if (cX < 0) 
        {
            return BlockID::AIR;
        }
        if (cZ < 0)
        {
            return BlockID::AIR;
        }
        if (cX >= TEMP_WORLD_SIZE)
        {
            return BlockID::AIR;
        }
        if (cZ >= TEMP_WORLD_SIZE)
        {
            return BlockID::AIR;
        }

        return _chunks.at(cX * TEMP_WORLD_SIZE + cZ)->getBlock(bX, y, bZ);
    }

    void World::setBlock(int x, int y, int z, const ChunkBlock& block)
    {
        int bX = x % CHUNK_SIZE;
        int bZ = z % CHUNK_SIZE;

        int cX = static_cast<int>(x / CHUNK_SIZE);
        int cZ = static_cast<int>(z / CHUNK_SIZE);

        if (cX < 0)
        {
            return;
        }
        if (cZ < 0)
        {
            return;
        }
        if (cX >= TEMP_WORLD_SIZE)
        {
            return;
        }
        if (cZ >= TEMP_WORLD_SIZE)
        {
            return;
        }

        _chunks.at(cX * TEMP_WORLD_SIZE + cZ)->setBlock(bX, y, bZ, block);
    }

    void World::editBlock(int x, int y, int z, const ChunkBlock& block)
    {
        int cX = static_cast<int>(x / CHUNK_SIZE);
        int cZ = static_cast<int>(z / CHUNK_SIZE);

        if (cX < 0)
        {
            return;
        }
        if (cZ < 0)
        {
            return;
        }
        if (cX >= TEMP_WORLD_SIZE)
        {
            return;
        }
        if (cZ >= TEMP_WORLD_SIZE)
        {
            return;
        }

        setBlock(x, y, z, block);
        _chunks.at(cX * TEMP_WORLD_SIZE + cZ)->makeAllMeshtemp();
    }

    void World::renderWorld(RenderMaster& master) 
    {
        for(int i = 0; i < _chunks.size(); i++)
        {
            _chunks.at(i)->drawChunks(master);
        }
    }
}