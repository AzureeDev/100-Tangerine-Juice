#include "DiceThrowComponent.h"
#include "Globals.h"
#include "SFXManager.h"
#include "Utils.h"

DiceThrowComponent::DiceThrowComponent(const bool isAI, const DiceComponentType type)
{
	this->componentType = type;
	this->componentBgContour.setNewTexture("assets/ui/rect_base.png");
	this->componentBgContour.setColor({ 10, 10, 10, 255 }, true);
	this->componentBgContour.setSize(Globals::engine->getDisplaySettings().wsWidth, 310);
	this->componentBg.setNewTexture("assets/ui/rect_gradient_base.png");
	this->componentUnit = Unit(Globals::gameManager->getCurrentTurnUnit()->identifier());
	this->componentUnit.setFlipped(true);

	SDL_Color bgColor = { 255, 255, 255, 255 };
	string bgText = "";

	switch (type)
	{
	case DiceComponentType::Movement:
		bgColor = { 52, 235, 64, 255 };
		bgText = "MOVEMENT  MOVEMENT  MOVEMENT";
		break;

	case DiceComponentType::Bonus:
		bgColor = { 255, 235, 0, 255 };
		bgText = "BONUS  BONUS  BONUS";
		break;

	case DiceComponentType::Drop:
		bgColor = { 52, 146, 235, 255 };
		bgText = "DROP  DROP  DROP";
		break;
	}

	this->componentBg.setColor(bgColor, true);
	this->componentBg.setSize(Globals::engine->getDisplaySettings().wsWidth, 300);

	this->componentBgText.createText(bgText, { 255, 255, 255, 50 }, 0, Globals::resources->getFont("bleachFontLarge"));
	this->componentBgText.setScrollable(true, 5);

	this->componentBg.placeMiddleScreen();
	this->componentBgContour.placeMiddleScreen();

	this->componentUnit.placeMiddleScreen();
	this->componentUnit.setX(this->componentUnit.position().x - 256);

	this->componentDiceTexture.placeMiddleScreen();
	this->componentDiceTexture.setX(this->componentDiceTexture.getX() + 64);

	this->componentBgText.setPosition(
		{
			0,
			this->componentBg.getY() + 10
		}
	);

	this->componentButton = Globals::UI->createButton("diceThrowComponentBtn");
	this->componentButton->getTexture().setSize(Globals::engine->getDisplaySettings().wsWidth, Globals::engine->getDisplaySettings().wsHeight);
	this->componentButton->setAllowSound(false);
	this->componentButton->supplyCallback([this]() { this->onPress(); });

	if (Globals::gameManager->getLocalUnit()->identifier() != Globals::gameManager->getCurrentTurnUnit()->identifier())
	{
		this->componentButton->setEnabled(false);
	}

	Globals::timer->createTimer("diceTextureRoll", 0.05f, [this]() {
		vector<string> diceTextures = {
			"assets/dice/1.png",
			"assets/dice/2.png",
			"assets/dice/3.png",
			"assets/dice/4.png",
			"assets/dice/5.png",
			"assets/dice/6.png",
		};

		this->componentDiceTexture.setNewTexture(diceTextures[Utils::randBetween(0, 5)]);
	});

	if (isAI)
	{
		Globals::timer->createTimer("AiAutoClick", 0.1f, [this]() {
			this->onPress();
		}, 1);
	}
}

DiceThrowComponent::~DiceThrowComponent()
{
	Globals::UI->destroyButton("diceThrowComponentBtn");
}

void DiceThrowComponent::init()
{
}

void DiceThrowComponent::onPress()
{
	Globals::timer->removeTimer("diceTextureRoll");
	this->componentButton->setEnabled(false);

	SFXManager::playSFX("btn_clicked");

	const int diceRoll = Utils::randBetween(1, 6);
	this->componentDiceTexture.setNewTexture("assets/dice/" + std::to_string(diceRoll) + ".png");

	if (this->componentType == DiceComponentType::Movement)
	{
		Globals::timer->createTimer("diceThrowCmpntOnPress", 0.5f, [diceRoll]() {
			Globals::gameManager->getCurrentTurnUnit()->movement(diceRoll);
			Globals::engine->destroyClass("DiceThrowComponent");
		}, 1);
	}
}

void DiceThrowComponent::update(const float dt)
{
	this->componentBgContour.render();
	this->componentBg.render();
	this->componentBgText.render();
	this->componentUnit.render(Globals::engine->getCamera());
	this->componentDiceTexture.render();
	this->componentButton->render();
}