#pragma once

#define	 SERVER_IP										"127.0.0.1"
constexpr unsigned short SERVER_PORT = 3500;
constexpr unsigned short MAX_BUFFER = 1024;

constexpr int MAX_CHANNEL = 10;

constexpr int MAX_USER = 1000;

constexpr int NPC_ID_START = 1000;
constexpr int MAX_NPC = 2000 * MAX_CHANNEL;

constexpr int MAX_CHARACTER = MAX_USER + MAX_NPC;

// ¸Ê °¡·Î Å©±â
constexpr unsigned short	WORLD_WIDTH = 300;
// ¸Ê ¼¼·Î Å©±â
constexpr unsigned short	WORLD_HEIGHT = 300;

enum DIR_TYPE { UP, DOWN, LEFT, RIGHT };

enum CS_PACKET_TYPE
{
	CS_SERVER_LOGIN,
	CS_CHANNEL_LOGIN,

	CS_MOVE,
	CS_ATTACK,
	CS_PICKUP_ITEM,
	CS_USE_ITEM,
	CS_LOGOUT,
	DCS_LOGIN
};

enum SC_PACKET_TYPE
{
	SC_SERVER_LOGIN_OK,
	SC_SERVER_LOGIN_FAIL,

	SC_CHANNEL_LOGIN_OK,
	SC_CHANNEL_LOGIN_FAIL,

	SC_POSITION,
	SC_REMOVE_OBJECT,
	SC_ADD_OBJECT,
};

#pragma pack(push, 1)
// Client To Server
struct CS_Packet_Server_Login
{
	char m_size;
	char m_type;
	char* m_ID[30];
};
struct CS_Packet_Channel_Login
{
	char m_size;
	char m_type;
	unsigned char m_channel;
};
struct CS_Packet_Move
{
	char	m_size;
	char	m_type;
	char	m_direction;
};

// Server To Client
struct SCPacket_Server_Login_Ok
{
	char size;
	char type;
	int id;
};
struct SCPacket_Server_Login_Fail
{
	char size;
	char type;
};
struct SCPacket_Channel_Login_Ok
{
	char size;
	char type;
	int id;
};
struct SCPacket_Channel_Login_Fail
{
	char size;
	char type;
};

struct SCPacket_Position
{
	char size;
	char type;
	int id;
	int x;
	int y;
};
struct SCPacket_Remove_Object
{
	char size;
	char type;
	int id;
};
struct SCPacket_Add_Object
{
	char size;
	char type;
	int id;
};
#pragma pack(pop)