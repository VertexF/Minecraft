#include "BlockDatabase.h"

namespace acid 
{
    BlockDatabase::BlockDatabase() :
        textureAtlas("DefaultPack")
    {
        _blocks[static_cast<int>(BlockID::AIR)] = std::make_unique<DefaultBlock>("Air");
        _blocks[static_cast<int>(BlockID::GRASS)] = std::make_unique<DefaultBlock>("Grass");
        _blocks[static_cast<int>(BlockID::DIRT)] = std::make_unique<DefaultBlock>("Dirt");
        _blocks[static_cast<int>(BlockID::STONE)] = std::make_unique<DefaultBlock>("Stone");
    }

    const BlockType& BlockDatabase::getBlock(BlockID id) const 
    {
        return *_blocks[static_cast<int>(id)];
    }

    const BlockData& BlockDatabase::getData(BlockID id) const 
    {
        return _blocks[static_cast<int>(id)]->getData();
    }
}