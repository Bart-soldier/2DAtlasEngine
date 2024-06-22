#pragma once

#include <SDL.h>

namespace AE
{
	class Timer
	{
	public:
		Timer();
		~Timer();

        void Start();
        void Reset();
        void Pause();
        void Resume();

        Uint32 GetTicks();

        bool IsStarted();
        bool IsPaused();

    private:
        Uint32 _startTicks;
        Uint32 _pausedTicks;

        bool _paused;
        bool _started;
	};
}