#include <iostream>

int main()
{
#ifdef RELEASE
    while (true)
    {
        std::cout << "Hello World in [RELEASE] mode!!" << std::endl;
    }
#endif
#ifndef RELEASE
    while (true)
    {
        std::cout << "Hello World in [DEBUG OR DEFAULT] mode!!" << std::endl;
    }
#endif
}