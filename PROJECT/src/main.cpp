#include <iostream>
#include <GLCore/Core/Core.hpp>

#include "ExampleLayer.hpp"
class ExampleApplication : public GLCore::Application {
    
public:
    ExampleApplication() : GLCore::Application("OpenGL_Example")
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