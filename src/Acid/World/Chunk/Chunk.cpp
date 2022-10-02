#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "ChunkMeshBuilder.h"

namespace acid 
{
    Chunk::Chunk(World& world) 
    {
        for (int y = 0; y < 5; y++) 
        {
            _chunks.emplace_back(sf::Vector3i(0, y, 0), world);
            auto& chunk = _chunks.back();

            ChunkMeshBuilder builder(chunk);
            builder.buildMesh(chunk.mesh);
            chunk.mesh.bufferMesh();
        }
    }

    ChunkBlock Chunk::getBlock(int x, int y, int z) const 
    {
        if (outOfBound(x, y, z))
        {
            return BlockID::AIR;
        }

        int bY = y % CHUNK_SIZE;

        return _chunks.at(y / CHUNK_SIZE).getBlock(x, bY, z);
    }

    void Chunk::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        if (outOfBound(x, y, z))
        {
            return;
        }
    }

    void Chunk::drawChunks(RenderMaster& renderer) 
    {
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

        if (y >= static_cast<int>(_chunks.size() * CHUNK_SIZE)) 
        {
            return true;
        }

        return false;
    }
}