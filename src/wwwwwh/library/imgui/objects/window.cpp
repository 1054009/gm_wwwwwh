#include "wwwwwh/library/imgui/objects/window.h"

ImGuiObject_Window::ImGuiObject_Window(std::string title)
{
	this->title = title;
}

void ImGuiObject_Window::startrender()
{
	ImGui::SetNextWindowFocus();
	ImGui::Begin(this->title.c_str());
}

void ImGuiObject_Window::endrender()
{
	ImGui::End();
}