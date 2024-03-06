#pragma once

#include "wwwwwh/library/imgui/objects/imguiobject.h"

#include <string>

class ImGuiObject_Window : public ImGuiObject
{
public:
	std::string title;

	ImGuiObject_Window(std::string title);

	void startrender();
	void endrender();
};