#include "Core.h"
// 메모리 릭이 있는지 알려준다.
#include <crtdbg.h>
#include "../GameObject/Character/Player/Player.h"

INIT_INSTACNE(Core)
Core::Core()
{
	m_IOCP = nullptr;
	m_workerThread.reserve(WORKER_THREAD_SIZE);
	m_characterList.reserve(MAX_CHARACTER);
	m_listenSocket = { 0 };

	// 메모리 릭이 있는지 체크를 해준다.
	// 릭이 있으면, 번호를 출력해준다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 출력된 번호를 넣어주면 그 지점으로 바로 이동시켜준다.
	// [ 예시 ]
	// Detected memory leaks!
	//	Dumping objects ->
	// {233} normal block at 0x000001469D91A680, 24 bytes long.
	// 233 이라는 지점에서 릭이 생김	
	//_CrtSetBreakAlloc(1061);
}

Core::~Core()
{
	for (auto& thd : m_workerThread)
	{
		if(thd.joinable() == true)
			thd.join();
	}

	if(m_acceptThread.joinable() == true)
		m_acceptThread.join();

	if (m_IOCP != nullptr)
	{
		CloseHandle(m_IOCP);
		m_IOCP = nullptr;
	}

	cout << "Server is quit" << endl;
}

bool Core::Initialize()
{
	_wsetlocale(LC_ALL, L"korean");
	// 에러발생시 한글로 출력되도록 명령
	wcout.imbue(locale("korean"));

	// IOCP 객체 생성
	m_IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (m_IOCP == nullptr)
		return false;

	// 워커 스레드 생성
	for (int i = 0; i < WORKER_THREAD_SIZE; ++i)
		m_workerThread.emplace_back(thread{ &Core::ThreadPool, this });

	// accept 스레드 생성
	m_acceptThread = thread{ &Core::AcceptClient, this };

	cout << "Server Initialize OK!!" << endl;

	return true;
}

bool Core::Run()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		for (auto& thd : m_workerThread)
		{
			OverEx* overEx = new OverEx;
			overEx->event_type = EVENT_TYPE::QUIT;

			PostQueuedCompletionStatus(m_IOCP, 1, NULL, &overEx->overlapped);
		}

		cout << "WorkerThread is quit" << endl;

		closesocket(m_listenSocket);
		WSACleanup();

		return false;
	}

	return true;
}

void Core::ErrorDisplay(const char* msg, int error)
{
	WCHAR* lpMsgBuf;
	FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	cout << msg;
	wcout << L"설명 : " << lpMsgBuf << endl;

	// 에러발생시 무한루프로 멈추게함
	while (true);

	LocalFree(lpMsgBuf);
}

void Core::ThreadPool()
{
	while (true)
	{
		DWORD io_byte;
		unsigned long long id;
		OverEx* overEx;
		// lpover에 recv인지 send인지 정보를 넣어야 됨.
		BOOL is_error = GetQueuedCompletionStatus(m_IOCP, &io_byte, &id, reinterpret_cast<LPWSAOVERLAPPED*>(&overEx), INFINITE);

		//  GetQueuedCompletionStatus( )가 에러인지 아닌지 확인한다
		if (is_error == FALSE)
		{
			int error_num = WSAGetLastError();
			if (error_num != 64)
				ErrorDisplay(" GetQueuedCompletionStatus()", error_num);
			else
			{
				cout << id << "번 클라이언트 나감" << endl;
				Disconnect(static_cast<int>(id));
				continue;
			}
		}

		// 클라와 끊어졌다면 (클라가 나갔을 때)
		if (io_byte == 0)
		{
			cout << id << "번 클라이언트 나감" << endl;
			Disconnect(static_cast<int>(id));
			continue;
		}

		// recv와 send가 끝났을 때 처리
		if (overEx->event_type == EVENT_TYPE::RECV)
		{

		}

		else if (overEx->event_type == EVENT_TYPE::SEND)
		{

		}

		else if (overEx->event_type == EVENT_TYPE::QUIT)
		{
			delete overEx;
			break;
		}
	}
}

void Core::AcceptClient()
{	
	// Winsock Start - windock.dll 로드
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
	{
		cout << "Error - Can not load 'winsock.dll' file" << endl;
		return;
	}

	m_listenSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_listenSocket == INVALID_SOCKET)
	{
		cout << "Error - Invalid Socket" << endl;
		WSACleanup();
		return;
	}

	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = PF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// 2. 소켓설정
	if (::bind(m_listenSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "Error - Fail bind" << endl;
		closesocket(m_listenSocket);
		WSACleanup();
		return;
	}

	// 3. 수신대기열생성
	if (listen(m_listenSocket, 5) == SOCKET_ERROR)
	{
		cout << "Error - Fail listen" << endl;
		closesocket(m_listenSocket);
		WSACleanup();
		return;
	}

	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	memset(&clientAddr, 0, addrLen);
	SOCKET clientSocket;

	while (true)
	{
		clientSocket = accept(m_listenSocket, (sockaddr*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			if (error == 10004)
			{
				cout << "AcceptThread it quit" << endl;
				return;
			}

			cout << "Error - Accept Failure" << endl;
			break;
		}

		// 빈 아이디를 생성해줌
		int id = CreatePlayerID();

		Player* player = reinterpret_cast<Player*>(m_characterList[id]);

		player->SetSocket(clientSocket);
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(clientSocket), m_IOCP, id, 0);

		RecvPacket(id);
	}

	closesocket(m_listenSocket);
	WSACleanup();
}

void Core::RecvPacket(int id)
{
	DWORD flags = 0;
	SOCKET socket = reinterpret_cast<Player*>(m_characterList[id])->GetSocket();
	OverEx* over = &(m_characterList[id]->GetOverEx());

	// WSASend(응답에 대한)의 콜백일 경우
	over->dataBuffer.len = MAX_BUFFER;
	over->dataBuffer.buf = over->messageBuffer;
	ZeroMemory(&(over->overlapped), sizeof(WSAOVERLAPPED));

	if (WSARecv(socket, &over->dataBuffer, 1, nullptr, &flags, &(over->overlapped), nullptr) == SOCKET_ERROR)
	{
		int error = WSAGetLastError();

		if (error != WSA_IO_PENDING)
			ErrorDisplay("WSARecv() Error - ", error);
	}
}

void Core::SendPacket(int id, char* packet)
{
	SOCKET socket = reinterpret_cast<Player*>(m_characterList[id])->GetSocket();
	OverEx* over = new OverEx;

	over->dataBuffer.len = packet[0];
	over->dataBuffer.buf = over->messageBuffer;
	// 패킷의 내용을 버퍼에 복사
	memcpy(over->messageBuffer, packet, packet[0]);
	ZeroMemory(&(over->overlapped), sizeof(WSAOVERLAPPED));
	over->event_type = EVENT_TYPE::SEND;

	if (WSASend(socket, &over->dataBuffer, 1, nullptr, 0, &(over->overlapped), nullptr) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
			cout << "Error - Fail WSARecv(error_code : " << WSAGetLastError() << endl;
	}
}

void Core::ProcessPacket(int id, char* buf)
{
	switch (buf[1])
	{
	case CS_MOVE:
		CS_Packet_Move* packet = reinterpret_cast<CS_Packet_Move*>(buf);
		m_characterList[id]->UpdatePosition(packet->direction);
		break;

	default:
		break;
	}
}

void Core::UpdateObjectView(int myID)
{
	m_characterList[myID]->ViewListMtxLock();
	// 이동 전 viewList
	unordered_set<int> old_viewList = m_characterList[myID]->GetViewList();
	m_characterList[myID]->ViewListMtxUnLock();
	
	// 이동 후 viewList
	unordered_set<int> new_viewList;

	for (int i = 0; i < MAX_USER; ++i)
	{
		// i에 해당하는 클라가 접속해있고, 
		// 나하고, 상대하고 근처에 있는지, 
		// 또한 나하고 id하고 같지 않을 때,
		Player* player = reinterpret_cast<Player*>(m_characterList[i]);
		if (player->GetIsConnected() == true && Is_Near_Object(id, i) == true && i != id)
			new_viewList.emplace(i);
	}

	for (int i = MONSTER_ID_START; i < MAX_CHARACTER; ++i)
	{
		// i에 해당하는 클라가 접속해있고, 
		// 나하고, 상대하고 근처에 있는지, 
		// 또한 나하고 id하고 같지 않을 때,
		// 몬스터가 죽지 않았을 때
		if (Is_Near_Object(id, i) == true && m_characterList[i]->GetState() != DIE)
			new_viewList.insert(i);
	}

	// Put Object
	// 나와 근처에 있는 오브젝트들에 대해
	for (auto id : new_viewList)
	{
		// (새로 시야에 들어옴)
		if (old_viewList.count(id) == 0)
		{
			m_characterList[myID]->ViewListMtxLock();
			m_characterList[myID]->GetViewList().emplace(id);
			m_characterList[myID]->ViewListMtxUnLock();
			//Send_Add_Object_Packet(id, character);

			if (id < MAX_CHARACTER)
				Send_Add_Object_Packet(myID, id);

			// 플레이어가 아니면, NPC를 깨워야함
			//if (Is_Player(character) == false)
			if (Is_Player(id) == false && id < MAX_CHARACTER)
			{
				WakeUp_NPC(id);
				continue;
			}

			if (id < MAX_CHARACTER)
			{
				m_characterList[id]->ViewListMtxLock();
				if (m_characterList[id]->GetViewList().count(id) != 0)
				{
					m_characterList[id]->ViewListMtxUnLock();
					Send_Position_Packet(id, myID);
				}

				else
				{
					m_characterList[character]->GetViewList().emplace(id);
					m_characterList[character]->GetViewListMtx().unlock();
					Send_Add_Object_Packet(character, id);
				}
			}
		}

		// old_viewList에 new_viewList에 있는 클라ID가 있을 때, (old, new 동시 존재)
		else if (old_viewList.count(character) != 0)
		{
			if (Is_Player(character) == false)	continue;

			m_characterList[character]->GetViewListMtx().lock();
			// viewList에 해당하는 id가 있으면, 
			if (m_characterList[character]->GetViewList().count(id) != 0)
			{
				m_characterList[character]->GetViewListMtx().unlock();
				Send_Position_Packet(character, id);
			}

			// viewList에 해당하는 id가 없으면,
			else
			{
				m_characterList[character]->GetViewList().emplace(id);
				m_characterList[character]->GetViewListMtx().unlock();
				Send_Add_Object_Packet(character, id);
			}
		}
	}

	// 시야에서 사라짐
	for (auto character : old_viewList)
	{
		if (new_viewList.count(character) != 0)	continue;

		if (character >= ORANGEMUSHROOM_ID_START && character < RIBBONPIG_ID_START)
		{
			OrangeMushroom* monster = reinterpret_cast<OrangeMushroom*>(m_characterList[character]);
			int target = monster->GetTarget();
			if (target == id)
				monster->SetTarget(-1);
		}

		m_characterList[id]->GetViewListMtx().lock();
		m_characterList[id]->GetViewList().erase(character);
		m_characterList[id]->GetViewListMtx().unlock();

		if (character < MAX_CHARACTER)
			Send_Remove_Object_Packet(id, character);
		else
			Send_Remove_Item_Packet(id, character);

		if (Is_Player(character) == false)	continue;

		m_characterList[character]->GetViewListMtx().lock();
		if (m_characterList[character]->GetViewList().count(id) != 0)
		{
			m_characterList[character]->GetViewList().erase(id);
			m_characterList[character]->GetViewListMtx().unlock();
			Send_Remove_Object_Packet(character, id);
		}

		else
			m_characterList[character]->GetViewListMtx().unlock();
	}
}

void Core::Disconnect(int id)
{
	for (int i = 0; i < MAX_USER; ++i)
	{
		if (reinterpret_cast<Player*>(m_characterList[i])->GetIsConnected() == false)
			continue;

		m_characterList[i]->ViewListMtxLock();
		if (m_characterList[i]->GetViewList().count(id) != 0)
		{
			m_characterList[i]->ViewListMtxUnLock();
			//Send_Remove_Object_Packet(i, id);
		}
		else
			m_characterList[i]->ViewListMtxUnLock();
	}
	Player* player = reinterpret_cast<Player*>(m_characterList[id]);
	player->ClearPlayerInfo();
}

int Core::CreatePlayerID()
{
	// 아이디가 있을 때까지, 루프돌면서 기다리게함
	while (true)
	{
		for (int i = 0; i < MAX_USER; ++i)
		{
			Player* player = reinterpret_cast<Player*>(m_characterList[i]);

			if (player->GetIsConnected() == false)
			{
				player->SetIsConnected(true);
				return i;
			}
		}
	}
}




