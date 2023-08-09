#pragma once
#include "GLCoreAssetPool.hpp"
using namespace GLCore;
class BasicAssetPoolINIT_GLSLSrcs : public util::AssetPoolINIT_GLSLSrcs {
public:
  void configure() override {
    util::AssetPool::setGLSLSrc("OpenGL-Examples\\assets\\shaders\\Square.frag",
                                "#version 330 core\n"
                                "\n"
                                "in vec3 fColor;\n"
                                "out vec4 color;\n"
                                "\n"
                                "void main()\n"
                                "{\n"
                                "	color = vec4(fColor, 1.0);\n"
                                "}");
    util::AssetPool::setGLSLSrc("OpenGL-Examples\\assets\\shaders\\Square.vert",
                                "#version 330 core\n"
                                "layout (location = 0) in vec2 aPos;\n"
                                "layout (location = 1) in vec3 aColor;\n"
                                "\n"
                                "out vec3 fColor;\n"
                                "\n"
                                "void main()\n"
                                "{\n"
                                "    fColor = aColor;\n"
                                "\n"
                                "    gl_Position = vec4(aPos, 1.0, 1.0);\n"
                                "}");
  }
};
