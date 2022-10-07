#include "ChunkSection.h"

#include "../World.h"
#include "../../Source/Global.h"
#include "ChunkMeshBuilder.h"

namespace acid
{
    ChunkSection::ChunkSection(const sf::Vector3i& position, World& world) : 
        _location(position), _world(&world), _hasMesh(false)
    {
        static_assert(sizeof(_blocks) == CHUNK_VOLUME, "Too many blocks for the chunk size.");
    }

    void ChunkSection::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
        {
            auto location = toWorldPosition(x, y, z);
            _world->setBlock(location.x, location.y, location.z, block);
            return;
        }

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
        bufferMesh();
        _hasMesh = true;
    }

    void ChunkSection::bufferMesh()
    {
        _mesh.bufferMesh();
    }

    const sf::Vector3i ChunkSection::getLocation() const noexcept
    {
        return _location;
    }

    bool ChunkSection::hasMesh() const noexcept
    {
        return _hasMesh;
    }

    void ChunkSection::setHasMesh(bool meshBool)
    {
        _hasMesh = meshBool;
    }

    ChunkMesh &ChunkSection::getMesh()
    {
        return _mesh;
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