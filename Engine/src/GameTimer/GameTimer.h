#pragma once

class GameTimer
{
public:
	GameTimer();

	float TotalTime()const; // in seconds
	float DeltaTime()const; // in seconds

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.

private:
	double mSecondsPerCount;
	double mDeltaTime;

	unsigned long long mBaseTime;
	unsigned long long mPausedTime;
	unsigned long long mStopTime;
	unsigned long long mPrevTime;
	unsigned long long mCurrTime;

	bool mStopped;
};