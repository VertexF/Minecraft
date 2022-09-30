#include <iostream>

#include <memory>
#include "Source/Application.h"

int main() 
{
    std::unique_ptr<acid::Application> application = std::make_unique<acid::Application>();

    std::cout << "Hello world." << std::endl;
    return 0;
}