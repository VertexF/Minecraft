#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"

namespace acid 
{
    Chunk::Chunk(World& world, const sf::Vector2i& location) : 
        _world(&world), _location(location)
    {
        for (int y = 0; y < 3; y++) 
        {
            _chunks.emplace_back(std::make_unique<ChunkSection>(sf::Vector3i(location.x, y, location.y), world));
        }

        int h = _chunks.size() * CHUNK_SIZE - 1;
        for (int y = 0; y < static_cast<int>(_chunks.size() * CHUNK_SIZE); y++) 
        {
            for (int x = 0; x < 16; x++) 
            {
                for (int z = 0; z < 16; z++)
                {
                    if (y == h) 
                    {
                        setBlock(x, y, z, BlockID::GRASS);
                    }
                    else if (y > h - 3) 
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
    }

    void Chunk::makeAllMeshtemp()
    {
        for (int i = 0; i < _chunks.size(); i++)
        {
            ChunkMeshBuilder builder(*_chunks.at(i).get());
            builder.buildMesh(_chunks.at(i)->_mesh);
            _chunks.at(i)->_mesh.bufferMesh();
        }
    }

    ChunkBlock Chunk::getBlock(int x, int y, int z) const 
    {
        if (outOfBound(x, y, z))
        {
            return BlockID::AIR;
        }

        int bY = y % CHUNK_SIZE;

        return _chunks.at(y / CHUNK_SIZE)->getBlock(x, bY, z);
    }

    void Chunk::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        if (outOfBound(x, y, z))
        {
            return;
        }

        int bY = y % CHUNK_SIZE;
        _chunks.at(y / CHUNK_SIZE)->setBlock(x, bY, z, block);
    }

    void Chunk::drawChunks(RenderMaster& renderer) 
    {
        for (int i = 0; i < _chunks.size(); i++)
        {
            renderer.drawChunk(_chunks.at(i)->_mesh);
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

        if (y >= static_cast<int>(_chunks.size() * CHUNK_SIZE)) 
        {
            return true;
        }

        return false;
    }
}