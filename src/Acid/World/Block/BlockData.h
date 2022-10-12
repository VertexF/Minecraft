#ifndef BLOCK_DATA_HDR
#define BLOCK_DATA_HDR

#include <SFML/Graphics.hpp>
#include <string>

#include "../../Util/NonCopyable.h"
#include "BlockID.h"

namespace acid 
{
    enum class BlockMeshType 
    {
        CUBE,
        X
    };

    struct BlockDataHolder : public NonCopyable
    {
        BlockID id;
        sf::Vector2i texTopCoord;
        sf::Vector2i texSideCoord;
        sf::Vector2i texBottomCoord;

        BlockMeshType meshType;

        bool isOpaque;
    };

    class BlockData : public NonCopyable 
    {
    public:
        BlockData(const std::string& fileName);
        const BlockDataHolder& getBlockData() const;
    private:
        BlockDataHolder _data;
    };
}

#endif // !BLOCK_DATA_HDR
