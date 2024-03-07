#pragma once

#include "wwwwwh/library/library.h"

#include "wwwwwh/library/imgui/objects/imguiobject.h"

#include <vector>

class LibraryImGui : public BaseLibrary
{
public:
	bool grabInput = false;
	bool cursorVisible = false;
	std::vector<ImGuiObject*> objects;

	void addobject(ImGuiObject* pObject);
	void clearobjects();

	void setup();
	void push();
	void destroy();
};