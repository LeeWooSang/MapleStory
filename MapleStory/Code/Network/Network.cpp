#include "Network.h"
#include "../Core/Core.h"

INIT_INSTACNE(Network)
Network::Network()
	: m_Socket(0), m_inPacketSize(0), m_savedPacketSize(0)
{
	ZeroMemory(m_sendBuf, sizeof(char) * MAX_BUFFER);
	ZeroMemory(m_recvBuf, sizeof(char) * MAX_BUFFER);

	m_sendWsaBuf.buf = m_sendBuf;
	m_sendWsaBuf.len = MAX_BUFFER;
	m_recvWsaBuf.buf = m_recvBuf;
	m_recvWsaBuf.len = MAX_BUFFER;

	ZeroMemory(m_packetBuf, sizeof(char) * MAX_BUFFER);
}

Network::~Network()
{
	if(m_Socket != 0)
		closesocket(m_Socket);

	WSACleanup();

	cout << "Network - 소멸자" << endl;
}

bool Network::Initialize()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		WSACleanup();
		return false;
	}

	// socket()
	m_Socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}

	return true;
}

void Network::Connect()
{	
	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(SOCKADDR_IN));
	serveraddr.sin_family = AF_INET;
	//serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serveraddr.sin_addr.s_addr = inet_addr(m_serverIP.c_str());
	serveraddr.sin_port = htons(SERVER_PORT);

	int result = WSAConnect(m_Socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr), nullptr, nullptr, nullptr, nullptr);
	if (result == SOCKET_ERROR)
	{
		result = WSAGetLastError();
		cout << "Connect Error : " << result << endl;
		//m_ConnectState = CONNECT_STATE::FAIL;
		return;	
	}

	WSAAsyncSelect(m_Socket, GET_INSTANCE(Core)->GetHwnd(), WM_SOCKET, FD_CLOSE | FD_READ);

	cout << "서버 연결 성공!!" << endl;

	ServerLogin();
	//m_ConnectState = CONNECT_STATE::OK;
}

void Network::Recv()
{
	unsigned long iobyte, ioflag = 0;

	int result = WSARecv(m_Socket, &m_recvWsaBuf, 1, &iobyte, &ioflag, nullptr, nullptr);
	if (result)
	{
		result = WSAGetLastError();
		cout << "Recv Error - " << result << endl;
		return;
	}

	unsigned char* ptr = reinterpret_cast<unsigned char*>(m_recvBuf);

	while (iobyte != 0)
	{
		if (m_inPacketSize == 0)
			m_inPacketSize = ptr[0];

		if (iobyte + m_savedPacketSize >= m_inPacketSize)
		{
			memcpy(m_packetBuf + m_savedPacketSize, ptr, m_inPacketSize - m_savedPacketSize);

			// 패킷 처리
			ProcessPacket(m_packetBuf);

			ptr += m_inPacketSize - m_savedPacketSize;
			iobyte -= m_inPacketSize - m_savedPacketSize;
			m_inPacketSize = 0;
			m_savedPacketSize = 0;
		}

		else
		{
			memcpy(m_packetBuf + m_savedPacketSize, ptr, iobyte);
			m_savedPacketSize += iobyte;
			iobyte = 0;
		}
	}
}

void Network::Send()
{
	unsigned long iobyte = 0;
	WSASend(m_Socket, &m_sendWsaBuf, 1, &iobyte, 0, nullptr, nullptr);
}

void Network::ProcessPacket(char* buf)
{
	switch (buf[1])
	{
	case SC_PACKET_TYPE::SC_SERVER_LOGIN_OK:
		{
			SCPacket_Server_Login_Ok* packet = reinterpret_cast<SCPacket_Server_Login_Ok*>(buf);
			m_myID = packet->id;
			ChannelLogin();
		}
		break;

	case SC_PACKET_TYPE::SC_SERVER_LOGIN_FAIL:
		{
			SCPacket_Server_Login_Fail* packet = reinterpret_cast<SCPacket_Server_Login_Fail*>(buf);
			cout << "Login is fail" << endl;
			ServerLogin();
		}
		break;

	case SC_PACKET_TYPE::SC_CHANNEL_LOGIN_OK:
		cout << "Channel login Ok" << endl;
		break;

	case SC_PACKET_TYPE::SC_CHANNEL_LOGIN_FAIL:
		cout << "Channel login fail" << endl;
		ChannelLogin();
		break;

	case SC_ADD_OBJECT:
		{
			SCPacket_Add_Object* packet = reinterpret_cast<SCPacket_Add_Object*>(buf);
			int id = packet->id;
			break;
		}

	case SC_POSITION:
		{
			SCPacket_Position* packet = reinterpret_cast<SCPacket_Position*>(buf);
			int id = packet->id;
			break;
		}

	case SC_REMOVE_OBJECT:
		break;

	default:
		break;
	}
}

void Network::ProcessWindowMessage(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
	{
		::PostQuitMessage(0);
		return;
	}

	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		Recv();
		break;

	case FD_CLOSE:
		::PostQuitMessage(0);
		break;
	}
}

void Network::ServerLogin()
{
	string id;
	cout << "로그인 아이디 입력 : ";
	cin >> id;
	SendServerLoginPacket(const_cast<char*>(id.c_str()));
}

void Network::ChannelLogin()
{
	int channel;
	cout << "접속할 채널 입력(0 ~ 9) : ";
	cin >> channel;
	SendChannelLoginPacket(static_cast<char>(channel));
}

void Network::SendServerLoginPacket(char* id)
{
	CSPacket_Server_Login* packet = reinterpret_cast<CSPacket_Server_Login*>(m_sendBuf);
	packet->m_size = sizeof(CSPacket_Server_Login);
	packet->m_type = CS_PACKET_TYPE::CS_SERVER_LOGIN;
	strcpy(packet->m_ID, id);

	m_sendWsaBuf.len = sizeof(CSPacket_Server_Login);

	Send();
}

void Network::SendChannelLoginPacket(char channel)
{
	CSPacket_Channel_Login* packet = reinterpret_cast<CSPacket_Channel_Login*>(m_sendBuf);
	packet->m_size = sizeof(CSPacket_Channel_Login);
	packet->m_type = CS_PACKET_TYPE::CS_CHANNEL_LOGIN;
	packet->m_channel = channel;

	m_sendWsaBuf.len = sizeof(CSPacket_Channel_Login);

	Send();
}

void Network::SendMovePacket(char dir)
{
	CSPacket_Move* packet = reinterpret_cast<CSPacket_Move*>(m_sendBuf);
	packet->m_size = sizeof(CSPacket_Move);
	packet->m_type = CS_PACKET_TYPE::CS_MOVE;
	packet->m_direction = dir;
	
	m_sendWsaBuf.len = sizeof(CSPacket_Move);

	Send();
}

