g_TableSize = 6;

ArcaneSymbol_Table = {};

ArcaneSymbol_Table[0] =
{
	name = "�����νɺ� : �Ҹ��� ����";
	requestLevel = 200;
};

ArcaneSymbol_Table[1] =
{
	name = "�����νɺ� : ���� ���Ϸ���";
	requestLevel = 200;
};

ArcaneSymbol_Table[2] =
{
	name = "�����νɺ� : ���︥";
	requestLevel = 200;
};

ArcaneSymbol_Table[3] =
{
	name = "�����νɺ� : �Ƹ�ī��";
	requestLevel = 200;
};

ArcaneSymbol_Table[4] =
{
	name = "�����νɺ� : ���";
	requestLevel = 200;
};

ArcaneSymbol_Table[5] =
{
	name = "�����νɺ� : �������";
	requestLevel = 200;
};

function GetArcaneSymbolInfo(id)
	API_GetArcaneSymbolInfo(ArcaneSymbol_Table[id].name, ArcaneSymbol_Table[id].requestLevel);
end


