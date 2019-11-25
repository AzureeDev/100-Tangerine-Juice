#pragma once
#include <vector>
#include <string>
#include <functional>
#include "LTimer.h"
#include "TimerCallbacks.h"

using std::string, std::vector, std::function;

/*
	ExecutionRepeat on 0 means that it will run infinitely, until you remove it yourself.
	Putting 3, however, will run the callback 3 times, then stop.
*/
struct TimerParams
{
	string timerName;
	float interval;
	LTimer instance;
	function<void()> callback = NULL;
	int executionRepeat = 0;
	int totalCurrentRepeats = 0;
};

class TimerManager
{
private:
	vector<TimerParams> timers = {};

public:
	void createTimer(const string timerID, const float interval, const function<void()> callback, const int executionRepeat = 0);
	void removeTimer(const string timerID);
	void removeAll();
	void update(const float dt);
};
