g_TableSize = 5;

CashItem_Table = {};

CashItem_Table[0] =
{
	name = "레드 더블식스팩";
	price = 10800;
	size = 12;
};

CashItem_Table[1] =
{
	name = "블랙 더블식스팩";
	price = 19800;
	size = 12;
};

CashItem_Table[2] =
{
	name = "골드 에디셔널 큐브 세트";
	price = 18900;
	size = 10;
};

CashItem_Table[3] =
{
	name = "메이플 로얄 스타일";
	price = 2200;
	size = 1;
};

CashItem_Table[4] =
{
	name = "메이플 로얄 스타일(묶음)";
	price = 99000;
	size = 45;
};

function GetCashItem(id)
	API_GetCashItem(CashItem_Table[id].name, CashItem_Table[id].price, CashItem_Table[id].size);
end
