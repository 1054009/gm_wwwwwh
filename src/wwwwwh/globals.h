#pragma once

#include "wwwwwh/pointers/pointers.h"
#include "wwwwwh/library/library.h"
#include "wwwwwh/hooks/hooks.h"

#include <GarrysMod/Lua/LuaInterface.h>

#define assert(condition) if (!##condition) throw -1;

#ifdef DEBUG
#define MODULE_NAME "wwwwwh_debug"
#else
#define MODULE_NAME "wwwwwh"
#endif

#define COLOR_WHITE Color(255, 255, 255, 255)
#define COLOR_GRAY Color(150, 150, 150, 255)
#define COLOR_BLUE Color(65, 135, 245, 255)
#define COLOR_RED Color(255, 0, 0, 255)

enum lua_interface
{
	client = 0,
	server,
	menu
};

class wwwwwh
{
public:
	wwwwwh();

	void setup(GarrysMod::Lua::ILuaInterface* pOriginInterface);
	void destroy();

	Pointers* pPointers;
	LibraryController* pLibrary;
	Hooks* pHooks;

	std::string tohex(void* pBlob);

	GarrysMod::Lua::ILuaInterface* getmessageinterface();
	void msgc(std::vector<std::pair<Color, std::string>> args);
	void msgn();
	void print(std::string message);
};

inline wwwwwh* globals;