#pragma once

#include <GarrysMod/Lua/LuaInterface.h>
#include <GarrysMod/Lua/Interface.h>

#include <any>
#include <functional>
#include <string>
#include <vector>

class BaseLibrary
{
public:
	std::string name;
	GarrysMod::Lua::ILuaInterface* pInterface;

	void pushcfunction(GarrysMod::Lua::CFunc function, const char* szName);
	void pushnumber(double number, const char* szName);
	void setinterface(GarrysMod::Lua::ILuaInterface* pInterface);

	virtual void setup() = 0;
	virtual void push() = 0;
	virtual void destroy() = 0;
};

class LibraryController
{
public:
	inline static int libraryReference;
	bool isMenuState;

	GarrysMod::Lua::ILuaInterface* pInterface;

	std::vector<BaseLibrary*> libraries;

	void addlibrary(BaseLibrary* library, std::string name);
	BaseLibrary* findlibrary(std::string name);
	void setup();

	void pushcfunction(GarrysMod::Lua::CFunc function, const char* szName);
	void setinterface(GarrysMod::Lua::ILuaInterface* pInterface);
	void pushtointerface();
	void popfrominterface();

	std::any looptable(GarrysMod::Lua::ILuaObject* pTable, GarrysMod::Lua::ILuaInterface* pInterface, std::function<std::any(GarrysMod::Lua::ILuaInterface*)> lambda);
};