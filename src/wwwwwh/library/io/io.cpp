#include "wwwwwh/library/io/io.h"

#include "wwwwwh/library/io/iofile.h"
#include "wwwwwh/library/io/iodirectory.h"

#include <filesystem>
#include <format>
#include <tuple>
#include <vector>

/*

	IOFile

*/
static int IOFile_TypeID;

LUA_FUNCTION(IOFile_tostring)
{
	LUA->CheckType(1, IOFile_TypeID);

	IOFile* pFile = LUA->GetUserType<IOFile>(1, IOFile_TypeID);
	if (!pFile)
		LUA->PushString("[NULL IOFile]");
	else
		LUA->PushString(std::format("IOFile ['{}']", pFile->m_strPath).c_str());

	return 1;
}

LUA_FUNCTION(IOFile_IsValid)
{
	LUA->CheckType(1, IOFile_TypeID);

	IOFile* pFile = LUA->GetUserType<IOFile>(1, IOFile_TypeID);
	if (!pFile)
	{
		LUA->PushBool(false);
		return 1;
	}

	bool exists = std::filesystem::exists(pFile->m_strPath);
	bool isFile = exists ? std::filesystem::is_regular_file(pFile->m_strPath) : false;

	LUA->PushBool(exists && isFile);
	return 1;
}

LUA_FUNCTION(IOFile_GetPath)
{
	LUA->CheckType(1, IOFile_TypeID);

	IOFile* pFile = LUA->GetUserType<IOFile>(1, IOFile_TypeID);
	if (!pFile)
	{
		LUA->ThrowError("Tried to use a NULL IOFile!");
		return 0;
	}

	LUA->PushString(pFile->m_strPath.c_str());
	return 1;
}

LUA_FUNCTION(IOFile_Read)
{
	LUA->CheckType(1, IOFile_TypeID);

	IOFile* pFile = LUA->GetUserType<IOFile>(1, IOFile_TypeID);
	if (!pFile)
	{
		LUA->ThrowError("Tried to use a NULL IOFile!");
		return 0;
	}

	if (!std::filesystem::exists(pFile->m_strPath))
	{
		LUA->ThrowError("Tried to use IOFile with non-existent path!");
		return 0;
	}

	LUA->PushString(pFile->read().c_str());
	return 1;
}

LUA_FUNCTION(IOFile_Write)
{
	LUA->CheckType(1, IOFile_TypeID);

	IOFile* pFile = LUA->GetUserType<IOFile>(1, IOFile_TypeID);
	if (!pFile)
	{
		LUA->ThrowError("Tried to use a NULL IOFile!");
		return 0;
	}

	const char* szData = LUA->CheckString(2);

	LUA->PushBool(pFile->write(szData));
	return 1;
}

LUA_FUNCTION(IOFile_Append)
{
	LUA->CheckType(1, IOFile_TypeID);

	IOFile* pFile = LUA->GetUserType<IOFile>(1, IOFile_TypeID);
	if (!pFile)
	{
		LUA->ThrowError("Tried to use a NULL IOFile!");
		return 0;
	}

	const char* szData = LUA->CheckString(2);

	LUA->PushBool(pFile->append(szData));
	return 1;
}

/*

	IODirectory

*/
static int IODirectory_TypeID;

LUA_FUNCTION(IODirectory__tostring)
{
	LUA->CheckType(1, IODirectory_TypeID);

	IODirectory* pDirectory = LUA->GetUserType<IODirectory>(1, IODirectory_TypeID);
	if (!pDirectory)
		LUA->PushString("[NULL IODirectory]");
	else
		LUA->PushString(std::format("IODirectory ['{}']", pDirectory->m_strPath).c_str());

	return 1;
}

LUA_FUNCTION(IODirectory_IsValid)
{
	LUA->CheckType(1, IODirectory_TypeID);

	IODirectory* pDirectory = LUA->GetUserType<IODirectory>(1, IODirectory_TypeID);
	if (!pDirectory)
	{
		LUA->PushBool(false);
		return 1;
	}

	bool exists = std::filesystem::exists(pDirectory->m_strPath);
	bool isDirectory = exists ? std::filesystem::is_directory(pDirectory->m_strPath) : false;

	LUA->PushBool(exists && isDirectory);
	return 1;
}

LUA_FUNCTION(IODirectory_GetPath)
{
	LUA->CheckType(1, IODirectory_TypeID);

	IODirectory* pDirectory = LUA->GetUserType<IODirectory>(1, IODirectory_TypeID);
	if (!pDirectory)
	{
		LUA->ThrowError("Tried to use a NULL IODirectory!");
		return 0;
	}

	LUA->PushString(pDirectory->m_strPath.c_str());
	return 1;
}

LUA_FUNCTION(IODirectory_Read)
{
	LUA->CheckType(1, IODirectory_TypeID);

	IODirectory* pDirectory = LUA->GetUserType<IODirectory>(1, IODirectory_TypeID);
	if (!pDirectory)
	{
		LUA->ThrowError("Tried to use a NULL IODirectory!");
		return 0;
	}

	std::tuple<std::vector<std::string>, std::vector<std::string>> results = pDirectory->read();
	std::vector<std::string> files = std::get<0>(results);
	std::vector<std::string> directories = std::get<1>(results);

	// Return in the style of file.Find
	LUA->CreateTable();
	{
		for (int i = 0; i < files.size(); i++)
		{
			IOFile* pFile = new IOFile();
			pFile->m_strPath = files[i];

			LUA->PushNumber(i);
			LUA->PushUserType(pFile, IOFile_TypeID);
			LUA->RawSet(-3);
		}
	}

	LUA->CreateTable();
	{
		for (int i = 0; i < directories.size(); i++)
		{
			IODirectory* pDirectory = new IODirectory();
			pDirectory->m_strPath = directories[i];

			LUA->PushNumber(i);
			LUA->PushUserType(pDirectory, IODirectory_TypeID);
			LUA->RawSet(-3);
		}
	}

	return 2;
}

/*

	Base IO

*/
LUA_FUNCTION(Exists)
{
	const char* szPath = LUA->CheckString(1);

	LUA->PushBool(std::filesystem::exists(szPath));
	return 1;
}

LUA_FUNCTION(GetFile)
{
	const char* szPath = LUA->CheckString(1);

	IOFile* pFile = new IOFile();
	pFile->m_strPath = std::string(szPath);

	LUA->PushUserType(pFile, IOFile_TypeID);
	return 1;
}

LUA_FUNCTION(GetDirectory)
{
	const char* szPath = LUA->CheckString(1);

	IODirectory* pDirectory = new IODirectory();
	pDirectory->m_strPath = std::string(szPath);

	LUA->PushUserType(pDirectory, IODirectory_TypeID);
	return 1;
}

/*

	Library Setup

*/
void LibraryIO::setup()
{

}

void LibraryIO::push()
{
	GarrysMod::Lua::ILuaInterface* pInterface = this->pInterface;

	// IOFile
	IOFile_TypeID = pInterface->CreateMetaTable("IOFile");
	{
		pInterface->PushString("__index");
		pInterface->Push(-2);
		pInterface->RawSet(-3);

		this->pushcfunction(IOFile_tostring, "__tostring");

		this->pushcfunction(IOFile_IsValid, "IsValid");
		this->pushcfunction(IOFile_GetPath, "GetPath");
		this->pushcfunction(IOFile_Read, "Read");
		this->pushcfunction(IOFile_Write, "Write");
		this->pushcfunction(IOFile_Append, "Append");
		
	}
	pInterface->Pop();

	// IODirectory
	IODirectory_TypeID = pInterface->CreateMetaTable("IODirectory");
	{
		pInterface->PushString("__index");
		pInterface->Push(-2);
		pInterface->RawSet(-3);

		this->pushcfunction(IODirectory__tostring, "__tostring");

		this->pushcfunction(IODirectory_IsValid, "IsValid");
		this->pushcfunction(IODirectory_GetPath, "GetPath");
		this->pushcfunction(IODirectory_Read, "Read");
	}
	pInterface->Pop();
	
	// _G.wwwwwh.io
	pInterface->PushString("io");
	pInterface->CreateTable();
	{
		this->pushcfunction(Exists, "Exists");
		this->pushcfunction(GetFile, "GetFile");
		this->pushcfunction(GetDirectory, "GetDirectory");
	}
	pInterface->RawSet(-3);
}

void LibraryIO::destroy()
{

}