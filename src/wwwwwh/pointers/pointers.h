#pragma once

#include <d3d9.h>
#include <GarrysMod/Lua/LuaShared.h>
#include <GarrysMod/Lua/LuaInterface.h>

class Pointers
{
public:
	void setup();

	GarrysMod::Lua::ILuaShared* pLuaShared = nullptr;

	GarrysMod::Lua::ILuaInterface* pLuaInterfaceClient = nullptr;
	GarrysMod::Lua::ILuaInterface* pLuaInterfaceServer = nullptr;
	GarrysMod::Lua::ILuaInterface* pLuaInterfaceMenu = nullptr;

	IDirect3DDevice9* pD3DDevice = nullptr;

	void msgaddress(std::string name, void* pObject);

	GarrysMod::Lua::ILuaInterface* getinterface(unsigned char interfaceType); // Stupid cyclic reference garbage trash
	GarrysMod::Lua::ILuaInterface* getorigininterface();

	int getinterfacetype(GarrysMod::Lua::ILuaInterface* pInterface);
	std::string getinterfacename(unsigned char interfaceType);
	std::string getinterfacename(GarrysMod::Lua::ILuaInterface* pInterface);
};