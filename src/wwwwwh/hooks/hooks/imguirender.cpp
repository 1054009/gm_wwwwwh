#include "wwwwwh/hooks/hooks/imguirender.h"

#include "wwwwwh/globals.h"
#include "wwwwwh/library/imgui/imgui.h"

#include <ranges>

void HookImGuiRender::setup()
{
	// Called from Lua thread
}

void HookImGuiRender::run()
{
	// Called from DirectX thread

	LibraryImGui* pLibraryImGui = (LibraryImGui*)globals->pLibrary->findlibrary("ImGui");
	if (pLibraryImGui)
	{
		for (ImGuiObject* pObject : pLibraryImGui->objects) // Start all the objects
			pObject->startrender();

		// Right here objects can be rendered inside of other objects

		for (ImGuiObject* pObject : std::ranges::views::reverse(pLibraryImGui->objects)) // End them all in reverse order to properly close them off
			pObject->endrender();

		pLibraryImGui->clearobjects();

		// Reset input
		pLibraryImGui->grabInput = false;
	}
}

void HookImGuiRender::destroy()
{

}