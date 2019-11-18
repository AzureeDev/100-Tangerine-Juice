#pragma once
#include <SDL.h>

class LTimer
{
private:
	float timer;
	Uint32 startTicks;
	Uint32 pausedTicks;
	bool paused;
	bool started;

public:
	LTimer();

	void start(const bool force = false);
	void startTick();
	void reset();
	void stop();
	void pause();
	void unpause();
	void update(const float dt);

	float getSeconds();

	bool isStarted();
	bool isPaused();
	Uint32 getTicks();
};
