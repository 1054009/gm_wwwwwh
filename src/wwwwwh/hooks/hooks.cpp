#include "wwwwwh/hooks/hooks.h"
#include "wwwwwh/hooks/hooks/reset.h"
#include "wwwwwh/hooks/hooks/endscene.h"

#include "wwwwwh/globals.h"

#include "wwwwwh/includes/kiero/kiero.h"

BaseHook* Hooks::addhook(BaseHook* pHook)
{
	pHook->setup();
	
	this->hooks.push_back(pHook);

	return pHook;
}

BaseHook* Hooks::findhook(std::string name)
{
	for (BaseHook* pHook : this->hooks)
		if (pHook->name == name)
			return pHook;

	return nullptr;
}

void Hooks::setup()
{
	if (kiero::init(kiero::RenderType::D3D9) != kiero::Status::Success)
	{
		globals->msgc({ { COLOR_RED, "Failed to initialize kiero!" } });
		globals->msgn();
	}

	this->addhook(new HookReset())->name = "Reset";
	this->addhook(new HookEndScene())->name = "EndScene";
}

void Hooks::destroy()
{
	kiero::shutdown();
}