#ifndef _TIME_H
#define _TIME_H

#include "SDL/include/SDL.h"
#include "j1Module.h"

class Timer : public j1Module {

private:

	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDelataTime;
	float mTimeScale;

	uint32	started_at;

public:

	static Timer* Instance();
	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float t);
	float TimeScale();

	bool Update(float dt);

	uint32 Read() const;
	float ReadSec() const;

	Timer();
	~Timer();



};







#endif