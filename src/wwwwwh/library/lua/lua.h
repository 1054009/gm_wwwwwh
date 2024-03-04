#pragma once

#include "wwwwwh/library/library.h"

class LibraryLua : public BaseLibrary
{
public:
	void setup();
	void push();
	void destroy();
};