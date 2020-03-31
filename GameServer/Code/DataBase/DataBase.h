#pragma once
#include "../../../MapleStory/Code/Macro.h"
#include "../Defines.h"
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")

enum DB_TRANSACTION_TYPE
{
	GET_PLAYER_STATUS_INFO,
	GET_PLAYER_INVENTORY_INFO,

	UPDATE_PLAYER_STATUS_INFO,

	PLAYER_LOGIN,
	PLAYER_LOGOUT
};

struct DBTransaction
{
	DBTransaction(DB_TRANSACTION_TYPE type, int id)
		: m_type(type), m_ID(id) {}

	DB_TRANSACTION_TYPE m_type;
	int m_ID;
};
constexpr int MAX_STRLEN = 50;

class Player;
class DataBase
{
	SINGLE_TONE(DataBase)

public:
	bool Initialize();
	bool Connect();
	void Update();

	void ProcessDBTransaction(DBTransaction&);
	void AddDBTransactionQueue(DB_TRANSACTION_TYPE, int);

	template <typename T>
	const wstring& MakeStoredProcedure(wstring&, T, bool);
	const wstring& MakeStoredProcedure(wstring&, const string&, bool);

	bool GetPlayerStatusInfo(Player*);
	bool GetPlayerInventoryInfo(Player*);
	bool UpdatePlayerStatusInfo(Player*);

	int PlayerLogin(Player*);
	bool CheckPlayerLoginID(Player*);
	bool CheckPlayerLoginPW(Player*);

	bool PlayerLogout(Player*);

private:
	void ErrorDisplay(RETCODE);

	SQLHENV		m_Henv;
	SQLHDBC		m_Hdbc;
	SQLHSTMT	m_Hstmt;

	queue<DBTransaction> m_dbTransactionQueue;
	mutex m_dbTransactionQueueMtx;
};


