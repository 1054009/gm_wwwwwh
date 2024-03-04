#include <GarrysMod/Lua/Interface.h>

#include "wwwwwh/globals.h"

GMOD_MODULE_OPEN()
{
	// No
	GarrysMod::Lua::ILuaInterface* LUA_INTERFACE = (GarrysMod::Lua::ILuaInterface*)LUA;
	if (LUA_INTERFACE->IsServer())
	{
		LUA->ThrowError("What are you doing");
		return 0;
	}

	// Yay
	if (!globals)
		globals = new wwwwwh();

	globals->setup(LUA_INTERFACE);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	if (!globals) return 0; // Uh oh

	globals->msgc({ { COLOR_RED, "Unloading" } });
	globals->msgn();

	globals->destroy();

	return 0;
}