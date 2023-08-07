#include "GLCore/Core/Runner.hpp"

/*Examples*/
#include "Examples/Basic/BasicApp.hpp"

int main()
{
    GLCore::Runner<BasicApp> runner;
    runner.run();
    LOG("Program ended");

    std::cout << "how consistently?";

    return 0;
}