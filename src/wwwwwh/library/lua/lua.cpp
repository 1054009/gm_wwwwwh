#include "wwwwwh/library/lua/lua.h"

#include "wwwwwh/globals.h"

#include <format>
#include <string>

LUA_FUNCTION(RunInterfaceString)
{
	int typeIndex = 1;
	int codeIndex = 2;
	int identifierIndex = 3;
	int handleIndex = 4;

	GarrysMod::Lua::ILuaInterface* LUA_INTERFACE = (GarrysMod::Lua::ILuaInterface*)LUA;
	int target = globals->pPointers->getinterfacetype(LUA_INTERFACE); // Default to current state

	// If they've specified a desired state to run on, try to find it
	if (LUA->IsType(1, GarrysMod::Lua::Type::Number))
	{
		int test = LUA->GetNumber(1);

		if (test == lua_interface::client || test == lua_interface::menu || test == lua_interface::server)
			target = test;
	}
	else
	{
		// Assume that the arguments are in normal RunString order
		codeIndex--;
		identifierIndex--;
		handleIndex--;
	}

	GarrysMod::Lua::ILuaInterface* TARGET_INTERFACE = globals->pPointers->getinterface(target);
	if (!TARGET_INTERFACE)
	{
		LUA->ThrowError(std::format("{} interface not found!", globals->pPointers->getinterfacename(target)).c_str());
		return 0;
	}

	// Get the rest of the argments
	std::string code = LUA->CheckString(codeIndex);

	std::string identifier = "RunString";
	if (LUA->IsType(identifierIndex, GarrysMod::Lua::Type::String))
		identifier = LUA->GetString(identifierIndex);

	bool handleError = true;
	if (LUA->IsType(handleIndex, GarrysMod::Lua::Type::Bool))
		handleError = LUA->GetBool(handleIndex);

	// Run the string!
	TARGET_INTERFACE->RunString(identifier.c_str(), identifier.c_str(), code.c_str(), true, handleError);

	return 0;
}

void LibraryLua::setup()
{

}

void LibraryLua::push()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	pInterface->PushString("lua");
	pInterface->CreateTable();
	{
		this->pushnumber(lua_interface::client, "LUA_INTERFACE_CLIENT");
		this->pushnumber(lua_interface::menu, "LUA_INTERFACE_MENU");
		this->pushnumber(lua_interface::server, "LUA_INTERFACE_SERVER");

		this->pushcfunction(RunInterfaceString, "RunInterfaceString");
	}
	pInterface->RawSet(-3);
}

void LibraryLua::destroy()
{

}