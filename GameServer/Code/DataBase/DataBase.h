#pragma once
#include "../../../MapleConvenienceFunction/Code/Macro.h"
#include "../../../MapleConvenienceFunction/Code/Defines.h"
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")

enum DB_TRANSACTION_TYPE
{
	UPDATE_PLAYER_STAUS_INFO,
	GET_PLAYER_INVENTORY_INFO
};

struct DBTransaction
{
	DBTransaction(DB_TRANSACTION_TYPE type, int id)
		: m_type(type), m_ID(id) {}

	DB_TRANSACTION_TYPE m_type;
	int m_ID;
};
constexpr int MAX_STRLEN = 50;

class DataBase
{
	SINGLE_TONE(DataBase)

public:
	bool Initialize();
	bool Connect();
	void Update();

	void ProcessDBTransaction(DBTransaction&);
	void AddDBTransactionQueue(DB_TRANSACTION_TYPE, int);
	
	bool GetInventoryInfo();

private:
	void ErrorDisplay(RETCODE);

	SQLHENV		m_Henv;
	SQLHDBC		m_Hdbc;
	SQLHSTMT	m_Hstmt;

	queue<DBTransaction> m_dbTransactionQueue;
	mutex m_dbTransactionQueueMtx;
};

