#include "wwwwwh/hooks/hooks/cursor.h"

#include "wwwwwh/globals.h"
#include "wwwwwh/library/imgui/imgui.h"

#include "vgui/ISurfaceV30.h"
#include "MinHook.h"

typedef void(__thiscall* UnlockCursor)(ISurfaceV30::ISurface*);
static UnlockCursor oUnlockCursor = NULL;

typedef void(__thiscall* LockCursor)(ISurfaceV30::ISurface*);
static LockCursor oLockCursor = NULL;

void hkUnlockCursor(ISurfaceV30::ISurface* _this)
{
	LibraryImGui* pLibraryImGui = (LibraryImGui*)globals->pLibrary->findlibrary("ImGui");
	if (pLibraryImGui)
		pLibraryImGui->cursorVisible = true;

	return oUnlockCursor(_this);
}

void hkLockCursor(ISurfaceV30::ISurface* _this)
{
	LibraryImGui* pLibraryImGui = (LibraryImGui*)globals->pLibrary->findlibrary("ImGui");
	if (pLibraryImGui)
	{
		if (pLibraryImGui->grabInput)
			return hkUnlockCursor(_this);

		pLibraryImGui->cursorVisible = false;
	}

	return oLockCursor(_this);
}

void HookCursor::setup()
{
	void* unlockCursor = globals->pPointers->getvfunc<void*>(globals->pPointers->pSurface, 65);
	void* lockCursor = globals->pPointers->getvfunc<void*>(globals->pPointers->pSurface, 66);

	MH_CreateHook(unlockCursor, hkUnlockCursor, (void**)&oUnlockCursor);
	MH_CreateHook(lockCursor, hkLockCursor, (void**)&oLockCursor);
}

void HookCursor::run()
{

}

void HookCursor::destroy()
{
	MH_DisableHook(oUnlockCursor);
	MH_DisableHook(oLockCursor);
}