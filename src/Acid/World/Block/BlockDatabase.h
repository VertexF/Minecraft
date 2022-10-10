#ifndef BLOCK_DATABASE_HDR
#define BLOCK_DATABASE_HDR

#include <memory>
#include <array>

#include "BlockType/BlockType.h"
#include "BlockID.h"
#include "../../Texture/TextureAtlas.h"

namespace acid 
{
    class BlockDatabase 
    {
    public:
        BlockDatabase();

        const BlockType& getBlock(BlockID id) const;
        const BlockData& getData(BlockID id) const;

        TextureAtlas textureAtlas;
    private:
        std::array<std::unique_ptr<BlockType>, static_cast<unsigned>(BlockID::NUM_TYPES)> _blocks;
    };
}

#endif // !BLOCK_DATABASE_HDR
