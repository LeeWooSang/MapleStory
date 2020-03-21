#pragma once
#include "../GameObject.h"

constexpr int MAX_CHANNEL_USER = 100;

class Channel : public GameObject
{
public:
	Channel(const string&);
	virtual ~Channel();

	virtual bool Initialize(void*);
	virtual void Update();

	void ProcessChannelLogin(int);
	void UpdateObjectViewList(int);

	void DisconnectChannel(int);

	void WakeUpNPC(int);
	bool IsPlayer(int);
	bool IsNearObject(int, int);

	size_t GetChannelUserSize() const { return m_channelCharacterList.size(); }
	void AddPlayerInChannel(int id, class Character* player) { m_channelCharacterList.emplace(id, player); }

	void ChannelMtxLock() { m_channelMtx.lock(); }
	void ChannelMtxUnLock() { m_channelMtx.unlock(); }

private:
	// Send 함수 종류
	void SendPositionPacket(int, int);
	void SendRemoveObjectPacket(int, int);
	void SendAddObjectPacket(int, int);

private:
	unordered_map<int, class Character*> m_channelCharacterList;
	mutex m_channelMtx;
};

