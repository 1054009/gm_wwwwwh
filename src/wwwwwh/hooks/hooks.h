#pragma once

#include <string>
#include <vector>

class BaseHook
{
public:
	std::string name;

	virtual void setup() = 0;
	virtual void destroy() = 0;
};

class Hooks
{
public:
	std::vector<BaseHook*> hooks;

	BaseHook* addhook(BaseHook* pHook);
	BaseHook* findhook(std::string name);

	void setup();
	void destroy();
};