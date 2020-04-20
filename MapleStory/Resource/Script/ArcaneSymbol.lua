g_TableSize = 6;

ArcaneSymbol_Table = {};

ArcaneSymbol_Table[0] =
{
	name = "아케인심볼 : 소멸의 여로";
	requestLevel = 200;
};

ArcaneSymbol_Table[1] =
{
	name = "아케인심볼 : 츄츄 아일랜드";
	requestLevel = 200;
};

ArcaneSymbol_Table[2] =
{
	name = "아케인심볼 : 레헬른";
	requestLevel = 200;
};

ArcaneSymbol_Table[3] =
{
	name = "아케인심볼 : 아르카나";
	requestLevel = 200;
};

ArcaneSymbol_Table[4] =
{
	name = "아케인심볼 : 모라스";
	requestLevel = 200;
};

ArcaneSymbol_Table[5] =
{
	name = "아케인심볼 : 에스페라";
	requestLevel = 200;
};

function GetArcaneSymbolInfo(id)
	API_GetArcaneSymbolInfo(ArcaneSymbol_Table[id].name, ArcaneSymbol_Table[id].requestLevel);
end


