// #include <iostream>

// #include "ExampleLayer.hpp"

// class ExampleApplication : public GLCore::Application
// {

// public:
//   ExampleApplication(const GLCore::WindowProps &props) : GLCore::Application(props)
//   {
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     glEnable(GL_DEPTH_TEST);
//   }

//   virtual void init() override
//   {
//     Extension::AssetPool::setShader(new Extension::Shaders::VertexPipelineShader("Cube", "cube.vert", "cube.frag"));
//     Extension::AssetPool::setShader(new Extension::Shaders::VertexPipelineShader("Axis", "axis.vert", "axis.frag"));
//     Extension::AssetPool::setComputeShader(new Extension::Shaders::ComputeShader("Point", "point.comp"));

//     pushLayer(new ExampleLayer());
//   }
// };

// int main()
// {
//   GLCore::WindowProps props = GLCore::WindowProps("PROJECT");
//   props.disableVsync();

//   std::unique_ptr<GLCore::Application> app = std::make_unique<ExampleApplication>(props);
//   app->init();
//   app->run();
// }

#include <memory>
#include <vector>
#include <unordered_map>

// #include "GLCore/Extension/Cameras/PerspectiveCamera.hpp"
// #include "GLCore/Extension/Cameras/PerspectiveCameraProps.hpp"
// #include <GLFW/glfw3.h>

// #include "GLCore/Extension/Shaders/Shader.hpp"
// #include "GLCore/Extension/Shaders/ComputeShader.hpp"
// #include "GLCore/Extension/Shaders/VertexPipelineShader.hpp"

// #include "GLCore/Extension/AssetPool.hpp"

// #include "GLCore/Core/Layer.hpp"
// #include "GLCore/Core/Application.hpp"

// #include "GLCore/Extension/Primitives/VBO.hpp"
// #include "GLCore/Extension/Primitives/VAO.hpp"
// #include "GLCore/Extension/Primitives/EBO.hpp"
// #include "GLCore/Extension/Primitives/SSBO.hpp"

#include <GLFW/glfw3.h>
#include "GLCore/Extension/Primitives/VBO.hpp"

class Testing
{

private:
  GLuint ID;

public:
  template <typename T>
  Testing()
  {
    glGenBuffers(1, &ID);
  }
};

int main()
{

  return 0;
}