#pragma once

#include <string>
#include <vector>

class BaseHook
{
public:
	std::string name;

	virtual void setup() = 0;
	virtual void run() = 0;
	virtual void destroy() = 0;
};

class Hooks
{
public:
	std::vector<BaseHook*> hooks;

	void addhook(BaseHook* pHook, std::string name);
	BaseHook* findhook(std::string name);
	void runhooks(std::string name);

	void setup();
	void destroy();
};