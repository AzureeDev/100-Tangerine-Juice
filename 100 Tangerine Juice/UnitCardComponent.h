#pragma once
#include "LClass.h"
#include "UnitDefinitions.h"
#include "Unit.h"

class UnitCardComponent : public LClass
{
private:
	UnitParams unitParams;

	LTexture unitCardBg;
	Unit unit;
	LTexture unitDescriptionLabel;

public:
	UnitCardComponent(const UnitParams params);
	void init();
	UnitParams getParams();
	void update(const float dt);
};

