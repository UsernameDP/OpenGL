#pragma once
#include "GLCoreAssetPool.hpp"

using namespace GLCore;

class BasicAssetPoolINIT : public util::AssetPoolINIT {
	
	void configure() override {
		util::AssetPool::setShader(
			new Shaders::VertexPipelineShader(
			"SquareShader",
			"OpenGL-Examples\\assets\\shaders\\Square.vert",
			"OpenGL-Examples\\assets\\shaders\\Square.frag"
		));
	}
};