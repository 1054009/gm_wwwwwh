#include "wwwwwh/library/system/system.h"

#include <Windows.h>

#undef MessageBox // Thanks!

LUA_FUNCTION(MessageBox)
{
	const char* title = LUA->CheckString(1);
	const char* body = LUA->CheckString(2);
	
	long buttons = MB_OK;
	if (LUA->IsType(3, GarrysMod::Lua::Type::Number))
		buttons = LUA->GetNumber(3);

	long icon = MB_ICONINFORMATION;
	if (LUA->IsType(4, GarrysMod::Lua::Type::Number))
		icon = LUA->GetNumber(4);

	MessageBoxA(NULL, body, title, buttons | icon | MB_TOPMOST);

	return 0;
}

void LibrarySystem::setup()
{

}

void LibrarySystem::push()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	pInterface->PushString("system");
	pInterface->CreateTable();
	{
		this->pushnumber(MB_OK, "MB_OK");
		this->pushnumber(MB_OKCANCEL, "MB_OKCANCEL");
		this->pushnumber(MB_ABORTRETRYIGNORE, "MB_ABORTRETRYIGNORE");
		this->pushnumber(MB_YESNOCANCEL, "MB_YESNOCANCEL");
		this->pushnumber(MB_YESNO, "MB_YESNO");
		this->pushnumber(MB_RETRYCANCEL, "MB_RETRYCANCEL");
		this->pushnumber(MB_CANCELTRYCONTINUE, "MB_CANCELTRYCONTINUE");

		this->pushnumber(MB_ICONHAND, "MB_ICONHAND");
		this->pushnumber(MB_ICONQUESTION, "MB_ICONQUESTION");
		this->pushnumber(MB_ICONEXCLAMATION, "MB_ICONEXCLAMATION");
		this->pushnumber(MB_ICONASTERISK, "MB_ICONASTERISK");
		this->pushnumber(MB_USERICON, "MB_USERICON");
		this->pushnumber(MB_ICONWARNING, "MB_ICONWARNING");
		this->pushnumber(MB_ICONERROR, "MB_ICONERROR");
		this->pushnumber(MB_ICONINFORMATION, "MB_ICONINFORMATION");

		this->pushcfunction(MessageBox, "MessageBox");
	}
	pInterface->RawSet(-3);
}

void LibrarySystem::destroy()
{

}