#include "wwwwwh/library/module/module.h"

#include "wwwwwh/globals.h"

#undef GetObject // Dumb

LUA_FUNCTION(Unload)
{
	// Remove from global table
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("_MODULES");
		LUA->RawGet(-2);
		if (LUA->IsType(-1, GarrysMod::Lua::Type::Table))
		{
			globals->msgc({ { COLOR_WHITE, "Removing from _MODULES" } });
			globals->msgn();

			LUA->PushString(MODULE_NAME);
			LUA->PushNil();
			LUA->RawSet(-3);
		}
		LUA->Pop();
	}
	LUA->Pop();

	// Remove from registry
	int __gc = NULL;
	int __module = NULL;

	// Get __gc
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_REG);
	{
		LUA->PushString("_LOADLIB");
		LUA->RawGet(-2);
		if (LUA->IsType(-1, GarrysMod::Lua::Type::Table))
		{
			LUA->PushString("__gc");
			LUA->RawGet(-2);
			if (LUA->IsType(-1, GarrysMod::Lua::Type::Function))
			{
				__gc = LUA->ReferenceCreate();
			}
			else
			{
				globals->msgc({ { COLOR_RED, "Failed to get __gc" } });
				globals->msgn();

				LUA->Pop();
			}
		}
		else
		{
			globals->msgc({ { COLOR_RED, "Failed to get _LOADLIB" } });
			globals->msgn();
		}
		LUA->Pop();
	}

	// Find the module userdata
	GarrysMod::Lua::ILuaInterface* LUA_INTERFACE = (GarrysMod::Lua::ILuaInterface*)LUA;
	std::any moduleResult = globals->pLibrary->looptable(LUA_INTERFACE->GetObject(-1), LUA_INTERFACE, [](GarrysMod::Lua::ILuaInterface* pInterface)->std::any
		{
			int __module = NULL;

			if (pInterface->IsType(-2, GarrysMod::Lua::Type::String))
			{
				if (std::string(pInterface->GetString(-2)).find(MODULE_NAME) != std::string::npos)
				{
					pInterface->Push(-1);
					__module = pInterface->ReferenceCreate();
				}
			}

			// Silly
			if (__module)
				return __module;
			else
			{
				std::any hi;
				return hi;
			}
		});

	if (moduleResult.has_value())
		__module = std::any_cast<int>(moduleResult);

	LUA->Pop(); // Get rid of _R

	// Check that we got the goods!
	LUA->ReferencePush(__gc);
	{
		if (!LUA->IsType(-1, GarrysMod::Lua::Type::Function))
		{
			globals->msgc({ { COLOR_RED, "Failed to get __gc" } });
			globals->msgn();

			LUA->Pop();

			LUA->PushBool(false);
			return 1;
		}
	}
	LUA->Pop();

	LUA->ReferencePush(__module);
	{
		if (!LUA->IsType(-1, GarrysMod::Lua::Type::UserData))
		{
			globals->msgc({ { COLOR_RED, "Failed to get __module" } });
			globals->msgn();

			LUA->Pop();

			LUA->PushBool(false);
			return 1;
		}
	}
	LUA->Pop();

	// Let a timer do the work. If we unload the module from within the module, the game crashes
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("__GC");
		LUA->ReferencePush(__gc);
		LUA->RawSet(-3);

		LUA->PushString("__WWWWWH");
		LUA->ReferencePush(__module);
		LUA->RawSet(-3);
	}
	LUA->Pop();

	LUA_INTERFACE->RunString("[C]", "[C]", "timer.Simple(0, function() pcall(__GC, __WWWWWH); rawset(_G, \"__GC\", nil); rawset(_G, \"__WWWWWH\", nil); end)", true, true);

	// Yay!
	LUA->ReferenceFree(__gc);
	LUA->ReferenceFree(__module);

	LUA->PushBool(true);
	return 1;
}

LUA_FUNCTION(Hide)
{
	// Hide global references
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("_MODULES");
		LUA->RawGet(-2);
		if (LUA->IsType(-1, GarrysMod::Lua::Type::Table))
		{
			globals->msgc({ { COLOR_WHITE, "Hiding from _MODULES" } });
			globals->msgn();

			LUA->PushString(MODULE_NAME);
			LUA->PushNil();
			LUA->RawSet(-3);
		}
		LUA->Pop();
	}
	LUA->Pop();

	// Delete the global table
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("wwwwwh");
		LUA->PushNil();
		LUA->RawSet(-3);
	}
	LUA->Pop();

	// Return the reference to the table
	LUA->ReferencePush(globals->pLibrary->libraryReference);
	return 1;
}

LUA_FUNCTION(Unhide)
{
	// Re-add the global references
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("_MODULES");
		LUA->RawGet(-2);
		if (LUA->IsType(-1, GarrysMod::Lua::Type::Table))
		{
			globals->msgc({ { COLOR_WHITE, "Un-hiding from _MODULES" } });
			globals->msgn();

			LUA->PushString(MODULE_NAME);
			LUA->PushBool(true);
			LUA->RawSet(-3);
		}
		LUA->Pop();
	}
	LUA->Pop();

	// Restore the global table
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		LUA->PushString("wwwwwh");
		LUA->ReferencePush(globals->pLibrary->libraryReference);
		LUA->RawSet(-3);
	}
	LUA->Pop();

	return 0;
}

void LibraryModule::setup()
{

}

void LibraryModule::push()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	pInterface->PushString("module");
	pInterface->CreateTable();
	{
		this->pushcfunction(Unload, "Unload");
		this->pushcfunction(Hide, "Hide");
		this->pushcfunction(Unhide, "Unhide");
	}
	pInterface->RawSet(-3);
}

void LibraryModule::destroy()
{

}