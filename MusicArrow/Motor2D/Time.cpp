#include "Time.h"

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance() {


	if (sInstance == NULL)
		sInstance = new Timer();

	return sInstance;
}

void Timer::Release() {

	delete sInstance;
	sInstance = NULL;

}

Timer::Timer(){

	Reset();
	mTimeScale = 1.0f;

}
Timer::~Timer() {


}

void Timer::Reset() {

	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDelataTime = 0.0f;

}

float Timer::DeltaTime() {

	return mDelataTime;
}

void Timer::TimeScale(float t) {

	mTimeScale = t;

}

float Timer::TimeScale() {

	return mTimeScale;
}

bool Timer::Update(float dt) {

	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDelataTime = mElapsedTicks * 0.001f;
	return true;
}

uint32 Timer::Read() const
{
	return SDL_GetTicks() - mStartTicks;//started_at;
}


float Timer::ReadSec() const
{
	return float(SDL_GetTicks() - mStartTicks) / 1000.0f;//started_at) / 1000.0f;
}