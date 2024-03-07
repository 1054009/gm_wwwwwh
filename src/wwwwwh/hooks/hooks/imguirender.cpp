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
		std::vector<ImGuiObject*> objects = pLibraryImGui->objects;

		// Start all the objects
		for (ImGuiObject* pObject : objects)
			pObject->startrender();

		// Objects can now be rendered inside of other objects

		// End them all in reverse order to properly close them off
		for (auto pIterator = objects.rbegin(); pIterator != objects.rend(); ++pIterator)
		{
			ImGuiObject* pObject = (ImGuiObject*)(*pIterator);

			pObject->endrender();
		}

		pLibraryImGui->clearobjects();

		// Reset input
		pLibraryImGui->grabInput = false;
	}
}

void HookImGuiRender::destroy()
{

}