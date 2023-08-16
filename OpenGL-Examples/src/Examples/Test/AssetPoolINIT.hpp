#pragma once
#include "GLCoreAssetPool.hpp"

using namespace GLCore;

class AssetPoolINIT : public util::AssetPoolINIT {
	
	void configure() override {
		util::AssetPool::setShader(
			new Shaders::VertexPipelineShader(
			"SquareShader",
			"OpenGL-Examples\\assets\\shaders\\Square.vert",
			"OpenGL-Examples\\assets\\shaders\\Square.frag"
		));
		util::AssetPool::setShader(
			new Shaders::VertexPipelineShader(
				"CubeShader",
				"OpenGL-Examples\\assets\\shaders\\Cube.vert",
				"OpenGL-Examples\\assets\\shaders\\Cube.frag"
			)
		);
	}
};