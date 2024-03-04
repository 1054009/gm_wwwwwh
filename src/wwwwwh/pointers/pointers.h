#pragma once

#include <GarrysMod/Lua/LuaShared.h>
#include <GarrysMod/Lua/LuaInterface.h>

class Pointers
{
public:
	void setup();

	GarrysMod::Lua::ILuaShared* pLuaShared = nullptr;

	GarrysMod::Lua::ILuaBase* pLuaClient = nullptr;
	GarrysMod::Lua::ILuaBase* pLuaMenu = nullptr;

	GarrysMod::Lua::ILuaInterface* pLuaInterfaceClient = nullptr;
	GarrysMod::Lua::ILuaInterface* pLuaInterfaceMenu = nullptr;

	GarrysMod::Lua::ILuaInterface* getinterface(unsigned char interfaceType); // Stupid cyclic reference garbage trash
	GarrysMod::Lua::ILuaInterface* getorigininterface();
};