#include "wwwwwh/library/library.h"

void BaseLibrary::pushcfunction(GarrysMod::Lua::CFunc function, const char* szName)
{
	this->pInterface->PushString(szName);
	this->pInterface->PushCFunction(function);
	this->pInterface->RawSet(-3);
}

void BaseLibrary::setinterface(GarrysMod::Lua::ILuaInterface* pInterface)
{
	if (!pInterface)
	{
		this->pInterface = nullptr;
		return;
	}

	this->pInterface = pInterface;
}