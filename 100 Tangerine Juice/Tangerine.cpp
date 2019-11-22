#include "Tangerine.h"
#include "Globals.h"
#include "MusicManager.h"
#include "OverlayManager.h"

float timer = 0.0f;

Tangerine::Tangerine()
{
	LilacClasses::Tangerine = this;
}

Tangerine::~Tangerine()
{
	Globals::engine->setActiveCameraUnit(nullptr);
}

void Tangerine::init()
{
	OverlayManager::fadeOut(3);
	MusicManager::playMusic("assets/musics/shine.mp3");

	test = PlayerUnit("sora_m");
	test.setAnimation("fwd");
	test.placeMiddleScreen();
	test2 = PlayerUnit("suguri");
	test2.setPosition({ 3000, 500 });
	test.setFlipped(true);
	test.setDash(true, 4);
	test.setActiveUnit();
	world.setNewWorld("assets/worlds/ml_sky.png");
	world.setScrollMultiplier(6);
}

void Tangerine::update(const float dt)
{
	timer += dt;
	world.render();
	test.render(Globals::engine->getCamera());
	test2.render(Globals::engine->getCamera());

	if (timer > 20)
	{
		test2.setActiveUnit();
	}
}