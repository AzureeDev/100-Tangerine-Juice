#include "UnitCardComponent.h"
#include "Globals.h"

UnitCardComponent::UnitCardComponent(const UnitParams params)
{
	this->unitParams = params;
}

void UnitCardComponent::init()
{
	unitCardBg.setNewTexture("assets/ui/rect_base.png");
	unitCardBg.setColor({ 0, 0, 0, 50 }, true);
	unitCardBg.setSize(Globals::engine->getDisplaySettings().wsWidth - 500, 900);
	unitCardBg.setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - unitCardBg.getWidth(),
			LilacClasses::MainMenu->getInformationBar().bottom().y
		}
	);
	unitCardBg.setFade(TextureFadingState::FadeIn);

	unit = Unit(this->unitParams.unitId, this->unitParams.unitDefaultPose);
	unit.texture().setFade(TextureFadingState::FadeIn);
	unit.setPosition(
		{
			unitCardBg.getX(),
			unitCardBg.getY()
		}
	);
	unit.setFlipped(true);

	unitDescriptionLabel.createText(this->unitParams.unitDesc, { 225, 225, 225, 255 }, Globals::engine->getDisplaySettings().wsWidth - 500 - unit.texture().getSheetSize());
	unitDescriptionLabel.setPosition(unit.texture().right(true) - 168, unit.texture().top().y + 154);
	unitDescriptionLabel.setFade(TextureFadingState::FadeIn);
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
}