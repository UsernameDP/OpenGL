#include "GLCore/Core/Runner.hpp"

/*Examples*/
#include "Examples/Basic/BasicApp.hpp"

int main()
{
    GLCore::Runner<BasicApp> runner;
    runner.run();
    LOG("Program ended");


    return 0;
}