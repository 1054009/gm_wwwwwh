#pragma once

#include "wwwwwh/library/library.h"

class LibraryModule : public BaseLibrary
{
public:
	void setup();
	void push();
	void destroy();
};