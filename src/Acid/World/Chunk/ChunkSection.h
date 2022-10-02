#ifndef CHUNK_SECTION_HDR
#define CHUNK_SECTION_HDR

#include <array>

#include <SFML/Graphics.hpp>

#include "../WorldConstants.h"
#include "../Block/ChunkBlock.h"
#include "ChunkMesh.h"

namespace acid 
{
    class ChunkSection 
    {
    public:
        ChunkSection();

        void setBlock(int x, int y, int z, const ChunkBlock& block);
        ChunkBlock getBlock(int x, int y, int z) const;

        const sf::Vector3i getLocation() const;

        ChunkMesh mesh;
    private:
        static bool outOfBounds(int value);
        static int getIndex(int x, int y, int z);

        std::array<ChunkBlock, CHUNK_VOLUME> _blocks;

        sf::Vector3i _location;
    };
}

#endif // !CHUNK_SECTION_HDR
