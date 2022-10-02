#include "BlockType.h"

namespace acid 
{
    BlockType::BlockType(const std::string& fileName) :
        _data(fileName)
    {
    }

    const BlockData& BlockType::getData() const 
    {
        return _data;
    }
}