#include "wwwwwh/hooks/hooks/lockcursor.h"

#include "wwwwwh/globals.h"
#include "wwwwwh/library/imgui/imgui.h"

#include "vgui/ISurfaceV30.h"
#include "MinHook.h"

typedef void(__thiscall* LockCursor)(ISurfaceV30::ISurface*);
static LockCursor oLockCursor = NULL;

void hkLockCursor(ISurfaceV30::ISurface* _this)
{
	LibraryImGui* pLibraryImGui = (LibraryImGui*)globals->pLibrary->findlibrary("ImGui");
	if (pLibraryImGui && pLibraryImGui->grabInput)
	{
		_this->UnlockCursor();
		return;
	}

	return oLockCursor(_this);
}

void HookLockCursor::setup()
{
	void* lockCursor = globals->pPointers->getvfunc<void*>(globals->pPointers->pSurface, 66);

	MH_CreateHook(lockCursor, hkLockCursor, (void**)&oLockCursor);
}

void HookLockCursor::run()
{

}

void HookLockCursor::destroy()
{
	MH_DisableHook(oLockCursor);
}