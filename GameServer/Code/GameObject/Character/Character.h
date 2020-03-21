#pragma once
#include "../GameObject.h"
#include "../../Core/Core.h"

// Ȯ�� ������Ʈ ����ü
struct OverEx
{
	WSAOVERLAPPED	overlapped;
	WSABUF					dataBuffer;
	char							messageBuffer[MAX_BUFFER];
	Core::EVENT_TYPE	event_type;
	int								event_target_id;
};

class Character : public GameObject
{
public:
	Character(const string& name);
	virtual ~Character();

	virtual bool Initialize(void*);
	virtual void Update();
	virtual void ClearCharacterInfo();

	void UpdatePosition(char);

	OverEx& GetOverEx() { return m_overEx; }

	void ViewListMtxLock() { m_viewListMtx.lock(); }
	void ViewListMtxUnLock() { m_viewListMtx.unlock(); }

	const unordered_set<int>& GetViewList()	const { return m_viewList; }
	void AddIDInViewList(int id) { m_viewList.emplace(id); }
	void RemoveIDInViewList(int id) { m_viewList.erase(id); }

	void SetChannel(unsigned char channel) { m_channel = channel; }
	unsigned char GetChannel() const { return m_channel; }

	int GetMap()	const { return m_map; }

	int GetX()	const { return m_x; }
	void SetX(int x) { m_x = x; }
	int GetY() const { return m_y; }
	void SetY(int y) { m_y = y; }

protected:
	class Status* m_stat;
	
	int m_ID;

	OverEx	m_overEx;
	mutex m_viewListMtx;
	unordered_set<int> m_viewList;

	unsigned char m_channel;

	int m_map;

	int m_x;
	int m_y;
};

