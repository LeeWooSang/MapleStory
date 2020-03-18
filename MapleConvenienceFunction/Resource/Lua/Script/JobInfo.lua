STR = 0x0001;
DEX = 0x0002;
INT = 0x0004;
LUK = 0x0008;
STR_DEX_LUK = 0x0010;
HP = 0x0020;

STR_UP	= 0x00000020;
DEX_UP	= 0x00000040;
INT_UP	= 0x00000080;
LUK_UP	= 0x00000100;
	
STR_DEX_LUK_UP = 0x00000200;

MAX_HP_PERCENT_UP = 0x00000400;
MAX_MP_PERCENT_UP = 0x00000800;
MAX_HP_UP = 0x00001000;
	
CRITICAL_UP = 0x00002000;
CRITICAL_DAMAGE_UP = 0x00004000;
	
BOSS_DAMAGE_UP = 0x00008000;
DEFENCE_IGNORE_UP = 0x00010000;

EXP_ACQUIRE_UP = 0x00020000;
MESO_ACQUIRE_UP = 0x00040000;

g_TableSize = 43;
Job_Table = {};

Job_Table[0] =
{
	occupationalCluster = "���谡";
	jobName = "�����";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[1] =
{
	occupationalCluster = "���谡";
	jobName = "�ȶ��";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[2] =
{
	occupationalCluster = "���谡";
	jobName = "������";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[3] =
{
	occupationalCluster = "���谡";
	jobName = "ĳ����";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[4] =
{
	occupationalCluster = "�ñ׳ʽ�";
	jobName = "��Ʈ����Ŀ";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[5] =
{
	occupationalCluster = "����";
	jobName = "�Ƶ�";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[6] =
{
	occupationalCluster = "����";
	jobName = "��ũ";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[7] =
{
	occupationalCluster = "���";
	jobName = "ī����";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[8] =
{
	occupationalCluster = "���谡";
	jobName = "���츶����";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[9] =
{
	occupationalCluster = "���谡";
	jobName = "�н����δ�";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[10] =
{
	occupationalCluster = "�ñ׳ʽ�";
	jobName = "����극��Ŀ";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[11] =
{
	occupationalCluster = "���";
	jobName = "������������";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[12] =
{
	occupationalCluster = "���谡";
	jobName = "��ũ������(��, ��)";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[13] =
{
	occupationalCluster = "���谡";
	jobName = "���";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[14] =
{
	occupationalCluster = "����������";
	jobName = "��Ʋ������";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[15] =
{
	occupationalCluster = "����";
	jobName = "��̳ʽ�";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[16] =
{
	occupationalCluster = "�ñ׳ʽ�";
	jobName = "�÷������ڵ�";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[17] =
{
	occupationalCluster = "���谡";
	jobName = "Ű�׽ý�";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[18] =
{
	occupationalCluster = "����";
	jobName = "�ϸ���";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[19] =
{
	occupationalCluster = "���谡";
	jobName = "�����̵�";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[20] =
{
	jobName = "������";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[21] =
{
	occupationalCluster = "�ñ׳ʽ�";
	jobName = "����Ʈ��Ŀ";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[22] =
{
	occupationalCluster = "���";
	jobName = "ī����";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[23] =
{
	occupationalCluster = "�ƴϸ�";
	jobName = "ȣ��";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[24] =
{
	occupationalCluster = "����������";
	jobName = "����";
	mainStat = STR_DEX_LUK;
	unionRaiderEffect = STR_DEX_LUK_UP;
};

Job_Table[25] =
{
	occupationalCluster = "���谡";
	jobName = "��ũ����Ʈ";
	mainStat = STR;
	unionRaiderEffect = MAX_HP_PERCENT_UP;
};

Job_Table[26] =
{
	occupationalCluster = "���谡";
	jobName = "��ũ������(��, ��)";
	mainStat = INT;
	unionRaiderEffect = MAX_MP_PERCENT_UP;
};

Job_Table[27] =
{
	occupationalCluster = "�ñ׳ʽ�";
	jobName = "������";
	mainStat = STR;
	unionRaiderEffect = MAX_HP_UP;
};

Job_Table[28] =
{
	occupationalCluster = "�ñ׳ʽ�";
	jobName = "�ҿ︶����";
	mainStat = STR;
	unionRaiderEffect = MAX_HP_UP;
};

Job_Table[29] =
{
	occupationalCluster = "���谡";
	jobName = "����Ʈ�ε�";
	mainStat = LUK;
	unionRaiderEffect = CRITICAL_UP;
};

Job_Table[30] =
{
	occupationalCluster = "���谡";
	jobName = "�ű�";
	mainStat = DEX;
	unionRaiderEffect = CRITICAL_UP;
};

Job_Table[31] =
{
	occupationalCluster = "���谡";
	jobName = "����";
	mainStat = STR;
	unionRaiderEffect = CRITICAL_DAMAGE_UP;
};

Job_Table[32] =
{
	occupationalCluster = "����������";
	jobName = "������";
	mainStat = HP;
	unionRaiderEffect = BOSS_DAMAGE_UP;
};

Job_Table[33] =
{
	occupationalCluster = "����������";
	jobName = "������";
	mainStat = STR;
	unionRaiderEffect = DEFENCE_IGNORE_UP;
};

Job_Table[34] =
{
	occupationalCluster = "�ʿ���";
	jobName = "����";
	mainStat = STR;
	unionRaiderEffect = EXP_ACQUIRE_UP;
};

Job_Table[35] =
{
	occupationalCluster = "����";
	jobName = "����";
	mainStat = LUK;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[36] =
{
	occupationalCluster = "����������";
	jobName = "���󽽷��̾�";
	mainStat = STR;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[37] =
{
	occupationalCluster = "����";
	jobName = "�ƶ�";
	mainStat = STR;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[38] =
{
	occupationalCluster = "����";
	jobName = "����";
	mainStat = INT;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[39] =
{
	occupationalCluster = "���谡";
	jobName = "ĸƾ";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[40] =
{
	occupationalCluster = "����";
	jobName = "�޸�������";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[41] =
{
	occupationalCluster = "����������";
	jobName = "���ϵ�����";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[42] =
{
	occupationalCluster = "����������";
	jobName = "��ī��";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

function GetJobInfo(id)
	API_GetJobInfo(Job_Table[id].occupationalCluster, Job_Table[id].jobName, Job_Table[id].mainStat, Job_Table[id].unionRaiderEffect);
end
