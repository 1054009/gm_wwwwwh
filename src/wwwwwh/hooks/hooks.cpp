#include "wwwwwh/hooks/hooks.h"

BaseHook::BaseHook(std::string name)
{
	this->name = name;
}

void Hooks::addhook(BaseHook* pHook)
{
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

void Hooks::setup()
{

}

void Hooks::destroy()
{

}