#include "wwwwwh/globals.h"

#include "wwwwwh/library/library.h"
#include "wwwwwh/library/io/io.h"
#include "wwwwwh/library/module/module.h"

/*

	Globals

*/
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
	this->addlibrary(new LibraryModule());
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