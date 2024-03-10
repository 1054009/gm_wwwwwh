#include "wwwwwh/hooks/hooks/imguirender.h"

#include "wwwwwh/globals.h"
#include "wwwwwh/library/imgui/imgui.h"

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
		pLibraryImGui->runfunctions();
		pLibraryImGui->clearfunctions();

		// Reset input
		pLibraryImGui->grabInput = false;
	}
}

void HookImGuiRender::destroy()
{

}