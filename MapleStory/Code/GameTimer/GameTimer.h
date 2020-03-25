#pragma once
#include "../Macro.h"
constexpr int MAX_SAMPLE_COUNT = 50;

class GameTimer
{
	SINGLE_TONE(GameTimer)

	void Tick(float);
	void Start();
	void Stop();
	void Reset();

	unsigned int GetFrameRate()	const { return m_nCurrentFrameRate; }
	float GetElapsedTime() const { return m_ElapsedTime; }
	float GetTotalTime();

private:
	double							m_TimeScale;						
	float								m_ElapsedTime;		

	__int64							m_nBasePerformanceCounter;
	__int64							m_nPausedPerformanceCounter;
	__int64							m_nStopPerformanceCounter;
	__int64							m_nCurrentPerformanceCounter;
    __int64							m_nLastPerformanceCounter;

	__int64							m_nPerformanceFrequencyPerSec;				

    float								m_fFrameTime[MAX_SAMPLE_COUNT];
	unsigned int					m_nSampleCount;

    unsigned int					m_nCurrentFrameRate;				
	unsigned int					m_nFramesPerSecond;					
	float								m_fFPSTimeElapsed;		

	bool								m_bStopped;
};
