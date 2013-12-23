#include "timer.h"

#if defined(_MSC_VER)
#include <sdl/SDL.h>
#endif

Timer::Timer()
    : mStartTicks(0), mPausedTicks(0), mStarted(false), mPaused(false)
{
}
void Timer::start() {
    mStarted = true;
    mPaused  = false;
    mStartTicks = SDL_GetTicks();
}
void Timer::stop() {
    mStarted = false;
    mPaused  = false;
}
void Timer::pause() {
    if (mStarted && !mPaused) {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
    }
}
void Timer::unpause() {
    if (mPaused) {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}
int Timer::restart() {
    int elapsedTicks = ticks();
    start();
    return elapsedTicks;
}
int Timer::ticks() const {
    if (mStarted) {
        if (mPaused)
            return mPausedTicks;
        else
            return SDL_GetTicks() - mStartTicks;
    }
    return 0;
}
bool Timer::started() const {
    return mStarted;
}
bool Timer::paused() const {
    return mPaused;
}
