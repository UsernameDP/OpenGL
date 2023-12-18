#pragma once

#include "GLCore/Core/Core.hpp"


class ExampleLayer : public GLCore::Layer {
	
public:
	ExampleLayer();
	virtual ~ExampleLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(const GLCore::TimeStep& ts) override;
	virtual void onImguiUpdate(const GLCore::TimeStep& ts) override;
private:

};