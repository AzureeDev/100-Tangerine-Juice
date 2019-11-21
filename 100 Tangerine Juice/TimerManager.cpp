#include "TimerManager.h"

void TimerManager::createTimer(const string timerID, const float interval, const function<void()> callback, const int executionRepeat)
{
	for (const auto& data : this->timers)
	{
		if (data.timerName == timerID)
		{
			return;
		}
	}

	this->timers.push_back(
		{
			timerID,
			interval,
			LTimer(),
			callback,
			executionRepeat,
			0
		}
	);
}

void TimerManager::update(const float dt)
{
	if (this->timers.empty())
	{
		return;
	}

	for (size_t i = 0; i < this->timers.size(); ++i)
	{
		TimerParams *params = &this->timers[i];

		if (params->executionRepeat > 0)
		{
			if (params->totalCurrentRepeats >= params->executionRepeat)
			{
				this->timers.erase(this->timers.begin() + i);
				continue;
			}
		}

		if (!params->instance.isStarted())
		{
			params->instance.start();
		}

		if (params->instance.getSeconds() >= params->interval)
		{
			if (params->callback != NULL)
			{
				params->instance.reset();
				params->callback();
			}

			if (params->executionRepeat > 0)
			{
				params->totalCurrentRepeats++;
			}
		}

		params->instance.update(dt);
	}
}
