#pragma once

#include "wwwwwh/library/library.h"

class LibraryIO : public BaseLibrary
{
public:
	void setup();
	void push();
	void destroy();
};