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

	const HANDLE& GetIOCPHandle()	const { return m_IOCP; }
	enum EVENT_TYPE { RECV, SEND, QUIT };
	void SendPacket(int, char*);

private:
	// 에러출력
	void ErrorDisplay(const char*, int);

	void ThreadPool();
	void AcceptClient();
	
	void RecvPacket(int);

	void ProcessPacket(int, char*);

	void ProcessLogin(unsigned char, int);
	void UpdateViewList(int);

	void DisconnectServer(int);

	int CreatePlayerID();

	void SendServerLoginOkPacket(int);
	void SendServerLoginFailPacket(int);

	void SendChannelLoginOkPacket(int);
	void SendChannelLoginFailPacket(int);

private:
	// 멤버 변수
	HANDLE m_IOCP;
	vector<thread> m_workerThread;
	thread m_acceptThread;

	SOCKET m_listenSocket;

	vector<class Character*> m_characterList;
	vector<Channel*> m_channelList;
};