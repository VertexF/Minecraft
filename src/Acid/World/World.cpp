#include "World.h"

#include "../Renderer/RenderMaster.h"

namespace 
{
    constexpr int TEMP_WORLD_SIZE = 8;

    struct VectorXZ 
    {
        int x, z;
    };

    VectorXZ getBlockXZ(int x, int z) 
    {
        return 
        {
            x % acid::CHUNK_SIZE,
            z % acid::CHUNK_SIZE
        };
    }

    VectorXZ getChunkXZ(int x, int z)
    {
        return
        {
            static_cast<int>(x / acid::CHUNK_SIZE),
            static_cast<int>(z / acid::CHUNK_SIZE)
        };
    }

    bool isOutOfBounds(const VectorXZ& chunkPosition)
    {
        if (chunkPosition.x < 0) 
        {
            return true;
        }
        if (chunkPosition.z < 0)
        {
            return true;
        }
        if (chunkPosition.x >= TEMP_WORLD_SIZE)
        {
            return true;
        }
        if (chunkPosition.z >= TEMP_WORLD_SIZE)
        {
            return true;
        }
        return false;
    }
}

namespace acid
{
    World::World()
    {
        for (int x = 0; x < TEMP_WORLD_SIZE; x++) 
        {
            for (int z = 0; z < TEMP_WORLD_SIZE; z++) 
            {
                addChunk(x, z);
            }
        }

        for(int i = 0; i < _chunks.size(); i++)
        {
            _chunks.at(i)->makeAllMesh();
        }
    }

    ChunkBlock World::getBlock(int x, int y, int z) const
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        if (isOutOfBounds(chunkPosition)) 
        {
            return BlockID::AIR;
        }

        return _chunks.at(chunkPosition.x * TEMP_WORLD_SIZE + chunkPosition.z)->getBlock(blockPosition.x, y, blockPosition.z);
    }

    void World::setBlock(int x, int y, int z, const ChunkBlock& block)
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        if (isOutOfBounds(chunkPosition))
        {
            return;
        }

        _chunks.at(chunkPosition.x * TEMP_WORLD_SIZE + chunkPosition.z)->setBlock(blockPosition.x, y, blockPosition.z, block);
    }

    void World::editBlock(int x, int y, int z, const ChunkBlock& block)
    {
        auto chunkPosition = getChunkXZ(x, z);

        if (isOutOfBounds(chunkPosition))
        {
            return;
        }

        setBlock(x, y, z, block);
        _changeChunks.emplace_back(_chunks.at(chunkPosition.x * TEMP_WORLD_SIZE + chunkPosition.z));
    }

    void World::addChunk(int x, int z) 
    {
        _chunks.emplace_back(std::make_shared<Chunk>(*this, sf::Vector2i(x, z)));
    }

    void World::renderWorld(RenderMaster& master) 
    {
        for (int i = 0; i < _changeChunks.size(); i++) 
        {
            _changeChunks.at(i)->makeAllMesh();
        }
        _changeChunks.clear();

        master.drawSky();

        for(int i = 0; i < _chunks.size(); i++)
        {
            _chunks.at(i)->drawChunks(master);
        }
    }
}