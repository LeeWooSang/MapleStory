#include "DataBase.h"
#include "../Core/Core.h"
#include "../GameObject/Character/Player/Player.h"
#include "../../Code/GameObject/Status/PlayerStatus/PlayerStatus.h"

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
		cout << "DB_Queue size : " << m_dbTransactionQueue.size() << endl;
		m_dbTransactionQueueMtx.unlock();

		ProcessDBTransaction(transaction);
	}
}

void DataBase::ProcessDBTransaction(DBTransaction& transaction)
{
	Player* player = reinterpret_cast<Player*>(GET_INSTANCE(Core)->GetPlayer(transaction.m_ID));

	switch (transaction.m_type)
	{
	case DB_TRANSACTION_TYPE::GET_PLAYER_STATUS_INFO:
		GetPlayerStatusInfo(player);
		break;

	case DB_TRANSACTION_TYPE::GET_PLAYER_INVENTORY_INFO:
		cout << "Inventory of " << transaction.m_ID << " player get" << endl;
		break;

	case DB_TRANSACTION_TYPE::UPDATE_PLAYER_STATUS_INFO:
		UpdatePlayerStatusInfo(player);
		cout << "Status of " << transaction.m_ID << " player update" << endl;
		break;

	case DB_TRANSACTION_TYPE::PLAYER_LOGIN:
		{
			int isLoginOk = PlayerLogin(player);
			OverEx* overEx = new OverEx;
			overEx->myID = transaction.m_ID;

			if(isLoginOk == NOTICE_TYPE::CORRECT)
				overEx->eventType = Core::EVENT_TYPE::PLAYER_LOGIN_OK;

			else if(isLoginOk == NOTICE_TYPE::ID_NOT_CORRECT)
				overEx->eventType = Core::EVENT_TYPE::PLAYER_LOGIN_ID_FAIL;

			else
				overEx->eventType = Core::EVENT_TYPE::PLAYER_LOGIN_PW_FAIL;

			PostQueuedCompletionStatus(GET_INSTANCE(Core)->GetIOCPHandle(), 1, transaction.m_ID, &overEx->overlapped);
		}
		break;

	case DB_TRANSACTION_TYPE::PLAYER_LOGOUT:
		PlayerLogout(player);
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

template <typename T>
const wstring& DataBase::MakeStoredProcedure(wstring& functionName, T a, bool isBegin)
{
	wchar_t temp[MAX_STRLEN] = { 0, };

	string name = typeid(T).name();
	if (name == "short" || name == "int" || name == "__int64")
	{
		wcscpy(temp, const_cast<wchar_t*>(to_wstring(a).c_str()));
	}

	if (isBegin == true)
		functionName += L" ";
	else
		functionName += L", ";

	functionName += temp;

	return functionName;
}

const wstring& DataBase::MakeStoredProcedure(wstring& functionName, const string& a, bool isBegin)
{
	wchar_t temp[MAX_STRLEN] = { 0, };
	
	mbstowcs(temp, const_cast<char*>(a.c_str()), a.length());

	if (isBegin == true)
		functionName += L" ";
	else
		functionName += L", ";

	functionName += temp;

	return functionName;
}

bool DataBase::GetPlayerStatusInfo(Player* player)
{
	PlayerStatus* stat = reinterpret_cast<PlayerStatus*>(player->GetStatus());

	//string name = "이우상";
	//wstring wname = L"";
	//mbstowcs(const_cast<wchar_t*>(wname.c_str()), const_cast<char*>(name.c_str()), name.length());

	string name = "이우상";
	wchar_t wname[50] = { 0, };
	mbstowcs(wname, const_cast<char*>(name.c_str()), name.length());

	wstring ws = L"EXEC GetPlayerStatusInfo ";
	ws += wname;

	SQLRETURN retcode;

	short level = 0;
	__int64 exp = 0;
	wchar_t jobName[MAX_STRLEN];
	SQLINTEGER HP, MP, STR, DEX, INT, LUK;
	SQLLEN cbLevel = 0, cbExp = 0, cbHP = 0, cbMP = 0, cbSTR = 0, cbDEX = 0, cbINT = 0, cbLUK = 0, cbJobName = 0;

	retcode = SQLExecDirect(m_Hstmt, (SQLWCHAR*)ws.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLBindCol(m_Hstmt, 1, SQL_SMALLINT, &level, 0, &cbLevel);
		retcode = SQLBindCol(m_Hstmt, 2, SQL_C_SBIGINT, &exp, 0, &cbExp);
		retcode = SQLBindCol(m_Hstmt, 3, SQL_C_LONG, &HP, 0, &cbHP);
		retcode = SQLBindCol(m_Hstmt, 4, SQL_C_LONG, &MP, 0, &cbMP);
		retcode = SQLBindCol(m_Hstmt, 5, SQL_C_LONG, &STR, 0, &cbSTR);
		retcode = SQLBindCol(m_Hstmt, 6, SQL_C_LONG, &DEX, 0, &cbDEX);
		retcode = SQLBindCol(m_Hstmt, 7, SQL_C_LONG, &INT, 0, &cbINT);
		retcode = SQLBindCol(m_Hstmt, 8, SQL_C_LONG, &LUK, 0, &cbLUK);
		retcode = SQLBindCol(m_Hstmt, 9, SQL_C_CHAR, &jobName, MAX_STRLEN, &cbJobName);

		while (true)
		{
			retcode = SQLFetch(m_Hstmt);

			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				stat->SetDBdataToPlayerStatus(level, exp, HP, MP, STR, DEX, INT, LUK);
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

bool DataBase::GetPlayerInventoryInfo(Player* player)
{
	string name = player->GetName();
	wstring wname = L"";
	mbstowcs(const_cast<wchar_t*>(wname.c_str()), const_cast<char*>(name.c_str()), name.length());

	wstring ws = L"EXEC GetPlayerInventoryInfo " + wname;

	SQLWCHAR itemName[MAX_STRLEN];
	SQLINTEGER length, level, size, exp;
	SQLLEN cbItemName = 0, cbLength= 0, cbLevel = 0, cbSize = 0, cbExp = 0;

	SQLRETURN retcode = SQLExecDirect(m_Hstmt, (SQLWCHAR*)ws.c_str(), SQL_NTS);

	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLBindCol(m_Hstmt, 1, SQL_C_LONG, &length, 100, &cbLength);
		retcode = SQLBindCol(m_Hstmt, 2, SQL_C_CHAR, itemName, MAX_STRLEN, &cbItemName);
		retcode = SQLBindCol(m_Hstmt, 3, SQL_C_LONG, &level, 100, &cbLevel);
		retcode = SQLBindCol(m_Hstmt, 4, SQL_C_LONG, &size, 100, &cbSize);
		retcode = SQLBindCol(m_Hstmt, 5, SQL_C_LONG, &exp, 100, &cbExp);

		while (true)
		{
			retcode = SQLFetch(m_Hstmt);

			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				name[length] = '\0';
				string s = reinterpret_cast<char*>(itemName);
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

bool DataBase::UpdatePlayerStatusInfo(Player* player)
{
	string name = player->GetName();
	wchar_t wname[50] = { 0, };
	mbstowcs(wname, const_cast<char*>(name.c_str()), name.length());
	PlayerStatus* stat = reinterpret_cast<PlayerStatus*>(player->GetStatus());

	wstring ws = L"EXEC UpdatePlayerStatusInfo";

	MakeStoredProcedure(ws, name, true);
	MakeStoredProcedure(ws, stat->GetLevel(), false);
	MakeStoredProcedure(ws, stat->GetExp(), false);
	MakeStoredProcedure(ws, stat->GetHP(), false);
	MakeStoredProcedure(ws, stat->GetMP(), false);
	MakeStoredProcedure(ws, stat->GetSTR(), false);
	MakeStoredProcedure(ws, stat->GetDEX(), false);
	MakeStoredProcedure(ws, stat->GetINT(), false);
	MakeStoredProcedure(ws, stat->GetLUK(), false);

	SQLRETURN retcode = SQLExecDirect(m_Hstmt, (SQLWCHAR *)ws.c_str(), SQL_NTS);
	if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
	{
		ErrorDisplay(retcode);
		SQLCloseCursor(m_Hstmt);
		return false;
	}

	SQLCloseCursor(m_Hstmt);
	return true;
}

int DataBase::PlayerLogin(Player* player)
{
	if (CheckPlayerLoginID(player) == false)
		return NOTICE_TYPE::ID_NOT_CORRECT;

	if (CheckPlayerLoginPW(player) == false)
		return NOTICE_TYPE::PW_NOT_CORRECT;

	return NOTICE_TYPE::CORRECT;
}

bool DataBase::CheckPlayerLoginID(Player* player)
{
	string id = player->GetLoginID();
	string pw = player->GetPassword();

	wstring ws = L"EXEC CheckPlayerLoginID";
	MakeStoredProcedure(ws, id, true);

	SQLWCHAR loginID[MAX_STRLEN];
	SQLINTEGER length;
	SQLLEN cbLength = 0, cbLoginID = 0;

	SQLRETURN retcode = SQLExecDirect(m_Hstmt, (SQLWCHAR*)ws.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLBindCol(m_Hstmt, 1, SQL_C_LONG, &length, 0, &cbLength);
		retcode = SQLBindCol(m_Hstmt, 2, SQL_C_CHAR, &loginID, MAX_STRLEN, &cbLoginID);

		retcode = SQLFetch(m_Hstmt);

		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			loginID[length] = '\0';
			player->SetLoginID(reinterpret_cast<char*>(loginID));
			SQLCloseCursor(m_Hstmt);
			return true;
		}

		else if (retcode == SQL_NO_DATA)
			cout << "ID of Player is not correct" << endl;

		else if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
			ErrorDisplay(retcode);
	}
	else
		ErrorDisplay(retcode);

	SQLCloseCursor(m_Hstmt);
	return false;
}

bool DataBase::CheckPlayerLoginPW(Player* player)
{
	string id = player->GetLoginID();
	string pw = player->GetPassword();

	wstring ws = L"EXEC CheckPlayerLoginPW";
	MakeStoredProcedure(ws, id, true);
	MakeStoredProcedure(ws, pw, false);

	SQLWCHAR loginID[MAX_STRLEN];
	SQLINTEGER length;
	SQLLEN cbLength = 0, cbLoginID = 0;

	SQLRETURN retcode = SQLExecDirect(m_Hstmt, (SQLWCHAR*)ws.c_str(), SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLBindCol(m_Hstmt, 1, SQL_C_LONG, &length, 0, &cbLength);
		retcode = SQLBindCol(m_Hstmt, 2, SQL_C_CHAR, &loginID, MAX_STRLEN, &cbLoginID);

		retcode = SQLFetch(m_Hstmt);

		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			loginID[length] = '\0';
			player->SetLoginID(reinterpret_cast<char*>(loginID));
			SQLCloseCursor(m_Hstmt);
			return true;
		}

		else if (retcode == SQL_NO_DATA)
			cout << "Password of Player is not correct" << endl;

		else if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
			ErrorDisplay(retcode);
	}
	else
		ErrorDisplay(retcode);

	SQLCloseCursor(m_Hstmt);
	return false;
}

bool DataBase::PlayerLogout(Player* player)
{
	string name = player->GetName();
	wstring wname = L"";
	mbstowcs(const_cast<wchar_t*>(wname.c_str()), const_cast<char*>(name.c_str()), name.length());

	wstring ws = L"EXEC PlayerLogout " + wname;

	player->ClearObjectInfo();

	return true;
}

void DataBase::ErrorDisplay(RETCODE retCode)
{
	SQLSMALLINT iRec = 0;
	SQLINTEGER  iError;
	wchar_t       wszMessage[1000] = { 0, };
	wchar_t       wszState[SQL_SQLSTATE_SIZE + 1];

	if (retCode == SQL_INVALID_HANDLE)
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
