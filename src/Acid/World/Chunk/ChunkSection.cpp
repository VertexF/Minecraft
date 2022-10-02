#include "ChunkSection.h"

namespace acid
{
    ChunkSection::ChunkSection()
    {
        _location = { 0, 0, 0 };
    }

    void ChunkSection::setBlock(int x, int y, int z, const ChunkBlock& block) 
    {
        if (outOfBounds(x)) 
        {
            return;
        }
        if (outOfBounds(y))
        {
            return;
        }
        if (outOfBounds(z))
        {
            return;
        }

        _blocks[getIndex(x, y, z)] = block;
    }

    ChunkBlock ChunkSection::getBlock(int x, int y, int z) const 
    {
        if (outOfBounds(x))
        {
            return BlockID::AIR;
        }
        if (outOfBounds(y))
        {
            return BlockID::AIR;
        }
        if (outOfBounds(z))
        {
            return BlockID::AIR;
        }

        return _blocks[getIndex(x, y, z)];
    }

    const sf::Vector3i ChunkSection::getLocation() const
    {
        return _location;
    }

    bool ChunkSection::outOfBounds(int value) 
    {
        return (value >= CHUNK_SIZE || value < 0);
    }

    int ChunkSection::getIndex(int x, int y, int z) 
    {
        return (y * CHUNK_AREA + z * CHUNK_SIZE + x);
    }
}