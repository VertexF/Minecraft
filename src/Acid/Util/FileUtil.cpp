#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace acid 
{
    std::string getFileContents(const std::string& filePath) 
    {
        std::ifstream inFile(filePath);
        if (inFile.is_open() == false) 
        {
            throw std::runtime_error("Unable to open file: " + filePath);
        }

        std::stringstream stream;
        stream << inFile.rdbuf();
        return stream.str();
    }
}