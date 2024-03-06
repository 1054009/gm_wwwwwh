#pragma once

#include "wwwwwh/hooks/hooks.h"

class HookLockCursor : public BaseHook
{
public:
	void setup();
	void run();
	void destroy();
};