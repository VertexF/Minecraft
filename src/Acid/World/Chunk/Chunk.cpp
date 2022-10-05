#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../Source/Global.h"

namespace acid 
{
    Chunk::Chunk(World& world, const sf::Vector2i& location) : 
        _world(&world), _location(location), _isLoaded(false)
    {
        for (int y = 0; y < 3; y++) 
        {
            _chunkSections.emplace_back(std::make_unique<ChunkSection>(sf::Vector3i(location.x, y, location.y), world));
        }

        int h = _chunkSections.size() * CHUNK_SIZE - 1;
        for (int y = 0; y < static_cast<int>(_chunkSections.size() * CHUNK_SIZE); y++)
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

    void Chunk::makeAllMesh()
    {
        for (int i = 0; i < _chunkSections.size(); i++)
        {
            if (_chunkSections.at(i)->hasMesh() == false)
            {
                ChunkMeshBuilder builder(*_chunkSections.at(i).get(), _chunkSections.at(i)->getMesh());
                builder.buildMesh();

                _chunkSections.at(i)->bufferMesh();
                _chunkSections.at(i)->setHasMesh(true);
            }
        }
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

    void Chunk::drawChunks(RenderMaster& renderer) 
    {
        for (int i = 0; i < _chunkSections.size(); i++)
        {
            if (_chunkSections.at(i)->hasMesh())
            {
                renderer.drawChunk(_chunkSections.at(i)->getMesh());
            }
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

        if (y >= static_cast<int>(_chunkSections.size() * CHUNK_SIZE)) 
        {
            return true;
        }

        return false;
    }
}