#include "wwwwwh/library/imgui/imgui.h"

#include "wwwwwh/globals.h"

#include "wwwwwh/library/imgui/functions/begin.hpp"
#include "wwwwwh/library/imgui/functions/end.hpp"

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

/*
*
*
*	Holy mother of god
* 
*/
LUA_FUNCTION(Begin)
{
	LibraryImGui* pLibraryImGui;
	if (grablibrary(pLibraryImGui))
	{
		std::string title = LUA->CheckString(1);

		ImGuiFunctionBegin* pBegin = new ImGuiFunctionBegin();
		if (!pBegin)
		{
			LUA->ThrowError("Failed to create function!");
			return 0;
		}

		pBegin->name = title;

		pLibraryImGui->addfunction(pBegin);
	}
	else
		LUA->ThrowError("Failed to find library!");

	return 0;
}

LUA_FUNCTION(End)
{
	LibraryImGui* pLibraryImGui;
	if (grablibrary(pLibraryImGui))
	{
		ImGuiFunctionEnd* pEnd = new ImGuiFunctionEnd();
		if (!pEnd)
		{
			LUA->ThrowError("Failed to create function!");
			return 0;
		}

		pLibraryImGui->addfunction(pEnd);
	}
	else
		LUA->ThrowError("Failed to find library!");

	return 0;
}

void LibraryImGui::addfunction(ImGuiFunction* pFunction)
{
	this->functions.push_back(pFunction);
}

void LibraryImGui::clearfunctions()
{
	for (ImGuiFunction* pFunction : this->functions)
		delete pFunction;

	this->functions.clear();
}

void LibraryImGui::runfunctions()
{
	for (ImGuiFunction* pFunction : this->functions)
		pFunction->call();
}

void LibraryImGui::setup()
{
	this->clearfunctions();
}

void LibraryImGui::push()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	pInterface->PushString("imgui");
	pInterface->CreateTable();
	{
		this->pushcfunction(SetGrabInput, "SetGrabInput");
		this->pushcfunction(GetGrabInput, "GetGrabInput");

		this->pushcfunction(Begin, "Begin");
		this->pushcfunction(End, "End");
	}
	pInterface->RawSet(-3);
}

void LibraryImGui::destroy()
{

}