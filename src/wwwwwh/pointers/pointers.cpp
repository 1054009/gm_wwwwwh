#include <GarrysMod/FactoryLoader.hpp>
#include <GarrysMod/Lua/LuaInterface.h>

#include "wwwwwh/globals.h"

#define LUA_SHARED_INTERFACE_VERSION "LUASHARED003"

void Pointers::setup()
{
	// Get Lua Shared
	SourceSDK::FactoryLoader factory_LuaShared("lua_shared");
	GarrysMod::Lua::ILuaShared* pLuaShared = factory_LuaShared.GetInterface<GarrysMod::Lua::ILuaShared>(LUA_SHARED_INTERFACE_VERSION);

	assert(pLuaShared);

	this->pLuaShared = pLuaShared;

	// Get the interfaces
	this->pLuaClient = pLuaShared->GetLuaInterface(0); // 0 is client. 1 is server. 2 is menu
	this->pLuaInterfaceClient = (GarrysMod::Lua::ILuaInterface*)this->pLuaClient;

	this->pLuaMenu = pLuaShared->GetLuaInterface(2);
	this->pLuaInterfaceMenu = (GarrysMod::Lua::ILuaInterface*)this->pLuaMenu;

	// Let them know
	globals->msgc({ { COLOR_WHITE, "Lua Shared: " }, { COLOR_BLUE, globals->tohex(pLuaShared) } });
	globals->msgn();

	globals->msgc({ { COLOR_WHITE, "Client Lua State: " }, { COLOR_BLUE, globals->tohex(this->pLuaClient) } });
	globals->msgn();

	globals->msgc({ { COLOR_WHITE, "Menu Lua State: " }, { COLOR_BLUE, globals->tohex(this->pLuaMenu) } });
	globals->msgn();
}

GarrysMod::Lua::ILuaInterface* Pointers::getinterface(unsigned char interfaceType)
{
	switch (interfaceType)
	{
		default:
		case lua_interface::client:
			return this->pLuaInterfaceClient;
	
		case lua_interface::server:
			return nullptr;

		case lua_interface::menu:
			return this->pLuaInterfaceMenu;
	}
}

GarrysMod::Lua::ILuaInterface* Pointers::getorigininterface()
{
	return this->getinterface(globals->pLibrary->isMenuState ? lua_interface::menu : lua_interface::client);
}