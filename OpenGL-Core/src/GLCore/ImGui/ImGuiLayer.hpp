#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "GLCore/Core/Layer.hpp"
#include "GLCore/Core/Application.hpp"


namespace GLCore {
	class ImGuiLayer : public Layer {
		ImGuiLayer() : Layer("ImGuiLayer") {};

		void onAttach() override;
		void onDetach() override;

		void begin(); 
		virtual void onUpdate(const TimeStep& ts) override; //Customize the imgui panel 
		void end();
	};

}