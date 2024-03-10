#pragma once

#include "wwwwwh/library/imgui/functions/imguifunction.h"

#include "wwwwwh/includes/imgui/imgui.h"

#include <string>

class ImGuiFunctionBegin : public ImGuiFunction
{
public:
	std::string name;

	void call()
	{
		ImGui::Begin(this->name.c_str());
	}
};