#include "wwwwwh/hooks/hooks/wndproc.h"

#include "wwwwwh/includes/imgui/imgui.h"
#include "wwwwwh/globals.h"
#include "wwwwwh/library/imgui/imgui.h"

#include <Windows.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

static WNDPROC oWndProc = NULL;

LRESULT CALLBACK hkWndProc(HWND hWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LibraryImGui* pLibraryImGui = (LibraryImGui*)globals->pLibrary->findlibrary("ImGui");
	if (pLibraryImGui && pLibraryImGui->grabInput)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWindow, uMsg, wParam, lParam))
			return 1L;
	}

	return CallWindowProc(oWndProc, hWindow, uMsg, wParam, lParam);
}

void HookWndProc::setup()
{
	oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc)));
}

void HookWndProc::run()
{

}

void HookWndProc::destroy()
{
	SetWindowLongPtr(GetActiveWindow(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
}