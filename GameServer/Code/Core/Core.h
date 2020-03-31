#pragma once
#include "../../../MapleStory/Code/Macro.h"
#include "../Defines.h"
#include "../Protocol.h"

constexpr int WORKER_THREAD_SIZE = 4;
constexpr int VIEW_DISTANCE = 3;

class Core
{
	SINGLE_TONE(Core)

public:
	bool Initialize();
	bool Run();

	const HANDLE& GetIOCPHandle()	const { return m_IOCP; }
	enum EVENT_TYPE 
	{ 
		RECV, 	
		SEND, 		
		QUIT,
		PLAYER_LOGIN_OK, 
		PLAYER_LOGIN_ID_FAIL,
		PLAYER_LOGIN_PW_FAIL,
		PLAYER_LOGOUT, 
		PLAYER_STATUS_UPDATE 
	};

	void SendPacket(int, char*);

	class Character* GetPlayer(int id) { return m_characterList[id]; }

private:
	// �������
	void ErrorDisplay(const char*, int);

	void ThreadPool();
	void AcceptClient();
	void Timer();
	void AccessDataBase();

	void RecvPacket(int);

	void ProcessPacket(int, char*);

	void ProcessChannelLogin(char, int);
	void UpdateViewList(int);
	void ProcessEvent(EVENT_TYPE&, int);

	void DisconnectServer(int);

	int CreatePlayerID();

	void SendServerLoginOkPacket(int);
	void SendServerLoginFailPacket(int, char);

	void SendChannelLoginOkPacket(int);
	void SendChannelLoginFailPacket(int);

private:
	volatile bool m_isRun;

	// ��� ����
	HANDLE m_IOCP;
	vector<thread> m_workerThread;
	thread m_acceptThread;
	thread m_timerThread;

	thread m_dbThread;

	SOCKET m_listenSocket;

	vector<class Character*> m_characterList;
	vector<class Channel*> m_channelList;
};
