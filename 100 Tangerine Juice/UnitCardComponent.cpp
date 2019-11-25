#include "UnitCardComponent.h"
#include "Globals.h"

UnitCardComponent::UnitCardComponent(const UnitParams params)
{
	this->unitParams = params;
}

void UnitCardComponent::init()
{
	// BACKGROUND SEMI OPAQUE
	unitCardBg.setNewTexture("assets/ui/rect_base.png");
	unitCardBg.setColor({ 0, 0, 0, 175 }, true);
	unitCardBg.setSize(Globals::engine->getDisplaySettings().wsWidth - 500, 900);
	unitCardBg.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - unitCardBg.getWidth(),
			LilacClasses::MainMenu->getInformationBar().bottom().y
		}
	);

	// UNIT ARTWORK
	unitArt.setNewTexture("assets/units/" + this->unitParams.unitId + "/_art.png");
	unitArt.setColor({ 255, 255, 255, 50 }, true);
	unitArt.setPosition(
		{
			unitCardBg.getX() + unitCardBg.getWidth() - unitArt.getWidth() + 230,
			unitCardBg.getY() + unitCardBg.getHeight() - unitArt.getHeight() + 168
		}
	);
	unitArt.setFade(TextureFadingState::FadeIn);

	// UNIT SPRITE
	unit = Unit(this->unitParams.unitId, this->unitParams.unitDefaultPose);
	unit.texture().setFade(TextureFadingState::FadeIn);
	unit.setPosition(
		{
			unitCardBg.getX(),
			unitCardBg.getY()
		}
	);
	unit.setFlipped(true);

	// STATS TITLE
	unitStatsTitle.createText("Stats of " + this->unitParams.unitName, { 225, 225, 225, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	unitStatsTitle.setPosition({ unit.texture().top().x + 64, unit.texture().top().y + 32 });

	// DESCRIPTION
	unitDescriptionLabel.createText(this->unitParams.unitDesc, { 225, 225, 225, 255 }, Globals::engine->getDisplaySettings().wsWidth - 500 - unit.texture().getSheetSize());
	unitDescriptionLabel.setPosition(unit.texture().right(true) - 32, unit.texture().top().y + 154);
	unitDescriptionLabel.setFade(TextureFadingState::FadeIn);

	// HP
	unitHPLabel.createText("MAX HP", { 180, 180, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitHPLabel.setPosition({ unitDescriptionLabel.getX(), unit.texture().bottom().y - unitHPLabel.getHeight() - 224 });
	unitHPAmount.createText(std::to_string(this->unitParams.unitMaxHealth) + " / " + std::to_string(this->unitParams.unitMaxHealth), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitHPAmount.setPosition(unitHPLabel.getX() + unitHPLabel.getWidth() + 128, unitHPLabel.getY() + (unitHPLabel.getHeight() / 2) - (unitHPAmount.getHeight() / 2));

	// ATTACK
	unitAtkLabel.createText("ATTACK", { 255, 180, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitAtkLabel.setPosition({ unitHPLabel.getX(), unitHPLabel.bottom().y });
	unitAtkAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Attack)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitAtkAmount.setPosition({ unitHPAmount.getX(), unitHPAmount.bottom().y });

	// DEFENSE
	unitDefLabel.createText("DEFENSE", { 180, 255, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitDefLabel.setPosition({ unitAtkLabel.getX(), unitAtkLabel.bottom().y });
	unitDefAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Defense)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitDefAmount.setPosition({ unitAtkAmount.getX(), unitAtkAmount.bottom().y });

	// EVASION
	unitEvaLabel.createText("EVASION", { 180, 180, 255, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitEvaLabel.setPosition({ unitDefLabel.getX(), unitDefLabel.bottom().y });
	unitEvaAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Evasion)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitEvaAmount.setPosition({ unitDefAmount.getX(), unitDefAmount.bottom().y });

	// RECOVERY
	unitRecLabel.createText("RECOVERY", { 255, 255, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitRecLabel.setPosition({ unitEvaLabel.getX(), unitEvaLabel.bottom().y });
	unitRecAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Recovery)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitRecAmount.setPosition({ unitEvaAmount.getX(), unitEvaAmount.bottom().y });

	// POWER
	unitPwrLabel.createText("SKILL POWER", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitPwrLabel.setPosition({ unitRecLabel.getX(), unitRecLabel.bottom().y });
	unitPwrEffect.setFixedSize(250);
	unitPwrEffect.setAnimationSpeed(80);
	unitPwrEffect.setNewTexture("assets/effects/lstrike.png");
	unitPwrEffect.setPosition(unitPwrLabel.getX() + (unitPwrLabel.getWidth() / 2) - (unitPwrEffect.getSheetSize() / 2), unitPwrLabel.getY() + (unitPwrLabel.getHeight() / 2) - (unitPwrEffect.getHeight() / 2));
	unitPwrEffect.setColor({ 174, 0, 209, 255 }, true);
	unitPwrAmount.createText("Start: " + std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::SkillPowerStart)]) + " - Max: " + std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::SkillPowerMax)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont27"));
	unitPwrAmount.setPosition({ unitRecAmount.getX(), unitRecAmount.bottom().y });

	// SKILL TITLE
	unitSkillTitle.createText("Skills (W.I.P.)", { 225, 225, 225, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	unitSkillTitle.setPosition(unitStatsTitle.getX(), unit.texture().bottom().y - 64);
}

UnitParams UnitCardComponent::getParams()
{
	return this->unitParams;
}

void UnitCardComponent::update(const float dt)
{
	unitCardBg.render();
	unitArt.render();
	unit.render(Globals::engine->getCamera());
	unitDescriptionLabel.render();

	/* Stats */
	unitStatsTitle.render();
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

	/* Skills */
	unitSkillTitle.render();

	/* Effects on LTextures */

	if (unitArt.getX() > unitCardBg.getX() + unitCardBg.getWidth() - unitArt.getWidth() + 196)
	{
		unitArt.setX(unitArt.getX() - 2);
	}
}