#include "Chunk.h"

#include <array>

#include "../../Renderer/RenderMaster.h"
#include "../World.h"
#include "../../Source/Global.h"
#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../../Source/Camera.h"
#include "../../Physics/AABB.h"
#include "../../Maths/Frustum.h"
#include "../Generation/TerrainGenerator.h"

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

    ChunkBlock Chunk::getBlock(int x, int y, int z) const noexcept
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
        addSectionsBlockTarget(y);
        if (outOfBound(x, y, z))
        {
            return;
        }

        int bY = y % CHUNK_SIZE;
        _chunkSections.at(y / CHUNK_SIZE)->setBlock(x, bY, z, block);
    }

    void Chunk::drawChunks(RenderMaster& renderer, const Camera& camera)
    {
        for (int i = 0; i < _chunkSections.size(); i++)
        {
            if (_chunkSections.at(i)->hasMesh())
            {
                if (_chunkSections.at(i)->hasBuffered() == false) 
                {
                    _chunkSections.at(i)->bufferMesh();
                }

                if (camera.getViewFrustum().isBoxInFrustum(_chunkSections.at(i)->getCurrentAABB()))
                {
                    renderer.drawChunk(*_chunkSections.at(i));
                }
            }
        }
    }

    bool Chunk::hasLoaded() const noexcept
    {
        return _isLoaded;
    }

    void Chunk::load() 
    {
        if (hasLoaded()) 
        {
            return;
        }

        TerrianGenerator gen;
        gen.generateTerrianFor(*this);
        _isLoaded = true;
    }

    ChunkSection& Chunk::getSection(int index) 
    {
        static ChunkSection errorSection({ 444, 444, 444 }, *_world);
        if(index >= static_cast<int>(_chunkSections.size()) || index < 0)
        {
            return errorSection;
        }

        return *_chunkSections.at(index);
    }

    void Chunk::addSection() 
    {
        int y = _chunkSections.size();
        _chunkSections.emplace_back(std::make_unique<ChunkSection>(sf::Vector3i(_location.x, y, _location.y), *_world));
    }

    void Chunk::addSectionsBlockTarget(int blockY) 
    {
        int index = blockY / CHUNK_SIZE;
        addSectionsIndexTarget(index);
    }

    void Chunk::addSectionsIndexTarget(int index) 
    {
        while (static_cast<int>(_chunkSections.size()) < index + 1)
        {
            addSection();
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

        if (y >= static_cast<int>(_chunkSections.size()) * CHUNK_SIZE) 
        {
            return true;
        }

        return false;
    }
}