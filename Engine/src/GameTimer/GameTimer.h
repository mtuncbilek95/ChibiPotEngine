#pragma once

class GameTimer
{
public:
	GameTimer();

	float TotalTime() const;
	float DeltaTime() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double m_secondsPerCount;
	double m_deltaTime;

	unsigned long long m_baseTime;
	unsigned long long m_pausedTime;
	unsigned long long m_stopTime;
	unsigned long long m_prevTime;
	unsigned long long m_currTime;

	bool mStopped;
};