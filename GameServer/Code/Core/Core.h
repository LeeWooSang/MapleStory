#pragma once
#include "../../../MapleConvenienceFunction/Code/Defines.h"
#include "../../../MapleConvenienceFunction/Code/Macro.h"
#include "../Protocol.h"
#include "../GameObject/Channel/Channel.h"

constexpr int WORKER_THREAD_SIZE = 4;
constexpr int VIEW_DISTANCE = 3;

class Core
{
	SINGLE_TONE(Core)

public:
	bool Initialize();
	bool Run();

	enum EVENT_TYPE { RECV, SEND, QUIT };

private:
	// 에러출력
	void ErrorDisplay(const char*, int);

	void ThreadPool();
	void AcceptClient();
	
	void RecvPacket(int);
	void SendPacket(int, char*);

	void ProcessPacket(int, char*);

	void ProcessChannelLogin(unsigned char, int);
	void UpdateObjectViewList(int);

	void Disconnect(int);

	int CreatePlayerID();
	bool IsPlayer(int);
	bool IsNearObject(int, int);

	void WakeUpNPC(int);

private:
	// Send 함수 종류
	void SendServerLoginOkPacket(int);
	void SendServerLoginFailPacket(int);

	void SendChannelLoginOkPacket(int);
	void SendChannelLoginFailPacket(int);

	void SendPositionPacket(int, int);
	void SendRemoveObjectPacket(int, int);
	void SendAddObjectPacket(int, int);

private:
	// 멤버 변수
	HANDLE m_IOCP;
	vector<thread> m_workerThread;
	thread m_acceptThread;

	SOCKET m_listenSocket;

	vector<class Character*> m_characterList;
	vector<Channel> m_channelList;
};