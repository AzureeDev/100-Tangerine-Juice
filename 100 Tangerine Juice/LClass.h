#pragma once
#include <string>

class LClass
{
protected:
	std::string className;

public:
	LClass(const std::string className, LClass* newClass);
	virtual ~LClass();
	virtual void init();
	virtual void update(const float deltaTime);
	LClass* getClass(const std::string className);
	std::string getName();
};