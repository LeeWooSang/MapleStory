#pragma once

#define	 SERVER_IP										"127.0.0.1"
constexpr unsigned short SERVER_PORT = 3500;
constexpr unsigned short MAX_BUFFER = 1024;

constexpr int MAX_USER = 1000;
constexpr int MAX_NPC = 1000;
constexpr int MAX_CHARACTER = MAX_USER + MAX_NPC;

// ¸Ê °¡·Î Å©±â
constexpr unsigned short	WORLD_WIDTH = 300;
// ¸Ê ¼¼·Î Å©±â
constexpr unsigned short	WORLD_HEIGHT = 300;

enum DIR_TYPE { UP, DOWN, LEFT, RIGHT };

enum CS_PACKET_TYPE
{
	CS_LOGIN,
	CS_MOVE,
	CS_ATTACK,
	CS_PICKUP_ITEM,
	CS_USE_ITEM,
	CS_LOGOUT,
	DCS_LOGIN
};

enum SC_PACKET_TYPE
{
	SC_LOGIN_OK,
	SC_LOGIN_FAIL,
	SC_POSITION,
	SC_REMOVE_OBJECT,
	SC_ADD_OBJECT,
};

#pragma pack(push, 1)
// Client To Server
struct CS_Packet_Move
{
	char	size;
	char	type;
	char	direction;
};

// Server To Client
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