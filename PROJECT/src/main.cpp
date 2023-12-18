#include <iostream>
#include <GLCore/Core/Core.hpp>

#include "ExampleLayer.hpp"
class ExampleApplication : public GLCore::Application {
    
public:
    ExampleApplication() : GLCore::Application("OpenGL_Example", 1280, 960, glm::vec4(0.0, 0.0, 0.0, 1.0))
    {

    }
       

    virtual void init() override {
        pushLayer(new ExampleLayer());
    }
};

int main()
{
    std::unique_ptr<GLCore::Application> app = std::make_unique<ExampleApplication>();
    app->init();
    
    app->run();
}