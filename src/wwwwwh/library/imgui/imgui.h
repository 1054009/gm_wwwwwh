#pragma once

#include "wwwwwh/library/library.h"

#include "wwwwwh/library/imgui/functions/imguifunction.h"

#include <vector>

class LibraryImGui : public BaseLibrary
{
public:
	bool grabInput = false;
	bool cursorVisible = false;

	std::vector<ImGuiFunction*> functions;

	void addfunction(ImGuiFunction* pFunction);
	void clearfunctions();
	void runfunctions();

	void setup();
	void push();
	void destroy();
};