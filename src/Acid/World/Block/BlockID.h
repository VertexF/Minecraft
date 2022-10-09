#ifndef BLOCK_ID_HDR
#define BLOCK_ID_HDR

#include <cstdint>

namespace acid 
{
    enum class BlockID : uint8_t 
    {
        AIR = 0,
        GRASS,
        DIRT,
        STONE,
        OAK_BARK,
        OAK_LEAF,
        SAND,
        WATER,
        CACTUS,

        NUM_TYPES
    };
}

#endif // !BLOCK_ID_HDR
