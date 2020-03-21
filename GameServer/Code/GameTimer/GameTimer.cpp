#include "GameTimer.h"
#include "../GameObject/Character/Character.h"

INIT_INSTACNE(GameTimer)
GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

void GameTimer::Update()
{
	// CPU 부하를 덜기위해 잠깐 멈춤
	this_thread::sleep_for(10ms);
	while (true)
	{
		m_timerQueueMtx.lock();
		if (m_timerQueue.empty() == true)
		{
			m_timerQueueMtx.unlock();
			break;
		}

		// 타이머 큐에서 해당 이벤트를 얻어옴
		TimerEvent ev = m_timerQueue.top();
		m_timerQueueMtx.unlock();

		if (ev.m_startTime > chrono::high_resolution_clock::now())
			break;

		m_timerQueueMtx.lock();
		m_timerQueue.pop();
		m_timerQueueMtx.unlock();

		OverEx* overEx = new OverEx;
		overEx->eventType = ev.m_eventType;
		overEx->myID = ev.m_objID;

		// 워커스레드에게 Process_Event를 넘겨야 됨
		PostQueuedCompletionStatus(GET_INSTANCE(Core)->GetIOCPHandle(), 1, ev.m_objID, &overEx->overlapped);
	}
}

void GameTimer::AddTimer(Core::EVENT_TYPE e_type, chrono::high_resolution_clock::time_point start_t, int obj_id)
{
	m_timerQueueMtx.lock();
	// 타이머 큐에 해당 이벤트를 넣음
	m_timerQueue.push(TimerEvent(start_t, e_type, obj_id));
	m_timerQueueMtx.unlock();
}
