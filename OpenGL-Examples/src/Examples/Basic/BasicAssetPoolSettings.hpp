#pragma once
#include "GLCore/Extension/Util/AssetPoolSettings.hpp"
#include "GLCore/Extension/Util/AssetPool.hpp"

#include "GLCore/Extension/Shaders/VertexPipelineShader.hpp"

using namespace GLCore;

class BasicAssetPoolSettings : public Util::AssetPoolSettings {
	
	void run() override {
		Util::AssetPool::setShader(new Shaders::VertexPipelineShader(
			"SquareShader",
			"OpenGL-Examples/assets/shaders/Square.vert",
			"OpenGL-Examples\\assets\\shaders\\Square.frag"
		));
	}
};