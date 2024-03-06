#pragma once

#include "wwwwwh/hooks/hooks.h"

class HookWndProc : public BaseHook
{
public:
	void setup();
	void run();
	void destroy();
};