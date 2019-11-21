#include "UnitCardComponent.h"
#include "Globals.h"

UnitCardComponent::UnitCardComponent(const UnitParams params)
{
	this->unitParams = params;
}

void UnitCardComponent::init()
{
	unitCardBg.setNewTexture("assets/ui/rect_base.png");
	unitCardBg.setColor({ 0, 0, 0, 125 }, true);
	unitCardBg.setSize(Globals::engine->getDisplaySettings().wsWidth - 500, 900);
	unitCardBg.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - unitCardBg.getWidth(),
			LilacClasses::MainMenu->getInformationBar().bottom().y
		}
	);

	unit = Unit(this->unitParams.unitId, this->unitParams.unitDefaultPose);
	unit.texture().setFade(TextureFadingState::FadeIn);
	unit.setPosition(
		{
			unitCardBg.getX(),
			unitCardBg.getY()
		}
	);
	unit.setFlipped(true);

	unitStatsTitle.createText("Stats of " + this->unitParams.unitName, { 225, 225, 225, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	unitStatsTitle.setPosition({ unit.texture().top().x + 64, unit.texture().top().y + 32 });

	unitDescriptionLabel.createText(this->unitParams.unitDesc, { 225, 225, 225, 255 }, Globals::engine->getDisplaySettings().wsWidth - 500 - unit.texture().getSheetSize());
	unitDescriptionLabel.setPosition(unit.texture().right(true) - 32, unit.texture().top().y + 154);
	unitDescriptionLabel.setFade(TextureFadingState::FadeIn);

	// HP
	unitHPLabel.createText("MAX HP: ", { 180, 180, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitHPLabel.setPosition({ unitDescriptionLabel.getX(), unit.texture().bottom().y - unitHPLabel.getHeight() - 224 });
	unitHPAmount.createText(std::to_string(this->unitParams.unitMaxHealth) + " / " + std::to_string(this->unitParams.unitMaxHealth), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont28"));
	unitHPAmount.setPosition(unitHPLabel.getX() + unitHPLabel.getWidth() + 128, unitHPLabel.getY() + (unitHPLabel.getHeight() / 2) - (unitHPAmount.getHeight() / 2));
	
	// ATTACK
	unitAtkLabel.createText("ATTACK", { 255, 180, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitAtkLabel.setPosition({ unitHPLabel.getX(), unitHPLabel.bottom().y });
	unitAtkAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Attack)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont28"));
	unitAtkAmount.setPosition({ unitHPAmount.getX(), unitHPAmount.bottom().y });
	
	// DEFENSE
	unitDefLabel.createText("DEFENSE", { 180, 255, 180, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitDefLabel.setPosition({ unitAtkLabel.getX(), unitAtkLabel.bottom().y });
	unitDefAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Defense)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont28"));
	unitDefAmount.setPosition({ unitAtkAmount.getX(), unitAtkAmount.bottom().y });

	// EVASION
	unitEvaLabel.createText("EVASION", { 180, 180, 255, 255 }, 0, Globals::resources->getFont("bleachFont"));
	unitEvaLabel.setPosition({ unitDefLabel.getX(), unitDefLabel.bottom().y });
	unitEvaAmount.createText(std::to_string(this->unitParams.unitStats[static_cast<int>(UnitParams::UnitStatistics::Evasion)]), { 225, 225, 255, 255 }, 0, Globals::resources->getFont("defaultFont28"));
	unitEvaAmount.setPosition({ unitDefAmount.getX(), unitDefAmount.bottom().y });

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
	unit.render();
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

	/* Skills */
	unitSkillTitle.render();
}