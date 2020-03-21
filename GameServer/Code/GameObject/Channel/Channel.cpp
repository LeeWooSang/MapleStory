#include "Channel.h"
#include "../Character/Player/Player.h"
#include "../Character/NPC/NPC.h"

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
	// �ʰ� �������� �����־����
	SendAddObjectPacket(myID, myID);

	// ���ӵ� �ٸ� �������Ե� �� ������ ����
	for (int i = 0; i < MAX_USER; ++i)
	{
		if (i == myID)
			continue;

		if (reinterpret_cast<Player*>(m_channelCharacterList[i])->GetIsConnected() == false)
			continue;

		// ���� ������ ��, ���̴� �ֵ鿡�Ը� ����(�� �丮��Ʈ�� ���� �����ȵ�)
		// lock, unlock�� �ʹ� �����ϸ� �ȵ�
		// �׷��� ���� ������ lock, unlock��  ���� �ʹ� ��� ������, lock, unlock�� ó�����ϴ� �κи� ���� ó��
		if (IsNearObject(i, myID) == false)
			continue;

		m_channelCharacterList[i]->ViewListMtxLock();
		m_channelCharacterList[i]->AddIDInViewList(myID);
		m_channelCharacterList[i]->ViewListMtxUnLock();
		SendAddObjectPacket(i, myID);
	}

	// ������ �ٸ� �ֵ� ������ �����־�� ��
	for (int i = 0; i < MAX_USER; ++i)
	{
		// �������� �Ⱥ�������
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

	// ������ ���̴� NPC ������ ����
	for (int i = NPC_ID_START; i < MAX_CHARACTER; ++i)
	{
		if (IsNearObject(myID, i) == false)
			continue;

		// ���̴� NPC�� �����.
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
	// �̵� �� viewList
	unordered_set<int> old_viewList = m_channelCharacterList[myID]->GetViewList();
	m_channelCharacterList[myID]->ViewListMtxUnLock();

	// �̵� �� viewList
	unordered_set<int> new_viewList;

	for (int i = 0; i < MAX_USER; ++i)
	{
		// i�� �ش��ϴ� Ŭ�� �������ְ�, 
		// ���ϰ�, ����ϰ� ��ó�� �ִ���, 
		// ���� ���ϰ� id�ϰ� ���� ���� ��,
		if (reinterpret_cast<Player*>(m_channelCharacterList[i])->GetIsConnected() == true && IsNearObject(myID, i) == true && i != myID)
			new_viewList.emplace(i);
	}

	for (int i = NPC_ID_START; i < MAX_CHARACTER; ++i)
	{
		// i�� �ش��ϴ� Ŭ�� �������ְ�, 
		// ���ϰ�, ����ϰ� ��ó�� �ִ���, 
		// ���� ���ϰ� id�ϰ� ���� ���� ��,
		if (IsNearObject(myID, i) == true)
			new_viewList.emplace(i);
	}

	// ���� ��ó�� �ִ� ������Ʈ�鿡 ����
	for (auto id : new_viewList)
	{
		// ���� �þ߿� ����
		if (old_viewList.count(id) == 0)
		{
			m_channelCharacterList[myID]->ViewListMtxLock();
			m_channelCharacterList[myID]->AddIDInViewList(id);
			m_channelCharacterList[myID]->ViewListMtxUnLock();
			SendAddObjectPacket(myID, id);
			// �÷��̾ �ƴϸ�, NPC�� ��������
			if (IsPlayer(id) == false)
			{
				WakeUpNPC(id);
				continue;
			}

			m_channelCharacterList[id]->ViewListMtxLock();
			// viewList�� �ش��ϴ� id�� ������, 
			if (m_channelCharacterList[id]->GetViewList().count(id) != 0)
			{
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendPositionPacket(id, myID);
			}
			// viewList�� �ش��ϴ� id�� ������,
			else
			{
				m_channelCharacterList[id]->AddIDInViewList(id);
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendAddObjectPacket(id, myID);
			}
		}

		// old_viewList�� new_viewList�� �ִ� Ŭ��ID�� ���� ��, (old, new ���� ����)
		else if (old_viewList.count(id) != 0)
		{
			if (IsPlayer(id) == false)
				continue;

			m_channelCharacterList[id]->ViewListMtxLock();
			// viewList�� �ش��ϴ� id�� ������, 
			if (m_channelCharacterList[id]->GetViewList().count(myID) != 0)
			{
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendPositionPacket(id, myID);
			}
			// viewList�� �ش��ϴ� id�� ������,
			else
			{
				m_channelCharacterList[id]->AddIDInViewList(myID);
				m_channelCharacterList[id]->ViewListMtxUnLock();
				SendAddObjectPacket(id, myID);
			}
		}
	}

	// �þ߿��� �����
	for (auto id : old_viewList)
	{
		if (new_viewList.count(id) != 0)
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

	for (auto npc_id : new_viewList)
	{
		if (IsPlayer(npc_id))	continue;

		OverEx* overEx = new OverEx;
		//overEx->event_type = EV_PLAYER_MOVE;
		//overEx->event_from_id = id;

		// NPC���Ը� ����
		PostQueuedCompletionStatus(GET_INSTANCE(Core)->GetIOCPHandle(), 1, npc_id, &overEx->overlapped);
	}
}

void Channel::DisconnectChannel(int id)
{
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