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
        _blocks[static_cast<int>(BlockID::OAK_BARK)] = std::make_unique<DefaultBlock>("OakBark");
        _blocks[static_cast<int>(BlockID::OAK_LEAF)] = std::make_unique<DefaultBlock>("OakLeaf");
        _blocks[static_cast<int>(BlockID::SAND)] = std::make_unique<DefaultBlock>("Sand");
        _blocks[static_cast<int>(BlockID::WATER)] = std::make_unique<DefaultBlock>("Water");
        _blocks[static_cast<int>(BlockID::CACTUS)] = std::make_unique<DefaultBlock>("Cactus");
        _blocks[static_cast<int>(BlockID::ROSE)] = std::make_unique<DefaultBlock>("Rose");
        _blocks[static_cast<int>(BlockID::DEADSHRUB)] = std::make_unique<DefaultBlock>("DeadShrub");
        _blocks[static_cast<int>(BlockID::TALLGRASS)] = std::make_unique<DefaultBlock>("TallGrass");
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