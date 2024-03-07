#pragma once

#include "wwwwwh/hooks/hooks.h"

class HookCursor : public BaseHook
{
public:
	void setup();
	void run();
	void destroy();
};