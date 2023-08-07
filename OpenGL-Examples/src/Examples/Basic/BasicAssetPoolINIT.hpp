#pragma once
#include "GLCoreAssetPool.hpp"
#include "BasicAssetPoolINIT_GLSLSrcs.hpp"

using namespace GLCore;

class BasicAssetPoolINIT : public util::AssetPoolINIT {
	
	void configure() override {
		BasicAssetPoolINIT_GLSLSrcs GLSLSrcs_init;
		GLSLSrcs_init.configure();
		std::cout << *util::AssetPool::getGLSLSrc("C:\\Users\\Devin\\Downloads\\Code\\VS\\Cpp\\OpenGL\\OpenGL-Examples\\assets\\shaders\\Square.vert") << std::endl;
		util::AssetPool::setShader(
			new Shaders::VertexPipelineShader(
			"SquareShader",
			"OpenGL-Examples\\assets\\shaders\\Square.vert",
			"OpenGL-Examples\\assets\\shaders\\Square.frag"
		));
	}
};