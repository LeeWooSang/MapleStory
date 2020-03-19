#pragma once
#include "../../../MapleConvenienceFunction/Code/Defines.h"
#include "../../../MapleConvenienceFunction/Code/Macro.h"
#include "../Protocol.h"

constexpr int WORKER_THREAD_SIZE = 4;

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
	void UpdateObjectView(int);

	void Disconnect(int);

	int CreatePlayerID();

	HANDLE m_IOCP;
	vector<thread> m_workerThread;
	thread m_acceptThread;

	SOCKET m_listenSocket;

	vector<class Character*> m_characterList;
};