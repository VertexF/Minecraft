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
            else if (line == "TexSide")
            {
                int x, y;
                inFile >> x >> y;
                _data.texSideCoord = { x, y };
            }
            else if (line == "TexBottom")
            {
                int x, y;
                inFile >> x >> y;
                _data.texBottomCoord = { x, y };
            }
            else if (line == "TexAll")
            {
                int x, y;
                inFile >> x >> y;
                _data.texTopCoord = { x, y };
                _data.texSideCoord = { x, y };
                _data.texBottomCoord = { x, y };
            }
            else if (line == "Id")
            {
                int id;
                inFile >> id;
                _data.id = static_cast<BlockID>(id);
            }
            else if(line == "Opaque") 
            {
                inFile >> _data.isOpaque;
            }
            else if(line == "MeshType")
            {
                int id;
                inFile >> id;
                _data.meshType = static_cast<BlockMeshType>(id);
            }
        }
    }

    const BlockDataHolder& BlockData::getBlockData() const
    {
        return _data;
    }
}