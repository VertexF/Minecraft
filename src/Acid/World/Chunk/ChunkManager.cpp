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
        if (_chunks.find({x, z}) == _chunks.end())
        {
            VectorXZ key{x, z};
            Chunk chunk{ *_world, {x, z} };
            _chunks.emplace(key, std::move(chunk));
        }

        return _chunks.at({ x, z });
    }

    const std::unordered_map<VectorXZ, Chunk>& ChunkManager::getChunks() const 
    {
        return _chunks;
    }

    bool ChunkManager::makeMesh(int x, int z) 
    {
        return getChunk(x, z).makeMesh();
    }

    void ChunkManager::queueChunk(int x, int z) 
    {
    }

    void ChunkManager::update() 
    {
    }
}