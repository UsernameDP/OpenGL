#include <iostream>
#include "GLCore/Core/Log.hpp"

int main()
{
    GLCore::Log::init();
    while (true) {
        std::cout << "yessss" << std::endl;
    }
}