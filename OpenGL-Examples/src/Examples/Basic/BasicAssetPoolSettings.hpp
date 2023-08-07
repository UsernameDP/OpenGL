#pragma once
#include "GLCore/Extension/util/AssetPoolSettings.hpp"
#include "GLCore/Extension/util/AssetPool.hpp"

#include "GLCore/Extension/Shaders/VertexPipelineShader.hpp"

using namespace GLCore;

class BasicAssetPoolSettings : public util::AssetPoolSettings {
	
	void run() override {
		util::AssetPool::setShader(new Shaders::VertexPipelineShader(
			"SquareShader",
			"OpenGL-Examples/assets/shaders/Square.vert",
			"OpenGL-Examples\\assets\\shaders\\Square.frag"
		));
	}
};