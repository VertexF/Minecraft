#include "BlockData.h"

#include <fstream>
#include <stdexcept>

namespace acid 
{
    BlockData::BlockData(const std::string& fileName) 
    {
        std::ifstream inFile("Assets/Blocks/" + fileName + ".block");
        if (inFile.is_open() == false) 
        {
            throw std::runtime_error("Unable to open block file: " + fileName);
        }

        std::string line;
        while (std::getline(inFile, line)) 
        {
            if (line == "TexTop") 
            {
                int x, y;
                inFile >> x >> y;
                _data.texTopCoord = { x, y };
            }
            else if (line == "TexTop")
            {
                int x, y;
                inFile >> x >> y;
                _data.texBottomCoord = { x, y };
            }
            else if (line == "TexTop")
            {
                int x, y;
                inFile >> x >> y;
                _data.texSideCoord = { x, y };
            }
            else if (line == "TexTop")
            {
                int x, y;
                inFile >> x >> y;
                _data.texTopCoord = { x, y };
                _data.texSideCoord = { x, y };
                _data.texBottomCoord = { x, y };
            }
        }
    }

    const BlockDataHolder& BlockData::getBlockData() const
    {
        return _data;
    }
}