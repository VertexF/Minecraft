#include "World.h"

namespace acid
{
    World::World() : _chunk(*this)
    {
    }

    ChunkBlock World::getBlock(int x, int y, int z) const
    {
    }

    void World::setBlock(int x, int y, int z, const ChunkBlock& block)
    {
    }

    void World::renderWorld(RenderMaster& master) 
    {
    }
}