#include "wwwwwh/globals.h"

#include "wwwwwh/library/library.h"
#include "wwwwwh/library/io/io.h"

/*

	Globals

*/
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

void LibraryController::addlibrary(BaseLibrary* library)
{
	library->setinterface(this->pInterface);
	library->setup();

	this->libraries.push_back(library);
}

void LibraryController::setup()
{
	// Initialize the libraries
	this->addlibrary(new LibraryIO());
}

void LibraryController::pushcfunction(GarrysMod::Lua::CFunc function, const char* szName)
{
	this->pInterface->PushString(szName);
	this->pInterface->PushCFunction(function);
	this->pInterface->RawSet(-3);
}

void LibraryController::setinterface(GarrysMod::Lua::ILuaInterface* pInterface)
{
	if (!pInterface)
	{
		this->pInterface = nullptr;
		this->isMenuState = false;

		return;
	}

	this->pInterface = pInterface;
	this->isMenuState = pInterface->IsMenu();
}

void LibraryController::pushtointerface()
{
	assert(this->pInterface);

	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;
	
	// Base global table
	// _G.wwwwwh
	pInterface->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		pInterface->CreateTable();
		{
			this->pushcfunction(Unload, "Unload");
			this->pushcfunction(Hide, "Hide");
			this->pushcfunction(Unhide, "Unhide");

			// Push all the libraries
			for (BaseLibrary* library : this->libraries)
				library->push();
		}
		this->libraryReference = pInterface->ReferenceCreate();
		
		pInterface->PushString("wwwwwh");
		pInterface->ReferencePush(this->libraryReference);
		pInterface->RawSet(-3);
	}
}

void LibraryController::popfrominterface()
{
	assert(this->pInterface);

	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	// Remove global
	pInterface->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		pInterface->PushString("wwwwwh");
		pInterface->PushNil();
		pInterface->RawSet(-3);
	}
	pInterface->Pop();

	globals->msgc({ { COLOR_WHITE, "Popped library" } });
	globals->msgn();

	// Empty table
	pInterface->ReferencePush(this->libraryReference);
	{
		this->looptable(pInterface->GetObject(-1), pInterface, [](GarrysMod::Lua::ILuaInterface* pInterface)->std::any
			{
				pInterface->Push(-2);
				pInterface->PushNil();
				pInterface->RawSet(-5);

				return NULL;
			});
	}
	pInterface->Pop();

	globals->msgc({ { COLOR_WHITE, "Emptied library" } });
	globals->msgn();
}

std::any LibraryController::looptable(GarrysMod::Lua::ILuaObject* pTable, GarrysMod::Lua::ILuaInterface* pInterface, std::function<std::any(GarrysMod::Lua::ILuaInterface*)> lambda)
{
	assert(pTable);
	assert(pInterface);

	std::any result = NULL;

	pInterface->PushLuaObject(pTable);
	pInterface->PushNil();

	while (pInterface->Next(-2))
	{
		std::any lambdaResult = lambda(pInterface);

		if (lambdaResult.has_value())
			result = lambdaResult;

		pInterface->Pop();
	}

	return result;
}