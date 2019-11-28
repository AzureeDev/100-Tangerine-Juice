#include "SkillDefinitions.h"

vector<SkillData> SkillDefinitions::def = {};

void SkillDefinitions::createDefinitions()
{
	///////////////////////////////////////////////////////
	/*
		Skill:			Dash
		Belongs to:		Suguri
														 */
	///////////////////////////////////////////////////////
	SkillData dash;
	dash.skillIdentifier = "dash";
	dash.skillName = "Dash";
	dash.skillDescription = "Add +3 to your next movement roll.";
	dash.skillOwner = "suguri";
	dash.skillIconPath = "assets/skills/skl_dash.png";
	dash.skillCallback = [](PlayerUnit* sender, PlayerUnit* receiver) 
	{
		
	};
	dash.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Speeding Up
		Belongs to:		Suguri
														 */
	///////////////////////////////////////////////////////
	SkillData speedup;
	speedup.skillIdentifier = "speedup";
	speedup.skillName = "Acceleration";
	speedup.skillDescription = "Gain +2 Evasion for this battle, and -1 Defense.";
	speedup.skillOwner = "suguri";
	speedup.skillIconPath = "assets/skills/skl_speedup.png";
	speedup.skillCallback = [](PlayerUnit* sender, PlayerUnit* receiver)
	{
		
	};
	speedup.skillCost = 2;
	speedup.skillUsableInsideBattle = true;
	speedup.skillUsableOutsideBattle = false;

	///////////////////////////////////////////////////////
	/*
		Skill:			Falling Stars
		Belongs to:		Suguri
														 */
	///////////////////////////////////////////////////////
	SkillData hyper_fallingstars;
	hyper_fallingstars.skillIdentifier = "hyper_fallingstars";
	hyper_fallingstars.skillName = "Falling Stars";
	hyper_fallingstars.skillDescription = "At each start of your turn, you will get 3 to 6 stars. This effect can be stacked, but is lost upon getting KO'd.";
	hyper_fallingstars.skillOwner = "suguri";
	hyper_fallingstars.skillIconPath = "assets/skills/skl_hyper_fallingstars.png";
	hyper_fallingstars.skillCallback = [](PlayerUnit* sender, PlayerUnit* receiver)
	{
		
	};
	hyper_fallingstars.skillCost = 4;

	///////////////////////////////////////////////////////
	/*
		Skill:			Deep Clone
		Belongs to:		Sora
														 */
	///////////////////////////////////////////////////////
	SkillData deepclone;
	deepclone.skillIdentifier = "deepclone";
	deepclone.skillName = "Deep Clone";
	deepclone.skillDescription = "Steal the positive stats of the enemy to convert them into a temporary bonus for this battle.";
	deepclone.skillOwner = "sora";
	deepclone.skillIconPath = "assets/skills/skl_deepclone.png";
	deepclone.skillCallback = [](PlayerUnit* sender, PlayerUnit* receiver)
	{

	};
	deepclone.skillCost = 2;
	deepclone.skillUsableInsideBattle = true;
	deepclone.skillUsableOutsideBattle = false;

	///////////////////////////////////////////////////////
	/*
		Skill:			Shield Invert
		Belongs to:		Sora
														 */
	///////////////////////////////////////////////////////
	SkillData shieldinvert;
	shieldinvert.skillIdentifier = "shieldinvert";
	shieldinvert.skillName = "Shield Invert";
	shieldinvert.skillDescription = "Deal damage depending on the current attack of the enemy minus their defense. No counter attack can be made, and the battle immediately ends.";
	shieldinvert.skillOwner = "sora";
	shieldinvert.skillIconPath = "assets/skills/skl_shieldinvert.png";
	shieldinvert.skillCallback = [](PlayerUnit* sender, PlayerUnit* receiver)
	{

	};
	shieldinvert.skillCost = 3;
	shieldinvert.skillUsableInsideBattle = true;
	shieldinvert.skillUsableOutsideBattle = false;

	///////////////////////////////////////////////////////
	/*
		Skill:			Extraordinary Specs
		Belongs to:		Sora
														 */
	///////////////////////////////////////////////////////
	SkillData extraspecs;
	extraspecs.skillIdentifier = "extraspecs";
	extraspecs.skillName = "Extraordinary Specs";
	extraspecs.skillDescription = "For 1 entire chapter: Always roll 6.";
	extraspecs.skillOwner = "sora";
	extraspecs.skillIconPath = "assets/skills/skl_hyper_extraspecs.png";
	extraspecs.skillCallback = [](PlayerUnit* sender, PlayerUnit* receiver)
	{

	};
	extraspecs.skillCost = 5;

	SkillDefinitions::def.push_back(dash);
	SkillDefinitions::def.push_back(speedup);
	SkillDefinitions::def.push_back(hyper_fallingstars);
	SkillDefinitions::def.push_back(deepclone);
	SkillDefinitions::def.push_back(shieldinvert);
	SkillDefinitions::def.push_back(extraspecs);

	SkillDefinitions::appendSkillToUnit();
}

void SkillDefinitions::appendSkillToUnit()
{
	for (const auto& skillData : SkillDefinitions::def)
	{
		for (auto& unitData : UnitDefinitions::def)
		{
			if (skillData.skillOwner == unitData.unitId)
			{
				unitData.unitSkills.push_back(skillData);
			}
		}
	}
}
