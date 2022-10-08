#include "World.h"

#include "../Renderer/RenderMaster.h"
#include "../Source/Camera.h"
#include "Chunk/Chunk.h"
#include "../Source/Camera.h"

namespace 
{
    constexpr int RENDER_DISTACE = 20;
    constexpr float GRAV = -3;
}

namespace acid
{
    World::World() : 
        _chunkManager(*this)
    {
    }

    ChunkBlock World::getBlock(int x, int y, int z)
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        return _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).getBlock(blockPosition.x, y, blockPosition.z);
    }

    void World::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        auto blockPosition = getBlockXZ(x, z);
        auto chunkPosition = getChunkXZ(x, z);

        _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).setBlock(blockPosition.x, y, blockPosition.z, block);
    }

    void World::update(const Camera& camera)
    {
        for (auto& event : _events)
        {
            event->handle(*this);
        }
        _events.clear();

        updateChunks();

        for (int x = 0; x < RENDER_DISTACE; x++)
        {
            for (int z = 0; z < RENDER_DISTACE; z++) 
            {
                if (_chunkManager.makeMesh(x, z)) 
                {
                    return;
                }
            }
        }
    }

    void World::updateChunk(int blockX, int blockY, int blockZ)
    {
        auto addChunkToUpdateBatch = [&](const sf::Vector3i& key, ChunkSection& section) 
        {
            _chunkUpdates.emplace(key, &section);
        };

        auto chunkPosition = getChunkXZ(blockX, blockZ);
        auto chunkY = blockY / CHUNK_SIZE;

        sf::Vector3i  key(chunkPosition.x, chunkY, chunkPosition.z);
        addChunkToUpdateBatch(key, _chunkManager.getChunk(chunkPosition.x, chunkPosition.z).getSection(chunkY));

        auto sectionBlockXZ = getBlockXZ(blockX, blockZ);
        auto sectionBlockY = blockY % CHUNK_SIZE;

        if (sectionBlockXZ.x == 0) 
        {
            sf::Vector3i newKey(chunkPosition.x - 1, chunkY, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        else if (sectionBlockXZ.x == CHUNK_SIZE - 1) 
        {
            sf::Vector3i newKey(chunkPosition.x + 1, chunkY, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }

        if (sectionBlockY == 0)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY - 1, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        else if (sectionBlockY == CHUNK_SIZE - 1)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY + 1, chunkPosition.z);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }

        if (sectionBlockXZ.z == 0)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY, chunkPosition.z - 1);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
        else if (sectionBlockXZ.z == CHUNK_SIZE - 1)
        {
            sf::Vector3i newKey(chunkPosition.x, chunkY, chunkPosition.z + 1);
            addChunkToUpdateBatch(newKey, _chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
        }
    }

    void World::renderWorld(RenderMaster& master) 
    {
        master.drawSky();

        std::unordered_map<VectorXZ, Chunk, hash<VectorXZ>>& chunkMap = _chunkManager.getChunks();
        for(auto& chunk : chunkMap)
        {
            chunk.second.drawChunks(master);
        }
    }

    const ChunkManager& World::getChunkManager() const 
    {
        return _chunkManager;
    }

    VectorXZ World::getBlockXZ(int x, int z) 
    {
        return
        {
            x % CHUNK_SIZE,
            z % CHUNK_SIZE
        };
    }

    VectorXZ World::getChunkXZ(int x, int z) 
    {
        return
        {
            x / CHUNK_SIZE,
            z / CHUNK_SIZE
        };
    }

    void World::collisionTest(Entity& entity) 
    {
    }

    void World::updateChunks() 
    {
        for (auto& newChunk : _chunkUpdates)
        {
            ChunkSection& section = *newChunk.second;
            section.makeMesh();
        }
        _chunkUpdates.clear();
    }
}