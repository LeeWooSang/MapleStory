#pragma once
#include "../Macro.h"
#include "../Defines.h"
#include "../../../GameServer/Code/Protocol.h"

class Network
{
	SINGLE_TONE(Network)

	bool Initialize();
	void Connect();
	void Recv();
	void Send();
	void ProcessPacket(char*);
	void ProcessWindowMessage(WPARAM, LPARAM);

	void ServerLogin();
	void ChannelLogin();

	void SetMyID(int id) { m_myID = id; }
	int GetMyID()	const { return m_myID; }

	void SendServerLoginPacket(char*);
	void SendChannelLoginPacket(char);
	void SendMovePacket(char);
private:
	SOCKET m_Socket;

	WSABUF	m_sendWsaBuf;
	char 	m_sendBuf[MAX_BUFFER];
	WSABUF	m_recvWsaBuf;
	char	m_recvBuf[MAX_BUFFER];

	char	m_packetBuf[MAX_BUFFER];
	unsigned long	m_inPacketSize;
	unsigned long	m_savedPacketSize;

	int m_myID;
};