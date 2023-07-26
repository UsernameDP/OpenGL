#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "GLCore/Core/Layer.hpp"


namespace GLCore {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer() : Layer("ImGuiLayer") {};
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onImguiUpdate(const TimeStep& ts) override {};

		void begin(); 
		void onUpdate(const TimeStep& ts) override = 0; //Customize the imgui panel 
		void end();
	};

}