#include <SDL.h>
#include "TimerCallbacks.h"

void TimerCallbacks::clbkTest()
{
	SDL_Log("Hello world! This is executed every 5 seconds.");
}

void TimerCallbacks::clbkTest2()
{
	SDL_Log("This one, every seconds, 10 times.");

}
