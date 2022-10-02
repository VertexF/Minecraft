#ifndef BLOCK_TYPE_HDR
#define BLOCK_TYPE_HDR

#include <string>

#include "../../../Util/NonCopyable.h"
#include "../BlockData.h"

namespace acid 
{
    class BlockType : public NonCopyable
    {
    public:
        BlockType(const std::string& fileName);
        virtual ~BlockType() = default;

        const BlockData& getData() const;

    private:
        BlockData _data;
    };

    class DefaultBlock : public BlockType 
    {
    public:
        DefaultBlock(const std::string fileName) :
            BlockType(fileName) 
        {
        }
    };
}

#endif // !BLOCK_TYPE_HDR
