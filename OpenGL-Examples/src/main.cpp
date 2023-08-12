#include "GLCore/Core/Runner.hpp"

/*Examples*/
#include "Examples/Tutorial/Tutorial_App.hpp"

int main()
{
    GLCore::Runner<Tutorial_App> runner;
    runner.run();
    LOG("Program ended");


    return 0;
}
