#include "ChunkSection.h"

#include "../World.h"
#include "../../Source/Global.h"
#include "ChunkMeshBuilder.h"

namespace acid
{
    ChunkSection::ChunkSection(const sf::Vector3i& position, World& world) : 
        _location(position), _world(&world), _hasMesh(false), _hasBufferedMesh(false), _aabb({ CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE })
    {
        _aabb.update({_location.x * CHUNK_SIZE, _location.y * CHUNK_SIZE, _location.z * CHUNK_SIZE });
    }

    void ChunkSection::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
        {
            auto location = toWorldPosition(x, y, z);
            _world->setBlock(location.x, location.y, location.z, block);
            return;
        }

        _layers[y].update(block);
        _blocks[getIndex(x, y, z)] = block;
    }

    ChunkBlock ChunkSection::getBlock(int x, int y, int z) const
    {
        if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
        {
            auto location = toWorldPosition(x, y, z);
            return _world->getBlock(location.x, location.y, location.z);
        }

        int index = getIndex(x, y, z);
        return _blocks.at(index);
    }

    void ChunkSection::makeMesh()
    {
        ChunkMeshBuilder(*this, _mesh).buildMesh();
        _hasMesh = true;
        _hasBufferedMesh = false;
    }

    void ChunkSection::bufferMesh()
    {
        _mesh.bufferMesh();
        _hasBufferedMesh = true;
    }

    const sf::Vector3i ChunkSection::getLocation() const
    {
        return _location;
    }

    bool ChunkSection::hasMesh() const
    {
        return _hasMesh;
    }

    bool ChunkSection::hasBuffered() const
    {
        return _hasBufferedMesh;
    }

    void ChunkSection::setHasMesh(bool meshBool)
    {
        _hasMesh = meshBool;
    }

    const ChunkSection::Layer& ChunkSection::getLayer(int layer) const 
    {
        if (layer == -1)
        {
            return (_world->getChunkManager().getChunk(_location.x, _location.z).getSection(_location.y - 1).getLayer(CHUNK_SIZE - 1));
        }
        else if (layer == CHUNK_SIZE) 
        {
            return (_world->getChunkManager().getChunk(_location.x, _location.z).getSection(_location.y - 1).getLayer(0));
        }
        else 
        {
            return _layers[layer];
        }
    }

    ChunkSection& ChunkSection::getAdjacent(int dx, int dz) 
    {
        int newX = _location.x + dx;
        int newZ = _location.z + dz;

        return _world->getChunkManager().getChunk(newX, newZ).getSection(_location.y);
    }

    ChunkMesh &ChunkSection::getMesh()
    {
        return _mesh;
    }

    AABB ChunkSection::getCurrentAABB() const
    {
        return _aabb;
    }

    sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z) const
    {
        return
        {
            _location.x * CHUNK_SIZE + x,
            _location.y * CHUNK_SIZE + y,
            _location.z * CHUNK_SIZE + z
        };
    }

    bool ChunkSection::outOfBounds(int value) 
    {
        return (value >= CHUNK_SIZE || value < 0);
    }

    int ChunkSection::getIndex(int x, int y, int z) 
    {
        return (y * 
            CHUNK_AREA + z * 
            CHUNK_SIZE + x);
    }
}