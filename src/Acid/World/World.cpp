#include "World.h"

#include "../Renderer/RenderMaster.h"
#include "../Source/Camera.h"
#include "Chunk/Chunk.h"

namespace 
{
    constexpr int TEMP_WORLD_SIZE = 32;

    acid::VectorXZ getBlockXZ(int x, int z) 
    {
        return 
        {
            x % acid::CHUNK_SIZE,
            z % acid::CHUNK_SIZE
        };
    }

    acid::VectorXZ getChunkXZ(int x, int z)
    {
        return
        {
            static_cast<int>(x / acid::CHUNK_SIZE),
            static_cast<int>(z / acid::CHUNK_SIZE)
        };
    }

    bool isOutOfBounds(const acid::VectorXZ& chunkPosition)
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
    World::World() : 
        _chunkManager(*this)
    {
        for (int x = 0; x < TEMP_WORLD_SIZE; x++) 
        {
            for (int z = 0; z < TEMP_WORLD_SIZE; z++) 
            {
                _chunkManager.getChunk(x, z).load();
            }
        }
    }

    ChunkBlock World::getBlock(int x, int y, int z)
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        if (isOutOfBounds(chunkPosition)) 
        {
            return BlockID::AIR;
        }

        return _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).getBlock(blockPosition.x, y, blockPosition.z);
    }

    void World::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        if (y == 0) 
        {
            return;
        }

        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        if (isOutOfBounds(chunkPosition))
        {
            return;
        }

        auto& chunk = _chunkManager.getChunk(chunkPosition.x, chunkPosition.x);
        chunk.setBlock(blockPosition.x, y, blockPosition.z, block);
        if (chunk.hasLoaded()) 
        {
            _rebuildChunks.emplace(chunkPosition.x, y / CHUNK_SIZE, chunkPosition.z);
        }
    }

    void World::update(const Camera& camera)
    {
        for (int x = 0; x < TEMP_WORLD_SIZE; x++) 
        {
            for (int y = 0; y < TEMP_WORLD_SIZE; y++) 
            {
                if (_chunkManager.makeMesh(x, y)) 
                {
                    return;
                }
            }
        }
    }

    void World::renderWorld(RenderMaster& master) 
    {
        for (auto& location : _rebuildChunks) 
        {
            ChunkSection& section = _chunkManager.getChunk(location.x, location.z).getSection(location.y);
            section.makeMesh();
        }
        _rebuildChunks.clear();

        master.drawSky();

        const auto& chunkMap = _chunkManager.getChunks();
        for(auto& chunk : chunkMap)
        {
            chunk.second.drawChunks(master);
        }
    }
}