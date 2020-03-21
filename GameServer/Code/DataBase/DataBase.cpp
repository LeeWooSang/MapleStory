#include "DataBase.h"
#include "../Core/Core.h"
#include "../GameObject/Character/Player/Player.h"

INIT_INSTACNE(DataBase)
DataBase::DataBase()
{
}

DataBase::~DataBase()
{
	SQLCancel(m_Hstmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_Hstmt);
	SQLDisconnect(m_Hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_Hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_Henv);
}

bool DataBase::Initialize()
{
	//setlocale(LC_ALL, "korean");
	//wcout.imbue(locale("korean"));

	SQLRETURN retcode;

	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_Henv);

	// Set the ODBC version environment attribute  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLSetEnvAttr(m_Henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);

		// Allocate connection handle  
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_Henv, &m_Hdbc);

			// Set login timeout to 5 seconds  
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				cout << "DB Initialize Complete!!" << endl;
				Connect();
			}

			else
			{
				ErrorDisplay(retcode);
				return false;
			}
		}

		else
		{
			ErrorDisplay(retcode);
			return false;
		}
	}

	else
	{
		ErrorDisplay(retcode);
		return false;
	}

	return true;
}

bool DataBase::Connect()
{
	SQLRETURN retcode;
	wstring odbc_dsn = L"MapleStory";

	SQLSetConnectAttr(m_Hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

	// Connect to data source  
	retcode = SQLConnect(m_Hdbc, (SQLWCHAR*)odbc_dsn.c_str(), SQL_NTS, nullptr, 0, nullptr, 0);

	// Allocate statement handle  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_Hdbc, &m_Hstmt);
		cout << "DB Connect Complete!!" << endl;
	}

	else
	{
		ErrorDisplay(retcode);
		cout << "DB Connect Fail!!" << endl;
		return false;
	}

	return true;
}

void DataBase::Update()
{
	while (true)
	{
		m_dbTransactionQueueMtx.lock();
		if (m_dbTransactionQueue.empty() == true)
		{
			m_dbTransactionQueueMtx.unlock();
			break;
		}
		// 큐에 가장 앞의 원소를 꺼냄
		DBTransaction transaction = m_dbTransactionQueue.front();
		m_dbTransactionQueue.pop();
		m_dbTransactionQueueMtx.unlock();

		ProcessDBTransaction(transaction);
	}
}

void DataBase::ProcessDBTransaction(DBTransaction& transaction)
{
	Player* player = reinterpret_cast<Player*>(GET_INSTANCE(Core)->GetPlayer(transaction.m_ID));

	switch (transaction.m_type)
	{
	case DB_TRANSACTION_TYPE::UPDATE_PLAYER_STAUS_INFO:
		cout << "Status of " << transaction.m_ID << " player update" << endl;
		break;

	case DB_TRANSACTION_TYPE::GET_PLAYER_INVENTORY_INFO:
		cout << "Inventory of " << transaction.m_ID << " player get" << endl;
		break;

	default:
		break;
	}
}

void DataBase::AddDBTransactionQueue(DB_TRANSACTION_TYPE type, int id)
{
	m_dbTransactionQueueMtx.lock();
	m_dbTransactionQueue.push(DBTransaction(type, id));
	m_dbTransactionQueueMtx.unlock();
}

bool DataBase::GetInventoryInfo()
{
	SQLRETURN retcode;

	SQLWCHAR name[MAX_STRLEN];
	SQLINTEGER length, level, size, exp;
	SQLLEN cbName = 0, cbLength= 0, cbLevel = 0, cbSize = 0, cbExp = 0;

	wstring ws = L"EXEC InventoryInfo ";

	retcode = SQLExecDirect(m_Hstmt, (SQLWCHAR*)ws.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLBindCol(m_Hstmt, 1, SQL_C_LONG, &length, 100, &cbLength);
		retcode = SQLBindCol(m_Hstmt, 2, SQL_C_CHAR, name, MAX_STRLEN, &cbName);
		retcode = SQLBindCol(m_Hstmt, 3, SQL_C_LONG, &level, 100, &cbLevel);
		retcode = SQLBindCol(m_Hstmt, 4, SQL_C_LONG, &size, 100, &cbSize);
		retcode = SQLBindCol(m_Hstmt, 5, SQL_C_LONG, &exp, 100, &cbExp);

		while (true)
		{
			retcode = SQLFetch(m_Hstmt);

			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				name[length] = '\0';
				string s = reinterpret_cast<char*>(name);
				cout << s << ", " << level << ", " << size << ", " << exp << endl;
			}
			
			else if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
			{
				ErrorDisplay(retcode);
				break;
			}

			else if (retcode == SQL_NO_DATA)
			{
				ErrorDisplay(retcode);
				SQLCloseCursor(m_Hstmt);
				return true;
			}
	
		}
	}
	else
		ErrorDisplay(retcode);

	SQLCloseCursor(m_Hstmt);

	return false;
}

void DataBase::ErrorDisplay(RETCODE RetCode)
{
	SQLSMALLINT iRec = 0;
	SQLINTEGER  iError;
	wchar_t       wszMessage[1000] = { 0, };
	wchar_t       wszState[SQL_SQLSTATE_SIZE + 1];

	if (RetCode == SQL_INVALID_HANDLE)
	{
		fwprintf(stderr, L"Invalid handle!\n");
		return;
	}

	while (SQLGetDiagRec(SQL_HANDLE_STMT, m_Hstmt, ++iRec, wszState, &iError, wszMessage, (SQLSMALLINT)(sizeof(wszMessage) / sizeof(wchar_t)), (SQLSMALLINT*)nullptr) == SQL_SUCCESS)
	{
		if (wcsncmp(wszState, L"01004", 5))
			fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
	}
}
