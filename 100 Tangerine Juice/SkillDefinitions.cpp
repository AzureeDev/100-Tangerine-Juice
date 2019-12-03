#include "SkillDefinitions.h"
#include "Utils.h"
#include "Globals.h"
#include "OverlayManager.h"
#include "MusicManager.h"

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
	dash.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("DASH\n+ 3 MOVEMENT ROLL", { 100, 255, 100, 255 });
		unit->createSkillEffect(
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
	speedup.skillDescription = "For 2 chapters: Gain +2 Evasion, and -1 Defense.";
	speedup.skillOwner = "suguri";
	speedup.skillIconPath = "assets/skills/skl_speedup.png";
	speedup.skillType = SkillType::Defensive;
	speedup.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("ACCELERATION", { 100, 255, 100, 255 });
		unit->createSkillEffect(
			{
				"speedup",
				2,
				1
			}
		);

		unit->updateTempStats(0, -1, 2);
	};
	speedup.skillEffectEnded = [](shared_ptr<PlayerUnit> unit)
	{
		unit->updateTempStats(0, 1, -2);
	};
	speedup.skillCost = 2;

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
	hyper_fallingstars.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("REVIVAL OF STARS", { 255, 255, 0, 255 });
		unit->createSkillEffect(
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
		Skill:			Last Chance
		Belongs to:		Sora
														 */
	///////////////////////////////////////////////////////
	SkillData lastchance;
	lastchance.skillIdentifier = "lastchance";
	lastchance.skillName = "Last Chance";
	lastchance.skillDescription = "For 2 chapters: Gain +3 Evasion, but lose 3 Attack and 3 Defense.";
	lastchance.skillOwner = "sora";
	lastchance.skillIconPath = "assets/skills/skl_deepclone.png";
	lastchance.skillType = SkillType::Offensive;
	lastchance.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("LAST CHANCE", { 100, 255, 100, 255 });
		unit->createSkillEffect(
			{
				"lastchance",
				2,
				1
			}
		);

		unit->updateTempStats(-3, -3, 3);
	};
	lastchance.skillEffectEnded = [](shared_ptr<PlayerUnit> unit)
	{
		unit->updateTempStats(3, 3, -3);
	};
	lastchance.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Shield Invert
		Belongs to:		Sora
														 */
	///////////////////////////////////////////////////////
	SkillData shieldinvert;
	shieldinvert.skillIdentifier = "shieldinvert";
	shieldinvert.skillName = "Shield Breaker";
	shieldinvert.skillDescription = "For 3 chapters: All units, including yourself, will lose 1 Defense.";
	shieldinvert.skillOwner = "sora";
	shieldinvert.skillIconPath = "assets/skills/skl_shieldinvert.png";
	shieldinvert.skillType = SkillType::Defensive;
	shieldinvert.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("SHIELD BREAKER", { 255, 100, 100, 255 });
		unit->createSkillEffect(
			{
				"shieldinvert",
				3,
				1
			}
		);
		for (const auto& unit : Globals::gameManager->getUnits())
		{
			unit->updateTempStats(0, -1, 0);
		}
	};
	shieldinvert.skillEffectEnded = [](shared_ptr<PlayerUnit> unit)
	{
		for (const auto& unit : Globals::gameManager->getUnits())
		{
			unit->updateTempStats(0, 1, 0);
		}
	};
	shieldinvert.skillCost = 3;

	///////////////////////////////////////////////////////
	/*
		Skill:			Extraordinary Specs
		Belongs to:		Sora
														 */
	///////////////////////////////////////////////////////
	SkillData extraspecs;
	extraspecs.skillIdentifier = "extraspecs";
	extraspecs.skillName = "Extraordinary Specs";
	extraspecs.skillDescription = "For 1 chapter: Always roll 6.";
	extraspecs.skillOwner = "sora";
	extraspecs.skillIconPath = "assets/skills/skl_hyper_extraspecs.png";
	extraspecs.skillType = SkillType::Boost;
	extraspecs.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("EXTRAORDINARY SPECS", { 255, 255, 0, 255 });
		unit->createSkillEffect(
			{
				"extraspecs",
				1,
				1
			}
		);
	};
	extraspecs.skillCost = 4;

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
	beam.skillIconPath = "assets/skills/skl_laserbeam.png";
	beam.skillType = SkillType::Offensive;
	beam.skillConditionFunction = [](shared_ptr<PlayerUnit> unit)
	{
		if (Globals::gameManager->getAliveUnitsCount() <= 1)
		{
			return false;
		}
		
		return true;
	};
	beam.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		const shared_ptr<PlayerUnit> randomUnit = Globals::gameManager->getRandomAliveUnitExcluding(unit);
		randomUnit->setActiveUnit();
		randomUnit->takeTerrainDamage(1);

		Globals::timer->createTimer("delayCameraBackToUnit", 1, [unit, randomUnit]() { randomUnit->setInactiveUnit(); unit->setActiveUnit();  }, 1);
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
	quickrestore.skillIconPath = "assets/skills/skl_quickrestore.png";
	quickrestore.skillType = SkillType::Boost;
	quickrestore.skillConditionFunction = [](shared_ptr<PlayerUnit> unit)
	{
		if (unit->getCurrentHealth() == unit->getMaxHealth())
		{
			return false;
		}

		return true;
	};
	quickrestore.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->heal(1);
		unit->setStatusMessage("QUICK RESTORATION", { 255, 150, 255, 255 });
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
	fairbattle.skillName = "Ransom";
	fairbattle.skillDescription = "For 3 chapters: All battles won will give you 50% of the KO'd unit's stars.";
	fairbattle.skillOwner = "hime";
	fairbattle.skillIconPath = "assets/skills/skl_fairbattle.png";
	fairbattle.skillType = SkillType::Defensive;
	fairbattle.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("RANSOM", { 255, 0, 0, 255 });
		unit->createSkillEffect(
			{
				"fairbattle",
				3,
				1
			}
		);
	};
	fairbattle.skillCost = 3;

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
	dropbarrier.skillIconPath = "assets/skills/skl_barrier.png";
	dropbarrier.skillType = SkillType::Boost;
	dropbarrier.skillConditionFunction = [](shared_ptr<PlayerUnit> unit)
	{
		if (unit->hasSkillEffect("dropbarrier"))
		{
			return false;
		}

		return true;
	};
	dropbarrier.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("DROP BARRIER", { 125, 125, 255, 255 });
		unit->createSkillEffect(
			{
				"dropbarrier",
				-1,
				1
			}
		);
	};
	dropbarrier.skillCost = 2;

	///////////////////////////////////////////////////////
	/*
		Skill:			Binding Chains
		Belongs to:		Hime
														 */
	///////////////////////////////////////////////////////
	SkillData chains;
	chains.skillIdentifier = "chains";
	chains.skillName = "Binding Chains";
	chains.skillDescription = "The next turn of all other units will be skipped.";
	chains.skillOwner = "hime";
	chains.skillIconPath = "assets/skills/skl_chains.png";
	chains.skillType = SkillType::Boost;
	chains.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		for (const auto& chainedUnit : Globals::gameManager->getUnits())
		{
			if (chainedUnit->identifier() != unit->identifier())
			{
				chainedUnit->playTempAnimation("dmg", 1);
				chainedUnit->setStatusMessage("CHAINED", { 255, 0, 0, 255 });
				chainedUnit->createSkillEffect(
					{
						"chains",
						1,
						1
					}
				);
			}
		}
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
	extend.skillDescription = "Stock the following effect: If you are KO'd, you will automatically revive on your next turn.";
	extend.skillOwner = "sham";
	extend.skillIconPath = "assets/skills/skl_extend.png";
	extend.skillRemoveOnDeath = false;
	extend.skillType = SkillType::Boost;
	extend.skillConditionFunction = [](shared_ptr<PlayerUnit> unit)
	{
		if (unit->hasSkillEffect("extend"))
		{
			return false;
		}

		return true;
	};
	extend.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->setStatusMessage("EXTEND", { 125, 255, 125, 255 });
		unit->createSkillEffect(
			{
				"extend",
				-1,
				1
			}
		);
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
	deltafield.skillDescription = "Give the following effect to other units: All dice rolls will be 1.\nNote: Extraordinary Specs overrides this effect.";
	deltafield.skillOwner = "sham";
	deltafield.skillIconPath = "assets/skills/skl_deltafield.png";
	deltafield.skillType = SkillType::Offensive;
	deltafield.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		for (const auto& deltaFieldedUnit : Globals::gameManager->getUnits())
		{
			if (deltaFieldedUnit->identifier() != unit->identifier())
			{
				deltaFieldedUnit->playTempAnimation("dmg", 1);
				deltaFieldedUnit->setStatusMessage("DELTA FIELD", { 0, 150, 255, 255 });
				deltaFieldedUnit->createSkillEffect(
					{
						"deltafield",
						1,
						1
					}
				);
			}
		}
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
	sbbomb.skillIconPath = "assets/skills/skl_sbbomb.png";
	sbbomb.skillType = SkillType::Offensive;
	sbbomb.skillConditionFunction = [](shared_ptr<PlayerUnit> unit)
	{
		if (Globals::gameManager->getAliveUnitsCount() <= 1)
		{
			return false;
		}

		return true;
	};
	sbbomb.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		const shared_ptr<PlayerUnit> randomUnit = Globals::gameManager->getRandomAliveUnitExcluding(unit);
		randomUnit->setActiveUnit();
		randomUnit->takeTerrainDamage(Utils::randBetween(1, 3));

		Globals::timer->createTimer("delayCameraBackToUnit", 1, [unit, randomUnit]() { randomUnit->setInactiveUnit(); unit->setActiveUnit();  }, 1);
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
	mutilation.skillDescription = "For 2 chapters: Pay 1 HP to gain 2 Attack.";
	mutilation.skillOwner = "sb";
	mutilation.skillIconPath = "assets/skills/skl_mutilation.png";
	mutilation.skillType = SkillType::Offensive;
	mutilation.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->takeTerrainDamage(1);
		unit->setStatusMessage("MUTILATION", { 255, 0, 125, 255 });
		unit->createSkillEffect(
			{
				"mutilation",
				2,
				1
			}
		);

		unit->updateTempStats(2, 0, 0);
	};
	mutilation.skillConditionFunction = [](shared_ptr<PlayerUnit> unit)
	{
		if (unit->hasSkillEffect("mutilation"))
		{
			return false;
		}

		if (unit->getCurrentHealth() <= 1)
		{
			return false;
		}

		return true;
	};
	mutilation.skillEffectEnded = [](shared_ptr<PlayerUnit> unit)
	{
		unit->updateTempStats(-2, 0, 0);
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
	grandfinale.skillIconPath = "assets/skills/skl_grandfinale.png";
	grandfinale.skillType = SkillType::Offensive;
	grandfinale.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		OverlayManager::fadeIn(12);
		MusicManager::fadeOutMusic(500);

		Globals::timer->createTimer("grandFinaleDelay", 1, [unit]()
			{
				MusicManager::playMusic("assets/musics/finale.mp3");
				LilacClasses::Tangerine->getWorld().setWorldColor({ 255, 0, 0, 255 });
				OverlayManager::fadeOut(12);

				for (const auto& killedUnit : Globals::gameManager->getUnits())
				{
					if (killedUnit->identifier() != unit->identifier())
					{
						killedUnit->takeTerrainDamage(666);
					}
				}
			}
		, 1);
	};
	grandfinale.skillCost = 7;

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
	stealth.skillIconPath = "assets/skills/skl_ghost.png";
	stealth.skillType = SkillType::Boost;
	stealth.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unit->texture().setColor({ 115, 240, 255, 255 }, true);
		unit->setStatusMessage("STEALTH MODE", { 115, 240, 255, 255 });
		unit->createSkillEffect(
			{
				"stealth",
				3,
				1
			}
		);
	};
	stealth.skillEffectEnded = [](shared_ptr<PlayerUnit> unit)
	{
		unit->texture().setColor({ 255, 255, 255, 255 }, true);
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
	starsgift.skillDescription = "Gain 10 to 25 stars.";
	starsgift.skillOwner = "saki";
	starsgift.skillIconPath = "assets/skills/skl_stargift.png";
	starsgift.skillType = SkillType::Boost;
	starsgift.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		const unsigned stars = Utils::randBetween(10, 25);
		unit->setStatusMessage("STARS GIFT\n+ " + std::to_string(stars) + " STARS", { 255, 255, 0, 255 });
		unit->addStars(stars);
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
	cookie.skillName = "Saki's Cookie";
	cookie.skillDescription = "All units, excepted yourself, will be healed by 1 HP, unless they are full HP. KO'd units will be revived with 1 HP. You will get 10 stars for each affected unit.";
	cookie.skillOwner = "saki";
	cookie.skillIconPath = "assets/skills/skl_cookie.png";
	cookie.skillType = SkillType::Boost;
	cookie.skillCallback = [](shared_ptr<PlayerUnit> unit)
	{
		unsigned stars = 0;

		for (const auto& healedUnit : Globals::gameManager->getUnits())
		{
			if (healedUnit->identifier() != unit->identifier())
			{
				if (healedUnit->getCurrentHealth() < healedUnit->getMaxHealth())
				{
					healedUnit->heal(1);
					stars += 10;
				}
			}
		}

		unit->setStatusMessage("COOKIE TIME\n+ " + std::to_string(stars) + " STARS", { 255, 255, 0, 255 });
		unit->addStars(stars);
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
	SkillDefinitions::def.push_back(lastchance);
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
