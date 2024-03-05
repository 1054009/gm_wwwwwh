#include "wwwwwh/globals.h"

#include <iomanip>
#include <sstream>

wwwwwh::wwwwwh()
{
	this->pPointers = new Pointers();

	this->pLibrary = new LibraryController();
}

void wwwwwh::setup(GarrysMod::Lua::ILuaInterface* pOriginInterface)
{
	this->pPointers->setup();

	// Push the globals to wherever we were included from
	this->pLibrary->setinterface(pOriginInterface);
	this->pLibrary->setup();
	this->pLibrary->pushtointerface();
}

void wwwwwh::destroy()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pPointers->getorigininterface();

	assert(pInterface);

	this->pPointers->destroy();
	this->pLibrary->popfrominterface();
}

std::string wwwwwh::tohex(void* pBlob)
{
	std::stringstream stream;
	stream << "0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << (uintptr_t)pBlob; // Holy moly

	return stream.str();
}

GarrysMod::Lua::ILuaInterface* wwwwwh::getmessageinterface()
{
	GarrysMod::Lua::ILuaInterface* pMessageInterface = this->pPointers->getinterface(lua_interface::client);
	if (pMessageInterface) return pMessageInterface;

	// Fall back to menu state
	return this->pPointers->getinterface(lua_interface::menu);
}

void wwwwwh::msgc(std::vector<std::pair<Color, std::string>> args)
{
	GarrysMod::Lua::ILuaInterface* pMessageInterface = this->getmessageinterface();
	if (!pMessageInterface) return;

	pMessageInterface->MsgColour(COLOR_GRAY, "[");
	pMessageInterface->MsgColour(COLOR_BLUE, "wwwwwh");
	pMessageInterface->MsgColour(COLOR_GRAY, "] ");

	for (std::pair<Color, std::string> arg : args)
		pMessageInterface->MsgColour(arg.first, arg.second.c_str());
}

void wwwwwh::msgn()
{
	GarrysMod::Lua::ILuaInterface* pMessageInterface = this->getmessageinterface();
	if (!pMessageInterface) return;

	pMessageInterface->Msg("\n");
}

void wwwwwh::print(std::string message)
{
	GarrysMod::Lua::ILuaInterface* pMessageInterface = this->getmessageinterface();
	if (!pMessageInterface) return;

	pMessageInterface->Msg(message.c_str());

	this->msgn();
}