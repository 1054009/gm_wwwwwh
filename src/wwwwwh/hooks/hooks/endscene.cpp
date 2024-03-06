#include "wwwwwh/hooks/hooks/endscene.h"

#include "wwwwwh/globals.h"

#include <d3d9.h>
#include <d3d9types.h>
#include "wwwwwh/includes/imgui/backends/imgui_impl_dx9.h"
#include "wwwwwh/includes/imgui/backends/imgui_impl_win32.h"
#include "wwwwwh/includes/kiero/kiero.h"

typedef long(__stdcall* EndScene)(IDirect3DDevice9*);
static EndScene oEndScene = NULL;

long __stdcall hkEndScene(IDirect3DDevice9* pDevice)
{
	static bool initialized = false;

	if (!initialized)
	{
		globals->msgc({ { COLOR_WHITE, "Initializing ImGui" } });
		globals->msgn();

		globals->pPointers->msgaddress("DirectX Device", pDevice);

		D3DDEVICE_CREATION_PARAMETERS creationParameters;
		pDevice->GetCreationParameters(&creationParameters);

		ImGui::CreateContext();

		ImGui_ImplWin32_Init(creationParameters.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);

		initialized = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	globals->pHooks->runhooks("ImGuiRender");

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}

void HookEndScene::setup()
{
	kiero::bind(42, (void**)&oEndScene, hkEndScene);
}

void HookEndScene::run()
{

}

void HookEndScene::destroy()
{
	kiero::unbind(42);
}