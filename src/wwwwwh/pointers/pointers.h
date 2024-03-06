#pragma once

#include <GarrysMod/Lua/LuaShared.h>
#include <GarrysMod/Lua/LuaInterface.h>
#include <vgui/ISurfaceV30.h>

class Pointers
{
public:
	void setup();
	void destroy();

	GarrysMod::Lua::ILuaShared* pLuaShared = nullptr;

	GarrysMod::Lua::ILuaInterface* pLuaInterfaceClient = nullptr;
	GarrysMod::Lua::ILuaInterface* pLuaInterfaceServer = nullptr;
	GarrysMod::Lua::ILuaInterface* pLuaInterfaceMenu = nullptr;

	ISurfaceV30::ISurface* pSurface = nullptr;

	void msgaddress(std::string name, void* pObject);

	GarrysMod::Lua::ILuaInterface* getinterface(unsigned char interfaceType); // Stupid cyclic reference garbage trash
	GarrysMod::Lua::ILuaInterface* getorigininterface();

	int getinterfacetype(GarrysMod::Lua::ILuaInterface* pInterface);
	std::string getinterfacename(unsigned char interfaceType);
	std::string getinterfacename(GarrysMod::Lua::ILuaInterface* pInterface);
};