#pragma once
#include "../Character.h"

class Player : public Character
{
public:
	Player(const string&);
	virtual ~Player();

	virtual bool Initialize(void*);
	virtual void Update();
	virtual void ClearObjectInfo();

	const string& GetLoginID()	const { return m_loginID; }
	void SetLoginID(const string& id) { m_loginID = id; }

	const SOCKET& GetSocket()	const { return m_socket; }
	void SetSocket(const SOCKET& socket) { m_socket = socket; }

	char* GetPacketBuf() { return m_packetBuf; }

	int GetPrevSize()	const { return m_prevSize; }
	void SetPrevSize(int size) { m_prevSize = size; }

	void SetSendBytes(int bytes) { m_sendBytes = bytes; }

	bool GetIsConnected()	const { return m_isConnected; }
	void SetIsConnected(bool isConnected) { m_isConnected = isConnected; }

	class Inventory* GetInventory()		const { return m_inventory; }

private:
	struct UnionCharaterInfo* m_myCharacter;

	class Union* m_uni;
	class Inventory* m_inventory;

	string m_loginID;
	SOCKET m_socket;
	char m_packetBuf[MAX_BUFFER];
	int	 m_prevSize;
	int	 m_sendBytes;
	bool m_isConnected;
};

