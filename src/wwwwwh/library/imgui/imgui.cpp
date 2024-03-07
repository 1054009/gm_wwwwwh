#include "wwwwwh/library/imgui/imgui.h"

#include "wwwwwh/globals.h"

#include "wwwwwh/library/imgui/objects/window.h"

bool grablibrary(LibraryImGui*& target)
{
	LibraryImGui* pLibraryImGui = (LibraryImGui*)globals->pLibrary->findlibrary("ImGui");
	if (pLibraryImGui)
	{
		target = pLibraryImGui;
		return true;
	}

	return false;
}

LUA_FUNCTION(SetGrabInput)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::Bool);
	bool active = LUA->GetBool(1);
	
	LibraryImGui* pLibraryImGui;
	if (grablibrary(pLibraryImGui))
		pLibraryImGui->grabInput = active;

	return 0;
}

LUA_FUNCTION(GetGrabInput)
{
	LibraryImGui* pLibraryImGui;
	if (grablibrary(pLibraryImGui))
	{
		LUA->PushBool(pLibraryImGui->grabInput);
		return 1;
	}

	LUA->PushBool(false);
	return 1;
}

LUA_FUNCTION(CreateWindow)
{
	const char* title = LUA->CheckString(1);

	LibraryImGui* pLibraryImGui;
	if (grablibrary(pLibraryImGui))
	{
		ImGuiObject_Window* pWindow = new ImGuiObject_Window(title);

		pLibraryImGui->addobject(pWindow);
	}

	return 0;
}

void LibraryImGui::addobject(ImGuiObject* pObject)
{
	this->objects.push_back(pObject);
}

void LibraryImGui::clearobjects()
{
	for (ImGuiObject* pObject : this->objects)
		delete pObject;

	this->objects.clear();
}

void LibraryImGui::setup()
{
	this->clearobjects();
}

void LibraryImGui::push()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	pInterface->PushString("imgui");
	pInterface->CreateTable();
	{
		this->pushcfunction(SetGrabInput, "SetGrabInput");
		this->pushcfunction(GetGrabInput, "GetGrabInput");

		this->pushcfunction(CreateWindow, "CreateWindow");
	}
	pInterface->RawSet(-3);
}

void LibraryImGui::destroy()
{

}