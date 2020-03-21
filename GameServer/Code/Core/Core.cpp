#include "Core.h"
// �޸� ���� �ִ��� �˷��ش�.
#include <crtdbg.h>
#include "../GameObject/Character/Player/Player.h"

INIT_INSTACNE(Core)
Core::Core()
{
	m_IOCP = nullptr;
	m_workerThread.reserve(WORKER_THREAD_SIZE);
	m_workerThread.clear();

	m_listenSocket = 0;

	m_channelList.reserve(MAX_CHANNEL);
	m_channelList.clear();

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
	for (auto& character : m_characterList)
	{
		if (character != nullptr)
		{
			delete character;
			character = nullptr;
		}
	}

	for (auto& channel : m_channelList)
	{
		if (channel != nullptr)
		{
			delete channel;
			channel = nullptr;
		}
	}

	if (m_acceptThread.joinable() == true)
		m_acceptThread.join();

	for (auto& thd : m_workerThread)
	{
		if (thd.joinable() == true)
			thd.join();
	}

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

	for (int i = 0; i < MAX_CHANNEL; ++i)
		m_channelList.emplace_back(new Channel(to_string(i) + "ä��"));

	// �÷��̾� ����
	for (int i = 0; i < MAX_USER; ++i)
		m_characterList.emplace_back(new Player(""));

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
				DisconnectServer(static_cast<int>(id));
				continue;
			}
		}

		// Ŭ��� �������ٸ� (Ŭ�� ������ ��)
		if (io_byte == 0)
		{
			cout << id << "�� Ŭ���̾�Ʈ ����" << endl;
			DisconnectServer(static_cast<int>(id));
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
		int myID = CreatePlayerID();

		Player* player = reinterpret_cast<Player*>(m_characterList[myID]);
		player->SetSocket(clientSocket);
		player->SetIsConnected(true);

		CreateIoCompletionPort(reinterpret_cast<HANDLE>(clientSocket), m_IOCP, myID, 0);

		RecvPacket(myID);
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
	case CS_PACKET_TYPE::CS_SERVER_LOGIN:
		{
			CS_Packet_Server_Login* packet = reinterpret_cast<CS_Packet_Server_Login*>(buf);

			//m_characterList[id]->SetChannel(packet->m_channel);
		}
	break;

	case CS_PACKET_TYPE::CS_CHANNEL_LOGIN:
		{
			CS_Packet_Channel_Login* packet = reinterpret_cast<CS_Packet_Channel_Login*>(buf);
			packet->m_channel;
		}
		break;

	case CS_PACKET_TYPE::CS_MOVE:
		{
			CS_Packet_Move* packet = reinterpret_cast<CS_Packet_Move*>(buf);
			m_characterList[id]->UpdatePosition(packet->m_direction);
			UpdateViewList(id);
		}
	break;

	default:
		break;
	}
}

void Core::ProcessLogin(unsigned char channel, int myID)
{
	// ���� ä�ο� ����� ������ �ִ��� ����
	m_channelList[channel]->ChannelMtxLock();
	// ä�ο� ��� �� �� �ִ��� üũ�ؾ���
	if (m_channelList[channel]->GetChannelUserSize() >= MAX_CHANNEL_USER)
	{
		m_channelList[channel]->ChannelMtxUnLock();
		SendChannelLoginFailPacket(myID);
		return;
	}

	// ä���� ������
	reinterpret_cast<Player*>(m_characterList[myID])->SetChannel(channel);
	m_channelList[channel]->AddPlayerInChannel(myID, m_characterList[myID]);
	m_channelList[channel]->ChannelMtxUnLock();
	SendChannelLoginOkPacket(myID);

	m_channelList[channel]->ProcessChannelLogin(myID);
}

void Core::UpdateViewList(int myID)
{
	unsigned char channel = m_characterList[myID]->GetChannel();

	// ä�ο� �ִ� ������Ʈ�� �þ߸� ������Ʈ ����
	m_channelList[channel]->UpdateObjectViewList(myID);
}

void Core::DisconnectServer(int id)
{
	m_channelList[id]->DisconnectChannel(id);

	Player* player = reinterpret_cast<Player*>(m_characterList[id]);
	player->ClearCharacterInfo();
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

void Core::SendServerLoginOkPacket(int to)
{
	SCPacket_Server_Login_Ok packet;
	packet.id = to;
	packet.size = sizeof(SCPacket_Server_Login_Ok);
	packet.type = SC_PACKET_TYPE::SC_SERVER_LOGIN_OK;

	SendPacket(to, reinterpret_cast<char*>(&packet));
}

void Core::SendServerLoginFailPacket(int to)
{
	SCPacket_Server_Login_Fail packet;
	packet.size = sizeof(SCPacket_Server_Login_Fail);
	packet.type = SC_PACKET_TYPE::SC_SERVER_LOGIN_FAIL;

	SendPacket(to, reinterpret_cast<char*>(&packet));
}

void Core::SendChannelLoginOkPacket(int to)
{
	SCPacket_Channel_Login_Ok packet;
	packet.id = to;
	packet.size = sizeof(SCPacket_Channel_Login_Ok);
	packet.type = SC_PACKET_TYPE::SC_CHANNEL_LOGIN_OK;

	SendPacket(to, reinterpret_cast<char*>(&packet));
}

void Core::SendChannelLoginFailPacket(int to)
{
	SCPacket_Channel_Login_Fail packet;
	packet.size = sizeof(SCPacket_Channel_Login_Fail);
	packet.type = SC_PACKET_TYPE::SC_CHANNEL_LOGIN_FAIL;

	SendPacket(to, reinterpret_cast<char*>(&packet));
}




