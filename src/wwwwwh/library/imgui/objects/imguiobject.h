#pragma once

#include "wwwwwh/includes/imgui/imgui.h"

class ImGuiObject
{
public:
	virtual void startrender() = 0;
	virtual void endrender() = 0;
};