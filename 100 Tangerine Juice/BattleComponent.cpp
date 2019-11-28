#include "BattleComponent.h"
#include "Globals.h"

BattleComponent::BattleComponent(shared_ptr<PlayerUnit> attacker, shared_ptr<PlayerUnit> defender)
{
	this->battleAttacker = attacker.get();
	this->battleDefender = defender.get();
}

BattleComponent::~BattleComponent()
{
	this->battleAttacker = nullptr;
	this->battleDefender = nullptr;
}

void BattleComponent::init()
{
	SDL_Log("Initiate battle between %s and %s", battleAttacker->identifier().c_str(), battleDefender->identifier().c_str());

	this->componentBgContour.setNewTexture("assets/ui/rect_base.png");
	this->componentBgContour.setColor({ 10, 10, 10, 255 }, true);
	this->componentBgContour.setSize(Globals::engine->getDisplaySettings().wsWidth, 310);
	this->componentBgContour.placeMiddleScreen();
	this->componentBg.setNewTexture("assets/ui/rect_gradient_base.png");
	this->componentBg.setColor({ 200, 0, 0, 255 }, true);
	this->componentBg.setSize(Globals::engine->getDisplaySettings().wsWidth, 300);
	this->componentBg.placeMiddleScreen();

	SDL_Log("Attacker is an AI? %s", this->battleAttacker->isAI() ? "TRUE" : "FALSE");
	SDL_Log("Defender is an AI? %s", this->battleDefender->isAI() ? "TRUE" : "FALSE");

	this->battleAttackerUnit = Unit(this->battleAttacker->identifier());
	this->battleDefenderUnit = Unit(this->battleDefender->identifier());

	this->battleAttackerUnit.placeMiddleScreen();
	this->battleAttackerUnit.setFlipped(true);
	this->battleAttackerUnit.setX(this->battleAttackerUnit.texture().getX() - 128 * 3);

	this->battleDefenderUnit.placeMiddleScreen();
	this->battleDefenderUnit.setX(this->battleDefenderUnit.texture().getX() + 128 * 3);
}

void BattleComponent::battleEnded()
{
}

void BattleComponent::update(const float dt)
{
	this->componentBgContour.render();
	this->componentBg.render();
	this->battleAttackerUnit.render({});
	this->battleDefenderUnit.render({});
}
