#include "SkillDefinitions.h"
#include "Utils.h"

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
	dash.skillType = SkillType::Boost;
	dash.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{
		sender->setStatusMessage("DASH\n+ 3 MOVEMENT ROLL", { 100, 255, 100, 255 });
		sender->createSkillEffect(
			{
				"dash",
				1,
				1
			}
		);
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
	speedup.skillType = SkillType::Defensive;
	speedup.skillCallback = [](shared_ptr<PlayerUnit>, shared_ptr<PlayerUnit> receiver)
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
	hyper_fallingstars.skillName = "Revival of Stars";
	hyper_fallingstars.skillDescription = "You will now get 3 to 6 stars for every start of your turn. The effect can be stacked, but is lost upon getting KO'd.";
	hyper_fallingstars.skillOwner = "suguri";
	hyper_fallingstars.skillIconPath = "assets/skills/skl_hyper_fallingstars.png";
	hyper_fallingstars.skillType = SkillType::Boost;
	hyper_fallingstars.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{
		sender->setStatusMessage("FALLING STARS", { 255, 255, 0, 255 });
		sender->createSkillEffect(
			{
				"hyper_fallingstars",
				-1,
				1
			}
		);
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
	deepclone.skillType = SkillType::Offensive;
	deepclone.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
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
	shieldinvert.skillType = SkillType::Defensive;
	shieldinvert.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
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
	extraspecs.skillType = SkillType::Boost;
	extraspecs.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	extraspecs.skillCost = 5;

	///////////////////////////////////////////////////////
	/*
		Skill:			Beam
		Belongs to:		Sora (M)
														 */
	///////////////////////////////////////////////////////
	SkillData beam;
	beam.skillIdentifier = "beam";
	beam.skillName = "Laser Beam";
	beam.skillDescription = "A random unit will take 1 damage.";
	beam.skillOwner = "sora_m";
	beam.skillIconPath = "assets/skills/skl_placeholder.png";
	beam.skillType = SkillType::Offensive;
	beam.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	beam.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Quick Restoration
		Belongs to:		Sora (M)
														 */
	///////////////////////////////////////////////////////
	SkillData quickrestore;
	quickrestore.skillIdentifier = "quickrestore";
	quickrestore.skillName = "Quick Restoration";
	quickrestore.skillDescription = "Heal yourself by 1 HP.";
	quickrestore.skillOwner = "sora_m";
	quickrestore.skillIconPath = "assets/skills/skl_placeholder.png";
	quickrestore.skillType = SkillType::Boost;
	quickrestore.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	quickrestore.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Fair Battle
		Belongs to:		Hime
														 */
	///////////////////////////////////////////////////////
	SkillData fairbattle;
	fairbattle.skillIdentifier = "fairbattle";
	fairbattle.skillName = "Fair Battle";
	fairbattle.skillDescription = "The opponent and your stats will be adjusted to be 0.";
	fairbattle.skillOwner = "hime";
	fairbattle.skillIconPath = "assets/skills/skl_placeholder.png";
	fairbattle.skillType = SkillType::Defensive;
	fairbattle.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	fairbattle.skillCost = 3;
	fairbattle.skillUsableInsideBattle = true;
	fairbattle.skillUsableOutsideBattle = false;

	///////////////////////////////////////////////////////
	/*
		Skill:			Drop Barrier
		Belongs to:		Hime
														 */
	///////////////////////////////////////////////////////
	SkillData dropbarrier;
	dropbarrier.skillIdentifier = "dropbarrier";
	dropbarrier.skillName = "Drop Barrier";
	dropbarrier.skillDescription = "The next Drop panel won't do any effect to you.";
	dropbarrier.skillOwner = "hime";
	dropbarrier.skillIconPath = "assets/skills/skl_placeholder.png";
	dropbarrier.skillType = SkillType::Boost;
	dropbarrier.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	dropbarrier.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Chains
		Belongs to:		Hime
														 */
	///////////////////////////////////////////////////////
	SkillData chains;
	chains.skillIdentifier = "chains";
	chains.skillName = "Chains";
	chains.skillDescription = "The next turn of all other units will be skipped.";
	chains.skillOwner = "hime";
	chains.skillIconPath = "assets/skills/skl_placeholder.png";
	chains.skillType = SkillType::Boost;
	chains.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	chains.skillCost = 4;

	///////////////////////////////////////////////////////
	/*
		Skill:			Extend
		Belongs to:		Sham
														 */
	///////////////////////////////////////////////////////
	SkillData extend;
	extend.skillIdentifier = "extend";
	extend.skillName = "Extend";
	extend.skillDescription = "If you are KO'd, you will automatically revive on your next turn.";
	extend.skillOwner = "sham";
	extend.skillIconPath = "assets/skills/skl_placeholder.png";
	extend.skillType = SkillType::Boost;
	extend.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	extend.skillCost = 3;

	///////////////////////////////////////////////////////
	/*
		Skill:			Delta Field
		Belongs to:		Sham
														 */
	///////////////////////////////////////////////////////
	SkillData deltafield;
	deltafield.skillIdentifier = "deltafield";
	deltafield.skillName = "Delta Field";
	deltafield.skillDescription = "The opponent in this battle will always roll 1.";
	deltafield.skillOwner = "sham";
	deltafield.skillIconPath = "assets/skills/skl_placeholder.png";
	deltafield.skillType = SkillType::Offensive;
	deltafield.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	deltafield.skillCost = 3;

	///////////////////////////////////////////////////////
	/*
		Skill:			SB Bomb
		Belongs to:		SB
														 */
	///////////////////////////////////////////////////////
	SkillData sbbomb;
	sbbomb.skillIdentifier = "sbbomb";
	sbbomb.skillName = "SB Bomb";
	sbbomb.skillDescription = "A random unit will take 1 to 3 damage.";
	sbbomb.skillOwner = "sb";
	sbbomb.skillIconPath = "assets/skills/skl_placeholder.png";
	sbbomb.skillType = SkillType::Offensive;
	sbbomb.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	sbbomb.skillCost = 3;

	///////////////////////////////////////////////////////
	/*
		Skill:			Mutilation
		Belongs to:		SB
														 */
	///////////////////////////////////////////////////////
	SkillData mutilation;
	mutilation.skillIdentifier = "mutilation";
	mutilation.skillName = "Mutilation";
	mutilation.skillDescription = "Pay 1 HP to gain 2 Attack for this battle.";
	mutilation.skillOwner = "sb";
	mutilation.skillIconPath = "assets/skills/skl_placeholder.png";
	mutilation.skillType = SkillType::Offensive;
	mutilation.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	mutilation.skillCost = 4;

	///////////////////////////////////////////////////////
	/*
		Skill:			Grand Finale
		Belongs to:		SB
														 */
	///////////////////////////////////////////////////////
	SkillData grandfinale;
	grandfinale.skillIdentifier = "grandfinale";
	grandfinale.skillName = "Grand Finale";
	grandfinale.skillDescription = "All the other units will be KO'd instantly.";
	grandfinale.skillOwner = "sb";
	grandfinale.skillIconPath = "assets/skills/skl_placeholder.png";
	grandfinale.skillType = SkillType::Offensive;
	grandfinale.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	grandfinale.skillCost = 8;

	///////////////////////////////////////////////////////
	/*
		Skill:			Stealth Mode
		Belongs to:		Tsih
														 */
	///////////////////////////////////////////////////////
	SkillData stealth;
	stealth.skillIdentifier = "stealth";
	stealth.skillName = "Stealth Mode";
	stealth.skillDescription = "For 3 chapters, Encounter panels won't do any effect when you land on them, and other units cannot challenge you.";
	stealth.skillOwner = "tsih";
	stealth.skillIconPath = "assets/skills/skl_placeholder.png";
	stealth.skillType = SkillType::Boost;
	stealth.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	stealth.skillCost = 4;

	///////////////////////////////////////////////////////
	/*
		Skill:			Stars Gift
		Belongs to:		Saki
														 */
	///////////////////////////////////////////////////////
	SkillData starsgift;
	starsgift.skillIdentifier = "starsgift";
	starsgift.skillName = "Stars Gift";
	starsgift.skillDescription = "Gain 5 to 15 stars.";
	starsgift.skillOwner = "saki";
	starsgift.skillIconPath = "assets/skills/skl_placeholder.png";
	starsgift.skillType = SkillType::Boost;
	starsgift.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	starsgift.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Cookie Time!
		Belongs to:		Saki
														 */
	///////////////////////////////////////////////////////
	SkillData cookie;
	cookie.skillIdentifier = "cookie";
	cookie.skillName = "Cookie Time!";
	cookie.skillDescription = "All units will be healed by 1 HP. Each unit affected will pay you back 10 stars.";
	cookie.skillOwner = "saki";
	cookie.skillIconPath = "assets/skills/skl_placeholder.png";
	cookie.skillType = SkillType::Boost;
	cookie.skillCallback = [](shared_ptr<PlayerUnit> sender, shared_ptr<PlayerUnit> receiver)
	{

	};
	cookie.skillCost = 3;

	/*
	*
	*
	*
	*
	*/

	SkillDefinitions::def.push_back(dash);
	SkillDefinitions::def.push_back(speedup);
	SkillDefinitions::def.push_back(hyper_fallingstars);
	SkillDefinitions::def.push_back(deepclone);
	SkillDefinitions::def.push_back(shieldinvert);
	SkillDefinitions::def.push_back(extraspecs);
	SkillDefinitions::def.push_back(beam);
	SkillDefinitions::def.push_back(quickrestore);
	SkillDefinitions::def.push_back(fairbattle);
	SkillDefinitions::def.push_back(dropbarrier);
	SkillDefinitions::def.push_back(chains);
	SkillDefinitions::def.push_back(extend);
	SkillDefinitions::def.push_back(stealth);
	SkillDefinitions::def.push_back(deltafield);
	SkillDefinitions::def.push_back(sbbomb);
	SkillDefinitions::def.push_back(mutilation);
	SkillDefinitions::def.push_back(grandfinale);
	SkillDefinitions::def.push_back(starsgift);
	SkillDefinitions::def.push_back(cookie);
	

	SkillDefinitions::appendSkillToUnit();
}

vector<SkillData> SkillDefinitions::getUnitSkills(const string unitIdentifier)
{
	vector<SkillData> skills = {};

	for (const auto& skillData : SkillDefinitions::def)
	{
		if (skillData.skillOwner == unitIdentifier)
		{
			skills.push_back(skillData);
		}
	}

	return skills;
}

SkillData SkillDefinitions::getSkillData(const string skillIdentifier)
{
	for (const auto& skillData : SkillDefinitions::def)
	{
		if (skillData.skillIdentifier == skillIdentifier)
		{
			return skillData;
		}
	}

	return {};
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
