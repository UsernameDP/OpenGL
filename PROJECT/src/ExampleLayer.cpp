#include "ExampleLayer.hpp"
#include <imgui.h>
#include <iostream>

ExampleLayer::ExampleLayer() : GLCore::Layer("ExampleLayer") {

}
ExampleLayer::~ExampleLayer() {

}

void ExampleLayer::onAttach() {

}

void ExampleLayer::onDetach() {

}

void ExampleLayer::onUpdate(const GLCore::TimeStep& ts) {

}

void ExampleLayer::onImguiUpdate(const GLCore::TimeStep& ts) {
	ImGui::ShowDemoWindow();

	if (GLCore::Application::get().getKeyPressed(GLFW_KEY_F)) {
		std::cout << "Key F is being pressed" << std::endl;
	}
}