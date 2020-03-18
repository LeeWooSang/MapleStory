#pragma once
#include "../Macro.h"
#include "../Defines.h"
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")
#pragma execution_character_set( "utf-8" )

constexpr int MAX_STRLEN = 50;

class DataBase
{
	SINGLE_TONE(DataBase)

public:
	bool Initialize();
	bool Connect();

	bool GetInventoryInfo();

private:
	void ErrorDisplay(RETCODE);

	SQLHENV		m_Henv;
	SQLHDBC		m_Hdbc;
	SQLHSTMT	m_Hstmt;
};

