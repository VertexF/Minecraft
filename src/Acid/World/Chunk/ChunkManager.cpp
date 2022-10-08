#include "ChunkManager.h"

#include "../World.h"

namespace acid 
{
    ChunkManager::ChunkManager(World& world) :
        _world(&world)
    {
    }

    Chunk& ChunkManager::getChunk(int x, int z)
    {
        if (chunkExistsAt(x, z) == false)
        {
            VectorXZ key{ x, z };
            Chunk chunk({ *_world, {x, z} });
            _chunks.emplace(key, std::move(chunk));
        }

        return _chunks.at({ x, z });
    }

    std::unordered_map<VectorXZ, Chunk, hash<VectorXZ>>& ChunkManager::getChunks()
    {
        return _chunks;
    }

    bool ChunkManager::makeMesh(int x, int z) 
    {
        for (int nx = -1; nx <= 1; nx++) 
        {
            for (int nz = -1; nz <= 1; nz++) 
            {
                getChunk(x + nx, z + nz).load();
            }
        }

        return getChunk(x, z).makeMesh();
    }

    bool ChunkManager::chunkLoadedAt(int x, int z) const 
    {
        if (chunkExistsAt(x, z) == false)
        {
            return false;
        }

        return _chunks.at({ x, z }).hasLoaded();
    }

    bool ChunkManager::chunkExistsAt(int x, int z) const 
    {
        return (_chunks.find({ x, z }) != _chunks.end());
    }

    void ChunkManager::loadChunk(int x, int z) 
    {
        getChunk(x, z).load();
    }

    void ChunkManager::unloadChunk(int x, int z) 
    {
        //Save to a file or something.
    }
}