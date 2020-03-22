#include "GameTimer.h"
#include "../GameObject/Character/Character.h"
#include "../DataBase/DataBase.h"

INIT_INSTACNE(GameTimer)
GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

void GameTimer::Update()
{
	// CPU ���ϸ� �������� ��� ����
	this_thread::sleep_for(10ms);
	while (true)
	{
		m_timerQueueMtx.lock();
		if (m_timerQueue.empty() == true)
		{
			m_timerQueueMtx.unlock();
			break;
		}

		// Ÿ�̸� ť���� �ش� �̺�Ʈ�� ����
		TimerEvent ev = m_timerQueue.top();
		m_timerQueueMtx.unlock();

		if (ev.m_startTime > chrono::high_resolution_clock::now())
			break;

		if (ev.m_eventType == Core::EVENT_TYPE::PLAYER_STATUS_UPDATE)
		{
			GET_INSTANCE(DataBase)->AddDBTransactionQueue(DB_TRANSACTION_TYPE::UPDATE_PLAYER_STATUS_INFO, ev.m_objID);
			break;
		}

		m_timerQueueMtx.lock();
		m_timerQueue.pop();
		m_timerQueueMtx.unlock();

		OverEx* overEx = new OverEx;
		overEx->eventType = ev.m_eventType;
		overEx->myID = ev.m_objID;

		// ��Ŀ�����忡�� Process_Event�� �Ѱܾ� ��
		PostQueuedCompletionStatus(GET_INSTANCE(Core)->GetIOCPHandle(), 1, ev.m_objID, &overEx->overlapped);
	}
}

void GameTimer::AddTimer(Core::EVENT_TYPE e_type, chrono::high_resolution_clock::time_point start_t, int obj_id)
{
	m_timerQueueMtx.lock();
	// Ÿ�̸� ť�� �ش� �̺�Ʈ�� ����
	m_timerQueue.push(TimerEvent(start_t, e_type, obj_id));
	m_timerQueueMtx.unlock();
}
