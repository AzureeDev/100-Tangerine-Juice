#include "LTimer.h"

/*
	LTimer - Custom Timer
*/

LTimer::LTimer()
{
	timer = 0;
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void LTimer::start(const bool force)
{
	if (!started || force)
	{
		started = true;
		paused = false;

		startTicks = static_cast<Uint32>(timer);
		pausedTicks = 0;
	}
}

void LTimer::startTick()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void LTimer::reset()
{
	timer = 0;
	startTicks = 0;
	pausedTicks = 0;
	started = false;
	paused = false;
}

void LTimer::stop()
{
	started = false;
	paused = false;
	timer = 0;
	startTicks = 0;
	pausedTicks = 0;
}

void LTimer::pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTicks = static_cast<Uint32>(timer) - startTicks;
		startTicks = 0;
	}
}

void LTimer::unpause()
{
	if (started && paused)
	{
		paused = false;
		startTicks = static_cast<Uint32>(timer) - pausedTicks;
		pausedTicks = 0;
	}
}

void LTimer::update(const float dt)
{
	if (started && !paused)
	{
		timer += dt;
	}
}

float LTimer::getSeconds()
{
	float time = 0;

	if (started)
	{
		if (paused)
		{
			time = static_cast<float>(pausedTicks);
		}
		else
		{
			time = timer;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	return started;
}

bool LTimer::isPaused()
{
	return started && paused;
}

Uint32 LTimer::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}