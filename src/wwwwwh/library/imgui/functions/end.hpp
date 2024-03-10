#pragma once

#include "wwwwwh/library/imgui/functions/imguifunction.h"

#include "wwwwwh/includes/imgui/imgui.h"

class ImGuiFunctionEnd : public ImGuiFunction
{
public:
	void call()
	{
		ImGui::End();
	}
};