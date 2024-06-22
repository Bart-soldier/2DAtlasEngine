#include "../inc/Timer.hpp"

namespace AE
{
	Timer::Timer()
	{
		Reset();
	}

	Timer::~Timer()
	{
	}

	void Timer::Start()
	{
		_started = true;
		_paused = false;

		_startTicks = SDL_GetTicks();
		_pausedTicks = 0;
	}

	void Timer::Reset()
	{
		_paused = false;
		_started = false;

		_startTicks = 0;
		_pausedTicks = 0;
	}

	void Timer::Pause()
	{
		if (_started && !_paused)
		{
			_paused = true;

			_pausedTicks = SDL_GetTicks() - _startTicks;
			_startTicks = 0;
		}
	}

	void Timer::Resume()
	{
		if (_started && _paused)
		{
			_paused = false;

			_startTicks = SDL_GetTicks() - _pausedTicks;
			_pausedTicks = 0;
		}
	}

	Uint32 Timer::GetTicks()
	{
		return _started ? (_paused ? _pausedTicks : SDL_GetTicks() - _startTicks) : 0;
	}

	bool Timer::IsStarted()
	{
		return _started;
	}

	bool Timer::IsPaused()
	{
		return _started && _paused;
	}
}