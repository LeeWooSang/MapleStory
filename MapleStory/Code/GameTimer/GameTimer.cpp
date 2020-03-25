#include "GameTimer.h"
#include "../Defines.h"

INIT_INSTACNE(GameTimer)
GameTimer::GameTimer()
{
	::QueryPerformanceFrequency((LARGE_INTEGER *)&m_nPerformanceFrequencyPerSec);
	::QueryPerformanceCounter((LARGE_INTEGER *)&m_nLastPerformanceCounter); 
	m_TimeScale = 1.0 / (double)m_nPerformanceFrequencyPerSec;

	m_nBasePerformanceCounter = m_nLastPerformanceCounter;
	m_nPausedPerformanceCounter = 0;
	m_nStopPerformanceCounter = 0;

	m_nSampleCount = 0;
	m_nCurrentFrameRate = 0;
	m_nFramesPerSecond = 0;
	m_fFPSTimeElapsed = 0.0f;
}

GameTimer::~GameTimer()
{
	cout << "GameTimer ¼Ò¸êÀÚ" << endl;
}

void GameTimer::Tick(float fps)
{
	if (m_bStopped)
	{
		m_ElapsedTime = 0.f;
		return;
	}

	float elapsedTime = 0.f;

	::QueryPerformanceCounter((LARGE_INTEGER *)&m_nCurrentPerformanceCounter);
	elapsedTime = float((m_nCurrentPerformanceCounter - m_nLastPerformanceCounter) * m_TimeScale);

    if (fps > 0.0f)
    {
        while (elapsedTime < (1.0f / fps))
        {
	        ::QueryPerformanceCounter((LARGE_INTEGER *)&m_nCurrentPerformanceCounter);
			elapsedTime = float((m_nCurrentPerformanceCounter - m_nLastPerformanceCounter) * m_TimeScale);
        }
    } 

	m_nLastPerformanceCounter = m_nCurrentPerformanceCounter;

    if (fabsf(elapsedTime - m_ElapsedTime) < 1.0f)
    {
        ::memmove(&m_fFrameTime[1], m_fFrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
        m_fFrameTime[0] = elapsedTime;

        if (m_nSampleCount < MAX_SAMPLE_COUNT) 
			m_nSampleCount++;
    }

	m_nFramesPerSecond++;
	m_fFPSTimeElapsed += elapsedTime;
	if (m_fFPSTimeElapsed > 1.0f) 
    {
		m_nCurrentFrameRate	= m_nFramesPerSecond;
		m_nFramesPerSecond = 0;
		m_fFPSTimeElapsed = 0.0f;
	} 

    m_ElapsedTime = 0.0f;
    for (ULONG i = 0; i < m_nSampleCount; i++) 
		m_ElapsedTime += m_fFrameTime[i];
    
	if (m_nSampleCount > 0) 
		m_ElapsedTime /= m_nSampleCount;
}

float GameTimer::GetTotalTime()
{
	if (m_bStopped) 
		return(float(((m_nStopPerformanceCounter - m_nPausedPerformanceCounter) - m_nBasePerformanceCounter) * m_TimeScale));
	
	return(float(((m_nCurrentPerformanceCounter - m_nPausedPerformanceCounter) - m_nBasePerformanceCounter) * m_TimeScale));
}

void GameTimer::Reset()
{
	__int64 nPerformanceCounter;
	::QueryPerformanceCounter((LARGE_INTEGER*)&nPerformanceCounter);

	m_nBasePerformanceCounter = nPerformanceCounter;
	m_nLastPerformanceCounter = nPerformanceCounter;
	m_nStopPerformanceCounter = 0;
	m_bStopped = false;
}

void GameTimer::Start()
{
	__int64 nPerformanceCounter;
	::QueryPerformanceCounter((LARGE_INTEGER *)&nPerformanceCounter);
	if (m_bStopped)
	{
		m_nPausedPerformanceCounter += (nPerformanceCounter - m_nStopPerformanceCounter);
		m_nLastPerformanceCounter = nPerformanceCounter;
		m_nStopPerformanceCounter = 0;
		m_bStopped = false;
	}
}

void GameTimer::Stop()
{
	if (!m_bStopped)
	{
		::QueryPerformanceCounter((LARGE_INTEGER *)&m_nStopPerformanceCounter);
		m_bStopped = true;
	}
}
