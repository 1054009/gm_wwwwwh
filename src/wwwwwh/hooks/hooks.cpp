#include "wwwwwh/hooks/hooks.h"
#include "wwwwwh/hooks/hooks/reset.h"
#include "wwwwwh/hooks/hooks/endscene.h"
#include "wwwwwh/hooks/hooks/imguirender.h"
#include "wwwwwh/hooks/hooks/wndproc.h"

#include "wwwwwh/globals.h"

#include "wwwwwh/includes/kiero/kiero.h"

void Hooks::addhook(BaseHook* pHook, std::string name)
{
	pHook->name = name;
	pHook->setup();
	
	this->hooks.push_back(pHook);
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
		if (pHook->name == name)
			pHook->run();
}

void Hooks::setup()
{
	if (kiero::init(kiero::RenderType::D3D9) != kiero::Status::Success)
	{
		globals->msgc({ { COLOR_RED, "Failed to initialize kiero!" } });
		globals->msgn();
	}

	this->addhook(new HookReset(), "Reset");
	this->addhook(new HookEndScene(), "EndScene");
	this->addhook(new HookImGuiRender(), "ImGuiRender");
	this->addhook(new HookWndProc(), "WndProc");
}

void Hooks::destroy()
{
	kiero::shutdown();
}