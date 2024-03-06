#pragma once

#include "wwwwwh/hooks/hooks.h"

class HookReset : public BaseHook
{
public:
	void setup();
	void run();
	void destroy();
};