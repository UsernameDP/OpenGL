#include "GLCore/Core/Runner.hpp"

/*GLCoreExamples*/
#include "Examples/LorenzComputeShader/App.hpp"

int main()
{
    GLCore::Runner<Lorenz_App> runner;
    runner.run();
    LOG("Program ended");

    return 0;
}
