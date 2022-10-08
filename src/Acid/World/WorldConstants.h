#ifndef WORLD_CONSTANTS_HDR
#define WORLD_CONSTANTS_HDR

namespace acid 
{
    constexpr int CHUNK_SIZE = 16;
    constexpr int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
    constexpr int CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

    constexpr int WATER_LEVEL = 64;
}

#endif // !WORLD_CONSTANTS_HDR
