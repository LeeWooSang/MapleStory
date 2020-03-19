#include "Core.h"
// �޸� ���� �ִ��� �˷��ش�.
#include <crtdbg.h>
#include "../GameObject/Character/Player/Player.h"

INIT_INSTACNE(Core)
Core::Core()
{
	m_IOCP = nullptr;
	m_workerThread.reserve(WORKER_THREAD_SIZE);
	m_characterList.reserve(MAX_CHARACTER);
	m_listenSocket = { 0 };

	// �޸� ���� �ִ��� üũ�� ���ش�.
	// ���� ������, ��ȣ�� ������ش�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ��µ� ��ȣ�� �־��ָ� �� �������� �ٷ� �̵������ش�.
	// [ ���� ]
	// Detected memory leaks!
	//	Dumping objects ->
	// {233} normal block at 0x000001469D91A680, 24 bytes long.
	// 233 �̶�� �������� ���� ����	
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
	// �����߻��� �ѱ۷� ��µǵ��� ���
	wcout.imbue(locale("korean"));

	// IOCP ��ü ����
	m_IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (m_IOCP == nullptr)
		return false;

	// ��Ŀ ������ ����
	for (int i = 0; i < WORKER_THREAD_SIZE; ++i)
		m_workerThread.emplace_back(thread{ &Core::ThreadPool, this });

	// accept ������ ����
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
	wcout << L"���� : " << lpMsgBuf << endl;

	// �����߻��� ���ѷ����� ���߰���
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
		// lpover�� recv���� send���� ������ �־�� ��.
		BOOL is_error = GetQueuedCompletionStatus(m_IOCP, &io_byte, &id, reinterpret_cast<LPWSAOVERLAPPED*>(&overEx), INFINITE);

		//  GetQueuedCompletionStatus( )�� �������� �ƴ��� Ȯ���Ѵ�
		if (is_error == FALSE)
		{
			int error_num = WSAGetLastError();
			if (error_num != 64)
				ErrorDisplay(" GetQueuedCompletionStatus()", error_num);
			else
			{
				cout << id << "�� Ŭ���̾�Ʈ ����" << endl;
				Disconnect(static_cast<int>(id));
				continue;
			}
		}

		// Ŭ��� �������ٸ� (Ŭ�� ������ ��)
		if (io_byte == 0)
		{
			cout << id << "�� Ŭ���̾�Ʈ ����" << endl;
			Disconnect(static_cast<int>(id));
			continue;
		}

		// recv�� send�� ������ �� ó��
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
	// Winsock Start - windock.dll �ε�
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

	// 2. ���ϼ���
	if (::bind(m_listenSocket, (SOCKADDR*)&serverAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "Error - Fail bind" << endl;
		closesocket(m_listenSocket);
		WSACleanup();
		return;
	}

	// 3. ���Ŵ�⿭����
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

		// �� ���̵� ��������
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

	// WSASend(���信 ����)�� �ݹ��� ���
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
	// ��Ŷ�� ������ ���ۿ� ����
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
	// �̵� �� viewList
	unordered_set<int> old_viewList = m_characterList[myID]->GetViewList();
	m_characterList[myID]->ViewListMtxUnLock();
	
	// �̵� �� viewList
	unordered_set<int> new_viewList;

	for (int i = 0; i < MAX_USER; ++i)
	{
		// i�� �ش��ϴ� Ŭ�� �������ְ�, 
		// ���ϰ�, ����ϰ� ��ó�� �ִ���, 
		// ���� ���ϰ� id�ϰ� ���� ���� ��,
		Player* player = reinterpret_cast<Player*>(m_characterList[i]);
		if (player->GetIsConnected() == true && Is_Near_Object(id, i) == true && i != id)
			new_viewList.emplace(i);
	}

	for (int i = MONSTER_ID_START; i < MAX_CHARACTER; ++i)
	{
		// i�� �ش��ϴ� Ŭ�� �������ְ�, 
		// ���ϰ�, ����ϰ� ��ó�� �ִ���, 
		// ���� ���ϰ� id�ϰ� ���� ���� ��,
		// ���Ͱ� ���� �ʾ��� ��
		if (Is_Near_Object(id, i) == true && m_characterList[i]->GetState() != DIE)
			new_viewList.insert(i);
	}

	// Put Object
	// ���� ��ó�� �ִ� ������Ʈ�鿡 ����
	for (auto id : new_viewList)
	{
		// (���� �þ߿� ����)
		if (old_viewList.count(id) == 0)
		{
			m_characterList[myID]->ViewListMtxLock();
			m_characterList[myID]->GetViewList().emplace(id);
			m_characterList[myID]->ViewListMtxUnLock();
			//Send_Add_Object_Packet(id, character);

			if (id < MAX_CHARACTER)
				Send_Add_Object_Packet(myID, id);

			// �÷��̾ �ƴϸ�, NPC�� ��������
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

		// old_viewList�� new_viewList�� �ִ� Ŭ��ID�� ���� ��, (old, new ���� ����)
		else if (old_viewList.count(character) != 0)
		{
			if (Is_Player(character) == false)	continue;

			m_characterList[character]->GetViewListMtx().lock();
			// viewList�� �ش��ϴ� id�� ������, 
			if (m_characterList[character]->GetViewList().count(id) != 0)
			{
				m_characterList[character]->GetViewListMtx().unlock();
				Send_Position_Packet(character, id);
			}

			// viewList�� �ش��ϴ� id�� ������,
			else
			{
				m_characterList[character]->GetViewList().emplace(id);
				m_characterList[character]->GetViewListMtx().unlock();
				Send_Add_Object_Packet(character, id);
			}
		}
	}

	// �þ߿��� �����
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
	// ���̵� ���� ������, �������鼭 ��ٸ�����
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




