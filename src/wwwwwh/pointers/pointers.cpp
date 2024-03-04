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
	this->pLuaInterfaceClient = pLuaShared->GetLuaInterface(lua_interface::client);
	this->pLuaInterfaceServer = pLuaShared->GetLuaInterface(lua_interface::server);
	this->pLuaInterfaceMenu = pLuaShared->GetLuaInterface(lua_interface::menu);

	// Fun facts
	globals->msgc({ { COLOR_WHITE, "Lua Shared: " }, { COLOR_BLUE, globals->tohex(pLuaShared) } });
	globals->msgn();

	globals->msgc({ { COLOR_WHITE, "Client Lua State: " }, { this->pLuaInterfaceClient ? COLOR_BLUE : COLOR_RED, globals->tohex(this->pLuaInterfaceClient) } });
	globals->msgn();

	globals->msgc({ { COLOR_WHITE, "Server Lua State: " }, { this->pLuaInterfaceServer ? COLOR_BLUE : COLOR_RED, globals->tohex(this->pLuaInterfaceServer) } });
	globals->msgn();

	globals->msgc({ { COLOR_WHITE, "Menu Lua State: " }, { this->pLuaInterfaceMenu ? COLOR_BLUE : COLOR_RED, globals->tohex(this->pLuaInterfaceMenu) } });
	globals->msgn();
}

GarrysMod::Lua::ILuaInterface* Pointers::getinterface(unsigned char interfaceType)
{
	switch (interfaceType)
	{
		case lua_interface::client:
			return this->pLuaInterfaceClient;
	
		case lua_interface::server:
			return this->pLuaInterfaceServer;

		case lua_interface::menu:
			return this->pLuaInterfaceMenu;

		default:
			return nullptr;
	}
}

GarrysMod::Lua::ILuaInterface* Pointers::getorigininterface()
{
	return this->getinterface(globals->pLibrary->isMenuState ? lua_interface::menu : lua_interface::client);
}

int Pointers::getinterfacetype(GarrysMod::Lua::ILuaInterface* pInterface)
{
	if (!pInterface) return -1;

	if (pInterface->IsClient())
		return lua_interface::client;

	if (pInterface->IsServer())
		return lua_interface::server;

	if (pInterface->IsMenu())
		return lua_interface::menu;

	return -1; // Invalid
}

std::string Pointers::getinterfacename(unsigned char interfaceType)
{
	switch (interfaceType)
	{
		case lua_interface::client:
			return "Client";

		case lua_interface::server:
			return "Server";

		case lua_interface::menu:
			return "Menu";

		default:
			return "Invalid";
	}
}

std::string Pointers::getinterfacename(GarrysMod::Lua::ILuaInterface* pInterface)
{
	return this->getinterfacename(this->getinterfacetype(pInterface));
}