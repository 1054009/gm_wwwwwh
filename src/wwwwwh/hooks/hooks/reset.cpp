#include "wwwwwh/hooks/hooks/reset.h"

#include <d3d9.h>
#include <d3d9types.h>
#include "wwwwwh/includes/imgui/backends/imgui_impl_dx9.h"
#include "wwwwwh/includes/kiero/kiero.h"

typedef long(__stdcall* Reset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
static Reset oReset = NULL;

long __stdcall hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	long result = oReset(pDevice, pPresentationParameters);

	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}

void HookReset::setup()
{
	kiero::bind(16, (void**)&oReset, hkReset);
}

void HookReset::destroy()
{
	kiero::unbind(16);
}