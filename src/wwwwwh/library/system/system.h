#pragma once

#include "wwwwwh/library/library.h"

class LibrarySystem : public BaseLibrary
{
public:
	void setup();
	void push();
	void destroy();
};