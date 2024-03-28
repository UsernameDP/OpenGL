#include <iostream>

#include "ExampleLayer.hpp"
class ExampleApplication : public GLCore::Application {

public:
    ExampleApplication( const GLCore::WindowProps& props ) : GLCore::Application(props)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    virtual void init() override {

        Extension::AssetPool::setShader(new Extension::Shaders::VertexPipelineShader("Cube", "cube.vert", "cube.frag"));
        Extension::AssetPool::setShader(new Extension::Shaders::VertexPipelineShader("Axis", "axis.vert", "axis.frag"));
        Extension::AssetPool::setComputeShader(new Extension::Shaders::ComputeShader("Point", "point.comp"));

        pushLayer(new ExampleLayer());
    }
};

int main()
{
    GLCore::WindowProps props = GLCore::WindowProps("PROJECT");
    props.disableVsync();

    std::unique_ptr<GLCore::Application> app = std::make_unique<ExampleApplication>(props);
    app->init();
    app->run();
}
