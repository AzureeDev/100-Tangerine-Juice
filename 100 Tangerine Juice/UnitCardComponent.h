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
	LTexture unitArt;
	LTexture unitDescriptionLabel;

	// Stats
	LTexture unitStatsTitle;
	LTexture unitHPLabel;
	LTexture unitHPAmount;
	LTexture unitAtkLabel;
	LTexture unitAtkAmount;
	LTexture unitDefLabel;
	LTexture unitDefAmount;
	LTexture unitEvaLabel;
	LTexture unitEvaAmount;
	LTexture unitRecLabel;
	LTexture unitRecAmount;
	LTexture unitPwrLabel;
	LTexture unitPwrEffect;
	LTexture unitPwrAmount;

	// Skills
	LTexture unitSkillTitle;

public:
	UnitCardComponent(const UnitParams params);
	void init();
	UnitParams getParams();
	void update(const float dt);
};
