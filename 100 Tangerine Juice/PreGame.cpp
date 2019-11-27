#include "PreGame.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"
#include "Utils.h"

const string DEFAULT_WORLD_ID = "ri_se_sky";
const SDL_Color DEFAULT_WORLD_COLOR = { 79, 202, 255, 255 };

PreGame::PreGame()
{
	LilacClasses::PreGame = this;
}

PreGame::~PreGame()
{
	for (size_t i = 0; i < this->unitPickButtons.size(); ++i)
	{
		Globals::UI->destroyButton(this->unitPickButtons[i].unitIdentifier + "_pickBtn");
	}

	Globals::UI->destroyButton("startTangerine");
	Globals::UI->destroyButton("worldGenRandom");
	Globals::UI->destroyButton("worldGenFairRandom");
	Globals::UI->destroyButton("worldGenBattlefield");
}

void PreGame::init()
{
	/* Reverse back to normal, since the main menu had to reverse once for the buttons. */
	std::reverse(UnitDefinitions::def.begin(), UnitDefinitions::def.end());

	OverlayManager::fadeOut(3);
	MusicManager::playMusic("assets/musics/begins.mp3");

	pregameBg.setNewTexture("assets/ui/ig/characterSelectBg.png");
	selectedWorld = World("assets/worlds/" + DEFAULT_WORLD_ID + ".png");
	selectedWorld.setWorldColor(DEFAULT_WORLD_COLOR);
	selectedWorld.setAllowClouds(true);
	selectedWorld.setScrollMultiplier(3);

	/* Create our pick buttons and give a callback */
	for (const auto& unitData : UnitDefinitions::def)
	{
		LButton* btn = Globals::UI->createButton(unitData.unitId + "_pickBtn", "assets/units/" + unitData.unitId + "/_select.png");
		btn->getTexture().setColor({ 125, 125, 125, 255 }, true);
		btn->setHighlightColor({ 255, 255, 255, 255 });
		btn->supplyCallback([this, unitData]() {
			this->setPickedUnit(unitData.unitId);
		});

		this->unitPickButtons.push_back({ unitData.unitId, btn });
	}

	/* Then position them */
	for (size_t i = 0; i < this->unitPickButtons.size(); ++i)
	{
		/* Base pos, base the others on it afterwards */
		if (i == 0)
		{
			this->unitPickButtons[i].unitButton->setPosition(
				{
					810,
					200
				}
			);
		}
		else
		{
			this->unitPickButtons[i].unitButton->setPosition(
				{
					this->unitPickButtons[i - 1].unitButton->getX() + this->unitPickButtons[i - 1].unitButton->getTexture().getWidth() - 10,
					200
				}
			);
		}
		
	}

	unitPickLabel.createText("Units", { 25, 25, 25, 255 }, 0, Globals::resources->getFont("defaultFont32"));
	unitPickLabel.setPosition(
		{
			this->unitPickButtons[0].unitButton->getTexture().top().x + 32,
			this->unitPickButtons[0].unitButton->getTexture().top().y - unitPickLabel.getHeight() - 5,
		}
	);

	startGame = Globals::UI->createButton("startTangerine", "assets/ui/ig/gameStartBtn.png");
	startGame->setEnabled(false);
	startGame->getTexture().setColor({ 255, 255, 255, 100 }, true);
	startGame->setHighlightColor({ 171, 199, 209 });
	startGame->supplyCallback([this]()
		{
			this->onGameStart();
			MusicManager::fadeOutMusic();
			OverlayManager::fadeIn(3);

			Globals::timer->createTimer("tangerineStartDelay", 2.5f, [this]() {
				Globals::engine->createClass("Tangerine", new Tangerine(this->getGameParams()));
				Globals::engine->destroyClass("PreGame");
			}, 1);
		}
	);

	/* 1260 is the distance between the right side of the background texture and the world area */
	startGame->setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - (1260 / 2) - (startGame->getTexture().getWidth() / 2),
			Globals::engine->getDisplaySettings().wsHeight - startGame->getTexture().getHeight() - 10
		}
	);

	this->createTopBar();
}

void PreGame::createTopBar()
{
	topBar.setNewTexture("assets/ui/rect_base.png");
	topBar.setSize(Globals::engine->getDisplaySettings().wsWidth, 96);
	topBar.setY(32);
	topBar.setColor({ 12, 12, 12, 255 }, true);

	topBarScroll.setNewTexture("assets/ui/main_menu/topBar.png");
	topBarScroll.setScrollable(true);
	topBarScroll.reverseScroll(true);
	topBarScroll.setPosition(
		{
			0,
			topBar.getY() + 3
		}
	);

	topBarScroll.setColor({ 84, 198, 255, 255 }, true);

	topBarScrollLabel.createText("PREPARATION", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFontLarge"));
	topBarScrollLabel.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - topBarScrollLabel.getWidth() - 20,
			topBarScroll.getY() + (topBarScroll.getHeight() / 2) - (topBarScrollLabel.getHeight() / 2) + 5
		}
	);
}

void PreGame::setPickedUnit(const string unitId)
{
	this->gameParameters.pickedUnit = unitId;
	this->onPickedUnit(unitId);
}

void PreGame::setPickedWorldGen(const GameParams::WorldGeneration worldGen)
{
	this->gameParameters.pickedGeneration = worldGen;
}

void PreGame::onPickedUnit(const string& unitId)
{
	unitPickedArt.setNewTexture("assets/units/" + unitId + "/_art.png");
	unitPickedArt.setTextureFlip(true);
	unitPickedArt.setColor({ 255, 255, 255, 255 }, true);
	unitPickedArt.setPosition(
		{
			-140,
			Globals::engine->getDisplaySettings().wsHeight - unitPickedArt.getHeight() + 128
		}
	);
	unitPickedArt.setFade(TextureFadingState::FadeIn);

	unitPicked = Unit(unitId);
	unitPicked.setFlipped(true);
	unitPicked.setPosition(
		{
			this->unitPickButtons[0].unitButton->getTexture().getX() - 160,
			this->unitPickButtons[0].unitButton->getTexture().bottom().y - 96
		}
	);

	unitNameLabel.createText(UnitDefinitions::getParamsById(unitId).unitName, { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitNameLabel.setPosition(
		{
			unitPicked.texture().right(true) - 140,
			unitPicked.position().y - unitNameLabel.getHeight() + 170
		}
	);

	labelBar.setNewTexture("assets/ui/rect_base.png");
	labelBar.setColor({ 150, 150, 150, 225 }, true);
	labelBar.setSize(1100, 48);
	labelBar.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - labelBar.getWidth() - 10,
			unitNameLabel.getY() - (unitNameLabel.getHeight() / 2)
		}
	);

	this->createStats(unitId);
	this->createWorldOptions();
}

void PreGame::createStats(const string& unitId)
{
	UnitParams params = UnitDefinitions::getParamsById(unitId);

	// HP
	unitHPLabel.createText("MAX HP", { 25, 25, 25, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitHPLabel.setPosition({ unitNameLabel.getX(), unitNameLabel.bottom().y + unitHPLabel.getHeight() });
	unitHPAmount.createText(std::to_string(params.unitMaxHealth) + " / " + std::to_string(params.unitMaxHealth), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitHPAmount.setPosition(unitHPLabel.getX() + unitHPLabel.getWidth() + 128, unitHPLabel.getY() + (unitHPLabel.getHeight() / 2) - (unitHPAmount.getHeight() / 2));

	// ATTACK
	unitAtkLabel.createText("ATTACK", { 200, 110, 110, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitAtkLabel.setPosition({ unitHPLabel.getX(), unitHPLabel.bottom().y });
	unitAtkAmount.createText(std::to_string(params.unitStats[static_cast<int>(UnitParams::UnitStatistics::Attack)]), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitAtkAmount.setPosition({ unitHPAmount.getX(), unitHPAmount.bottom().y });

	// DEFENSE
	unitDefLabel.createText("DEFENSE", { 110, 255, 110, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitDefLabel.setPosition({ unitAtkLabel.getX(), unitAtkLabel.bottom().y });
	unitDefAmount.createText(std::to_string(params.unitStats[static_cast<int>(UnitParams::UnitStatistics::Defense)]), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitDefAmount.setPosition({ unitAtkAmount.getX(), unitAtkAmount.bottom().y });

	// EVASION
	unitEvaLabel.createText("EVASION", { 110, 110, 200, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitEvaLabel.setPosition({ unitDefLabel.getX(), unitDefLabel.bottom().y });
	unitEvaAmount.createText(std::to_string(params.unitStats[static_cast<int>(UnitParams::UnitStatistics::Evasion)]), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitEvaAmount.setPosition({ unitDefAmount.getX(), unitDefAmount.bottom().y });

	// RECOVERY
	unitRecLabel.createText("RECOVERY", { 255, 255, 140, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitRecLabel.setPosition({ unitEvaLabel.getX(), unitEvaLabel.bottom().y });
	unitRecAmount.createText(std::to_string(params.unitStats[static_cast<int>(UnitParams::UnitStatistics::Recovery)]), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitRecAmount.setPosition({ unitEvaAmount.getX(), unitEvaAmount.bottom().y });

	// POWER
	unitPwrLabel.createText("SKILL POWER", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitPwrLabel.setPosition({ unitRecLabel.getX(), unitRecLabel.bottom().y });
	unitPwrEffect.setFixedSize(250);
	unitPwrEffect.setAnimationSpeed(80);
	unitPwrEffect.setNewTexture("assets/effects/lstrike.png");
	unitPwrEffect.setPosition(unitPwrLabel.getX() + (unitPwrLabel.getWidth() / 2) - (unitPwrEffect.getSheetSize() / 2), unitPwrLabel.getY() + (unitPwrLabel.getHeight() / 2) - (unitPwrEffect.getHeight() / 2));
	unitPwrEffect.setColor({ 174, 0, 209, 255 }, true);
	unitPwrAmount.createText(std::to_string(params.unitStats[static_cast<int>(UnitParams::UnitStatistics::SkillPowerStart)]) + " / " + std::to_string(params.unitStats[static_cast<int>(UnitParams::UnitStatistics::SkillPowerMax)]), { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitPwrAmount.setPosition({ unitRecAmount.getX(), unitRecAmount.bottom().y });

	this->createSkills(params);
}

void PreGame::createSkills(const UnitParams& params)
{
	this->unitSkills.clear();

	unitSkillLabel.createText("Skills", { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitSkillLabel.setPosition(
		{
			unitHPAmount.getPosition().x + unitHPAmount.getWidth() + 110,
			unitNameLabel.getY()
		}
	);

	for (size_t i = 0; i < params.unitSkills.size(); ++i)
	{
		Skill skillDef;
		skillDef.skillName = params.unitSkills[i].skillName;
		skillDef.skillDesc = params.unitSkills[i].skillDescription;
		skillDef.skillIcon = params.unitSkills[i].skillIconPath;
		skillDef.skillCost = params.unitSkills[i].skillCost;

		shared_ptr<LTexture> textureSkillName = shared_ptr<LTexture>(new LTexture);
		textureSkillName->createText(skillDef.skillName, { 25, 25, 25, 255 });
		shared_ptr<LTexture> textureSkillDesc = shared_ptr<LTexture>(new LTexture);
		textureSkillDesc->createText(skillDef.skillDesc, { 60, 60, 60, 255 }, 402, Globals::resources->getFont("defaultFontSmall"));
		shared_ptr<LTexture> textureSkillIcon = shared_ptr<LTexture>(new LTexture(skillDef.skillIcon));
		shared_ptr<LTexture> textureSkillCostIcon = shared_ptr<LTexture>(new LTexture("assets/ui/stats/pwr.png"));
		textureSkillCostIcon->setColor({ 0, 0, 0, 255 }, true);
		shared_ptr<LTexture> textureSkillCost = shared_ptr<LTexture>(new LTexture);
		textureSkillCost->createText(std::to_string(skillDef.skillCost), { 25, 25, 25, 255 });

		/* Base pos on the skill icon */
		textureSkillIcon->setPosition(
			{
				unitSkillLabel.getX(),
				unitSkillLabel.bottom().y + (16 * 1 + static_cast<int>(i)) + (32 * static_cast<int>(i)) + ((textureSkillIcon->getHeight() * static_cast<int>(i)))
			}
		);

		textureSkillName->setPosition(
			{
				textureSkillIcon->getX() + textureSkillIcon->getWidth() + 16,
				textureSkillIcon->top().y + 8
			}
		);

		textureSkillCostIcon->setPosition(
			{
				textureSkillName->getX() + textureSkillName->getWidth() + 16,
				textureSkillName->getY()
			}
		);

		textureSkillCost->setPosition(
			{
				textureSkillCostIcon->getX() + textureSkillCostIcon->getWidth() + 16,
				textureSkillName->getY()
			}
		);

		textureSkillDesc->setPosition(
			{
				textureSkillName->getX(),
				textureSkillName->bottom().y + 5
			}
		);

		skillDef.skillTextures.push_back(textureSkillName);
		skillDef.skillTextures.push_back(textureSkillDesc);
		skillDef.skillTextures.push_back(textureSkillIcon);
		skillDef.skillTextures.push_back(textureSkillCostIcon);
		skillDef.skillTextures.push_back(textureSkillCost);

		this->unitSkills.push_back(skillDef);
	}
}

void PreGame::createWorldOptions()
{
	worldGenerationLabel.createText("World Generation", { 15, 15, 15, 255 }, 0, Globals::resources->getFont("defaultFont32"));
	worldGenerationLabel.setPosition(
		{ 750, 730 }
	);

	worldGenRandom = Globals::UI->createButton("worldGenRandom", "assets/ui/ig/world_gen_total_random.png");
	worldGenFairRandom = Globals::UI->createButton("worldGenFairRandom", "assets/ui/ig/world_gen_fair_random.png");
	worldGenBattlefield = Globals::UI->createButton("worldGenBattlefield", "assets/ui/ig/world_gen_battlefield.png");

	worldGenRandom->setPosition(
		{
			worldGenerationLabel.getX() - 16,
			worldGenerationLabel.bottom().y + 16
		}
	);

	worldGenFairRandom->setPosition(
		{
			worldGenRandom->getX() + worldGenRandom->getTexture().getWidth() + 48,
			worldGenRandom->getY()
		}
	);

	worldGenBattlefield->setPosition(
		{
			worldGenFairRandom->getX() + worldGenFairRandom->getTexture().getWidth() + 48,
			worldGenRandom->getY()
		}
	);

	worldGenRandom->supplyCallback([this]() { this->setPickedWorldGen(GameParams::WorldGeneration::TotalRandom); });
	worldGenFairRandom->supplyCallback([this]() { this->setPickedWorldGen(GameParams::WorldGeneration::FairRandom); });
	worldGenBattlefield->supplyCallback([this]() { this->setPickedWorldGen(GameParams::WorldGeneration::Battlefield); });

	this->worldGenPickButtons = {
		{ GameParams::WorldGeneration::TotalRandom, worldGenRandom },
		{ GameParams::WorldGeneration::FairRandom, worldGenFairRandom },
		{ GameParams::WorldGeneration::Battlefield, worldGenBattlefield }
	};

	for (auto& worldBtn : this->worldGenPickButtons)
	{
		worldBtn.worldGenButton->setHighlightColor({ 255, 255, 255, 255 });
	}
}

void PreGame::onGameStart()
{
	this->gameLaunched = true;

	for (size_t i = 0; i < this->unitPickButtons.size(); ++i)
	{
		this->unitPickButtons[i].unitButton->setEnabled(false);
	}

	for (size_t i = 0; i < this->worldGenPickButtons.size(); ++i)
	{
		this->worldGenPickButtons[i].worldGenButton->setEnabled(false);
	}

	startGame->getTexture().setColor({ 255, 255, 255, 100 }, true);
	startGame->setEnabled(false);
}

GameParams PreGame::getGameParams() const
{
	return this->gameParameters;
}

void PreGame::update(const float dt)
{
	/* Handle the button being disabled on the active unit, as well the color of the button */
	if (this->gameParameters.pickedUnit != "" && !this->gameLaunched)
	{
		for (const auto& unitPickBtn : this->unitPickButtons)
		{
			if (unitPickBtn.unitIdentifier == this->gameParameters.pickedUnit)
			{
				unitPickBtn.unitButton->getTexture().setColor({ 255, 255, 255, 255 }, true);
				unitPickBtn.unitButton->setEnabled(false);
			}
			else
			{
				unitPickBtn.unitButton->getTexture().setColor({ 125, 125, 125, 255 }, true);
				unitPickBtn.unitButton->setEnabled(true);
			}
		}

		for (const auto& worldGenBtn : this->worldGenPickButtons)
		{
			if (worldGenBtn.worldGeneration == this->gameParameters.pickedGeneration)
			{
				worldGenBtn.worldGenButton->getTexture().setColor({ 255, 255, 255, 255 }, true);
				worldGenBtn.worldGenButton->setEnabled(false);
			}
			else
			{
				worldGenBtn.worldGenButton->getTexture().setColor({ 255, 255, 255, 125 }, true);
				worldGenBtn.worldGenButton->setEnabled(true);
			}
		}

		startGame->setEnabled(true);
		startGame->getTexture().setColor({ 255, 255, 255, 255 }, true);
	}

	/* World, bg & unit art */
	selectedWorld.render();
	unitPickedArt.render();
	pregameBg.render();

	/* Top bar */
	topBar.render();
	topBarScroll.render();
	topBarScrollLabel.render();

	/* Label bar */
	labelBar.render();

	/* Labels */
	unitPickLabel.render();
	unitNameLabel.render();
	unitSkillLabel.render();
	worldGenerationLabel.render();

	/* Unit btns */
	for (const auto& unitPickBtn : this->unitPickButtons)
	{
		unitPickBtn.unitButton->render();
	}

	/* Unit Sprite */
	unitPicked.render(Globals::engine->getCamera());

	/* Unit Stats */
	unitHPLabel.render();
	unitHPAmount.render();
	unitAtkLabel.render();
	unitAtkAmount.render();
	unitDefLabel.render();
	unitDefAmount.render();
	unitEvaLabel.render();
	unitEvaAmount.render();
	unitRecLabel.render();
	unitRecAmount.render();
	unitPwrEffect.render();
	unitPwrLabel.render();
	unitPwrAmount.render();

	/* Unit Skills */
	for (auto& unitSkill : this->unitSkills)
	{
		for (auto& unitSkillTexture : unitSkill.skillTextures)
		{
			unitSkillTexture->render();
		}
	}

	/* Buttons */
	startGame->render();

	for (const auto& worldPickBtn : this->worldGenPickButtons)
	{
		worldPickBtn.worldGenButton->render();
	}
}