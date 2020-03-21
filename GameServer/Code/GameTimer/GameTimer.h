#pragma once
#include "../../../MapleConvenienceFunction/Code/Macro.h"
#include "../../../MapleConvenienceFunction/Code/Defines.h"
#include "../Core/Core.h"

struct TimerEvent
{
	TimerEvent(chrono::high_resolution_clock::time_point startTime, Core::EVENT_TYPE eventType, int objID)
		: m_startTime(startTime), m_eventType(eventType), m_objID(objID) {}

	chrono::high_resolution_clock::time_point m_startTime;
	Core::EVENT_TYPE m_eventType;
	int	 m_objID;
	//int		target_id = TARGET_IS_NONE;

	// 우선순위 큐에 데이터를 넣을 때의 비교연산자
	constexpr bool operator < (const TimerEvent& _Left)	const { return ((*this).m_startTime > _Left.m_startTime); };
};

class GameTimer
{
	SINGLE_TONE(GameTimer)

	void Update();

	void AddTimer(Core::EVENT_TYPE, chrono::high_resolution_clock::time_point, int);

	bool IsTimerQueueEmpty()	const { return m_timerQueue.empty(); }
	void TimerQueueMtxLock() { m_timerQueueMtx.lock(); }
	void TimerQueueMtxUnLock() { m_timerQueueMtx.unlock(); }

private:
	priority_queue<TimerEvent> m_timerQueue;
	mutex m_timerQueueMtx;
};

