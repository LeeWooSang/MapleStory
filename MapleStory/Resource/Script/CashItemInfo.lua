g_TableSize = 5;

CashItem_Table = {};

CashItem_Table[0] =
{
	name = "���� ����Ľ���";
	price = 10800;
	size = 12;
};

CashItem_Table[1] =
{
	name = "�� ����Ľ���";
	price = 19800;
	size = 12;
};

CashItem_Table[2] =
{
	name = "��� ����ų� ť�� ��Ʈ";
	price = 18900;
	size = 10;
};

CashItem_Table[3] =
{
	name = "������ �ξ� ��Ÿ��";
	price = 2200;
	size = 1;
};

CashItem_Table[4] =
{
	name = "������ �ξ� ��Ÿ��(����)";
	price = 99000;
	size = 45;
};

function GetCashItem(id)
	API_GetCashItem(CashItem_Table[id].name, CashItem_Table[id].price, CashItem_Table[id].size);
end
