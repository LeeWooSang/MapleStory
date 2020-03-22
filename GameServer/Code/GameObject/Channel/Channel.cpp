#include "Channel.h"
#include "../Character/Player/Player.h"
#include "../Character/NPC/NPC.h"
#include "../../DataBase/DataBase.h"

Channel::Channel(const string& name)
	: GameObject(name)
{
	m_channelCharacterList.clear();
}

Channel::~Channel()
{
	m_channelCharacterList.clear();
}

bool Channel::Initialize(void*)
{
	return true;
}

void Channel::Update()
{
}

void Channel::ProcessChannelLogin(int myID)
{
	// 너가 누구인지 보내주어야함
	SendAddObjectPacket(myID, myID);

	// 접속된 다른 유저에게도 내 정보를 보냄
	for (int i = 0; i < MAX_USER; ++i)
	{
		if (i == myID)
			continue;

		if (reinterpret_cast<Player*>(m_channelCharacterList[i])->GetIsConnected() == false)
			continue;

		// 내가 들어왔을 때, 보이는 애들에게만 보냄(내 뷰리스트에 나를 넣음안됨)
		// lock, unlock을 너무 자주하면 안됨
		// 그러나 루프 밖으로 lock, unlock을  빼면 너무 길기 때문에, lock, unlock을 처리해하는 부분만 따로 처리
		if (IsNearObject(i, myID) == false)
			continue;

		m_channelCharacterList[i]->ViewListMtxLock();
		m_channelCharacterList[i]->AddIDInViewList(myID);
		m_channelCharacterList[i]->ViewListMtxUnLock();
		SendAddObjectPacket(i, myID);
	}

	// 나에게 다른 애들 정보도 보내주어야 함
	for (int i = 0; i < MAX_USER; ++i)
	{
		// 내정보는 안보내도됨
		if (i == myID)
			continue;

		if (reinterpret_cast<Player*>(m_channelCharacterList[i])->GetIsConnected() == false)
			continue;

		if (IsNearObject(i, myID) == false)
			continue;

		m_channelCharacterList[myID]->ViewListMtxLock();
		m_channelCharacterList[myID]->AddIDInViewList(i);
		m_channelCharacterList[myID]->ViewListMtxUnLock();
		SendAddObjectPacket(myID, i);
	}

	// 나에게 보이는 NPC 정보를 보냄
	for (int i = NPC_ID_START; i < MAX_CHARACTER; ++i)
	{
		if (IsNearObject(myID, i) == false)
			continue;

		// 보이는 NPC를 깨운다.
		WakeUpNPC(i);

		m_channelCharacterList[myID]->ViewListMtxLock();
		m_channelCharacterList[myID]->AddIDInViewList(i);
		m_channelCharacterList[myID]->ViewListMtxUnLock();
		SendAddObjectPacket(myID, i);
	}
}

void Channel::UpdateObjectViewList(int myID)
{
	m_channelCharacterList[myID]->ViewListMtxLock();
	// 이동 전 viewList
	unordered_set<int> oldViewList = m_channelCharacterList[myID]->GetViewList();
	m_channelCharacterList[myID]->ViewListMtxUnLock();

	// 이동 후 viewList
	unordered_set<int> newViewList;

	for (int i = 0; i < MAX_USER; ++i)
	{
		// i에 해당하는 클라가 접속해있고, 
		// 나하고, 상대하고 근처에 있는지, 
		// 또한 나하고 id하고 같지 않을 때,
		if (reinterpret_cast<Player*>(m_channelCharacterList[i])->GetIsConnected() == true && IsNearObject(myID, i) == true && i != myID)
			newViewList.emplace(i);
	}

	for (int i = NPC_ID_START; i < MAX_CHARACTER; ++i)
	{
		// i에 해당하는 클라가 접속해있고, 
		// 나하고, 상대하고 근처에 있는지, 
		// 또한 나하고 id하고 같지 않을 때,
		if (IsNearObject(myID, i) == true)
			newViewList.emplace(i);
	}

	// 나와 근처에 있는 오브젝트들에 대해
	for (auto id : newViewList)
	{
		// 새로 시야에 들어옴
		if (oldViewList.count(id) == 0)
		{
			m_channelCharacterList[myID]->ViewListMtxLock();
			m_channelCharacterList[myID]->AddIDInViewList(id);
			m_channelCharacterList[myID]->ViewListMtxUnLock();
			SendAddObjectPacket(myID, id);
			// 플레이어가 아니면, NPC를 깨워야함
			if (IsPlayer(id) == false)
			{
				WakeUpNPC(id);
				continue;
			}

			m_channelCharacterList[id]->ViewListMtxLock();
			// viewList에 해당하는 id가 있으면, 
			if (m_channelCharacterList[id]->GetViewList().count(id) != 0)
			{
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendPositionPacket(id, myID);
			}
			// viewList에 해당하는 id가 없으면,
			else
			{
				m_channelCharacterList[id]->AddIDInViewList(id);
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendAddObjectPacket(id, myID);
			}
		}

		// oldViewList에 newViewList에 있는 클라ID가 있을 때, (old, new 동시 존재)
		else if (oldViewList.count(id) != 0)
		{
			if (IsPlayer(id) == false)
				continue;

			m_channelCharacterList[id]->ViewListMtxLock();
			// viewList에 해당하는 id가 있으면, 
			if (m_channelCharacterList[id]->GetViewList().count(myID) != 0)
			{
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendPositionPacket(id, myID);
			}
			// viewList에 해당하는 id가 없으면,
			else
			{
				m_channelCharacterList[id]->AddIDInViewList(myID);
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendAddObjectPacket(id, myID);
			}
		}
	}

	// 시야에서 사라짐
	for (auto id : oldViewList)
	{
		if (newViewList.count(id) != 0)
			continue;

		m_channelCharacterList[myID]->ViewListMtxLock();
		m_channelCharacterList[myID]->RemoveIDInViewList(id);
		m_channelCharacterList[myID]->ViewListMtxUnLock();
		SendRemoveObjectPacket(myID, id);

		if (IsPlayer(id) == false)
			continue;

		m_channelCharacterList[id]->ViewListMtxLock();
		if (m_channelCharacterList[id]->GetViewList().count(myID) != 0)
		{
			m_channelCharacterList[id]->RemoveIDInViewList(myID);
			m_channelCharacterList[id]->ViewListMtxUnLock();
			SendRemoveObjectPacket(id, myID);
		}

		else
			m_channelCharacterList[id]->ViewListMtxUnLock();
	}

	SendPositionPacket(myID, myID);

	for (auto npc_id : newViewList)
	{
		if (IsPlayer(npc_id))	continue;

		OverEx* overEx = new OverEx;
		//overEx->event_type = EV_PLAYER_MOVE;
		//overEx->event_from_id = id;

		// NPC에게만 전송
		PostQueuedCompletionStatus(GET_INSTANCE(Core)->GetIOCPHandle(), 1, npc_id, &overEx->overlapped);
	}
}

void Channel::DisconnectChannel(int id)
{
	// viewList 정리
	for (int i = 0; i < MAX_USER; ++i)
	{
		if (reinterpret_cast<Player*>(m_channelCharacterList[i])->GetIsConnected() == false)
			continue;

		m_channelCharacterList[i]->ViewListMtxLock();
		if (m_channelCharacterList[i]->GetViewList().count(id) != 0)
		{
			m_channelCharacterList[i]->ViewListMtxUnLock();
			SendRemoveObjectPacket(i, id);
		}
		else
			m_channelCharacterList[i]->ViewListMtxUnLock();
	}

	// id 플레이어를 지워줌
	m_channelMtx.lock();
	m_channelCharacterList.erase(id);
	m_channelMtx.unlock();
}

void Channel::WakeUpNPC(int id)
{
}

bool Channel::IsPlayer(int id)
{
	if (id >= 0 && id < MAX_USER)
		return true;
	return false;
}

bool Channel::IsNearObject(int a, int b)
{
	int map1 = m_channelCharacterList[a]->GetMap();
	int map2 = m_channelCharacterList[b]->GetMap();
	if (map1 != map2)
		return false;

	int x1 = m_channelCharacterList[a]->GetX();
	int x2 = m_channelCharacterList[b]->GetY();
	int y1 = m_channelCharacterList[a]->GetY();
	int y2 = m_channelCharacterList[b]->GetY();

	if (VIEW_DISTANCE < abs(x1 - x2))
		return false;
	if (VIEW_DISTANCE < abs(y1 - y2))
		return false;

	return true;
}

void Channel::SendPositionPacket(int to, int obj)
{
	SCPacket_Position packet;
	packet.id = obj;
	packet.size = sizeof(SCPacket_Position);
	packet.type = SC_PACKET_TYPE::SC_POSITION;
	packet.x = m_channelCharacterList[obj]->GetX();
	packet.x = m_channelCharacterList[obj]->GetY();

	GET_INSTANCE(Core)->SendPacket(to, reinterpret_cast<char*>(&packet));
}

void Channel::SendRemoveObjectPacket(int to, int obj)
{
	SCPacket_Remove_Object packet;
	packet.id = obj;
	packet.size = sizeof(SCPacket_Remove_Object);
	packet.type = SC_PACKET_TYPE::SC_REMOVE_OBJECT;

	GET_INSTANCE(Core)->SendPacket(to, reinterpret_cast<char*>(&packet));
}

void Channel::SendAddObjectPacket(int to, int obj)
{
	SCPacket_Add_Object packet;
	packet.id = obj;
	packet.size = sizeof(SCPacket_Add_Object);
	packet.type = SC_PACKET_TYPE::SC_ADD_OBJECT;


	GET_INSTANCE(Core)->SendPacket(to, reinterpret_cast<char*>(&packet));
}