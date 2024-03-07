#include "wwwwwh/hooks/hooks.h"
#include "wwwwwh/hooks/hooks/reset.h"
#include "wwwwwh/hooks/hooks/endscene.h"
#include "wwwwwh/hooks/hooks/imguirender.h"
#include "wwwwwh/hooks/hooks/wndproc.h"
#include "wwwwwh/hooks/hooks/cursor.h"

#include "wwwwwh/globals.h"

#include "wwwwwh/includes/kiero/kiero.h"
#include "MinHook.h"

#include <format>

void Hooks::addhook(BaseHook* pHook, std::string name)
{
	pHook->name = name;
	pHook->setup();
	
	this->hooks.push_back(pHook);

	globals->msgc({ { COLOR_WHITE, std::format("Hooked {}", pHook->name) } });
	globals->msgn();
}

BaseHook* Hooks::findhook(std::string name)
{
	for (BaseHook* pHook : this->hooks)
		if (pHook->name == name)
			return pHook;

	return nullptr;
}

void Hooks::runhooks(std::string name)
{
	for (BaseHook* pHook : this->hooks)
	{
		if (!pHook)
			continue;

		if (pHook->name == name)
			pHook->run();
	}
}

void Hooks::setup()
{
	if (kiero::init(kiero::RenderType::D3D9) != kiero::Status::Success)
	{
		globals->msgc({ { COLOR_RED, "Failed to initialize kiero!" } });
		globals->msgn();
	}

	if (MH_Initialize() != MH_STATUS::MH_OK)
	{
		globals->msgc({ { COLOR_RED, "Failed to initialize MinHook!" } });
		globals->msgn();

		return;
	}

	this->addhook(new HookReset(), "Reset");
	this->addhook(new HookEndScene(), "EndScene");
	this->addhook(new HookImGuiRender(), "ImGuiRender");
	this->addhook(new HookWndProc(), "WndProc");
	this->addhook(new HookCursor(), "LockCursor");

	MH_EnableHook(MH_ALL_HOOKS);
}

void Hooks::destroy()
{
	for (BaseHook* pHook : this->hooks)
	{
		pHook->destroy();

		globals->msgc({ { COLOR_WHITE, std::format("Unhooked {}", pHook->name) } });
		globals->msgn();

		delete pHook;
	}

	kiero::shutdown();

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	delete this;
}