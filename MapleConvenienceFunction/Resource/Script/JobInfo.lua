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
	occupationalCluster = "모험가";
	jobName = "히어로";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[1] =
{
	occupationalCluster = "모험가";
	jobName = "팔라딘";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[2] =
{
	occupationalCluster = "모험가";
	jobName = "바이퍼";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[3] =
{
	occupationalCluster = "모험가";
	jobName = "캐논슈터";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[4] =
{
	occupationalCluster = "시그너스";
	jobName = "스트라이커";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[5] =
{
	occupationalCluster = "레프";
	jobName = "아델";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[6] =
{
	occupationalCluster = "레프";
	jobName = "아크";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[7] =
{
	occupationalCluster = "노바";
	jobName = "카이저";
	mainStat = STR;
	unionRaiderEffect = STR_UP;
};

Job_Table[8] =
{
	occupationalCluster = "모험가";
	jobName = "보우마스터";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[9] =
{
	occupationalCluster = "모험가";
	jobName = "패스파인더";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[10] =
{
	occupationalCluster = "시그너스";
	jobName = "윈드브레이커";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[11] =
{
	occupationalCluster = "노바";
	jobName = "엔젤릭버스터";
	mainStat = DEX;
	unionRaiderEffect = DEX_UP;
};

Job_Table[12] =
{
	occupationalCluster = "모험가";
	jobName = "아크메이지(썬, 콜)";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[13] =
{
	occupationalCluster = "모험가";
	jobName = "비숍";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[14] =
{
	occupationalCluster = "레지스탕스";
	jobName = "배틀메이지";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[15] =
{
	occupationalCluster = "영웅";
	jobName = "루미너스";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[16] =
{
	occupationalCluster = "시그너스";
	jobName = "플레임위자드";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[17] =
{
	occupationalCluster = "모험가";
	jobName = "키네시스";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[18] =
{
	occupationalCluster = "레프";
	jobName = "일리움";
	mainStat = INT;
	unionRaiderEffect = INT_UP;
};

Job_Table[19] =
{
	occupationalCluster = "모험가";
	jobName = "듀얼블레이드";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[20] =
{
	occupationalCluster = "모험가";
	jobName = "섀도어";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[21] =
{
	occupationalCluster = "시그너스";
	jobName = "나이트워커";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[22] =
{
	occupationalCluster = "노바";
	jobName = "카데나";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[23] =
{
	occupationalCluster = "아니마";
	jobName = "호영";
	mainStat = LUK;
	unionRaiderEffect = LUK_UP;
};

Job_Table[24] =
{
	occupationalCluster = "레지스탕스";
	jobName = "제논";
	mainStat = STR_DEX_LUK;
	unionRaiderEffect = STR_DEX_LUK_UP;
};

Job_Table[25] =
{
	occupationalCluster = "모험가";
	jobName = "다크나이트";
	mainStat = STR;
	unionRaiderEffect = MAX_HP_PERCENT_UP;
};

Job_Table[26] =
{
	occupationalCluster = "모험가";
	jobName = "아크메이지(불, 독)";
	mainStat = INT;
	unionRaiderEffect = MAX_MP_PERCENT_UP;
};

Job_Table[27] =
{
	occupationalCluster = "시그너스";
	jobName = "미하일";
	mainStat = STR;
	unionRaiderEffect = MAX_HP_UP;
};

Job_Table[28] =
{
	occupationalCluster = "시그너스";
	jobName = "소울마스터";
	mainStat = STR;
	unionRaiderEffect = MAX_HP_UP;
};

Job_Table[29] =
{
	occupationalCluster = "모험가";
	jobName = "나이트로드";
	mainStat = LUK;
	unionRaiderEffect = CRITICAL_UP;
};

Job_Table[30] =
{
	occupationalCluster = "모험가";
	jobName = "신궁";
	mainStat = DEX;
	unionRaiderEffect = CRITICAL_UP;
};

Job_Table[31] =
{
	occupationalCluster = "모험가";
	jobName = "은월";
	mainStat = STR;
	unionRaiderEffect = CRITICAL_DAMAGE_UP;
};

Job_Table[32] =
{
	occupationalCluster = "레지스탕스";
	jobName = "데몬어벤져";
	mainStat = HP;
	unionRaiderEffect = BOSS_DAMAGE_UP;
};

Job_Table[33] =
{
	occupationalCluster = "레지스탕스";
	jobName = "블래스터";
	mainStat = STR;
	unionRaiderEffect = DEFENCE_IGNORE_UP;
};

Job_Table[34] =
{
	occupationalCluster = "초월자";
	jobName = "제로";
	mainStat = STR;
	unionRaiderEffect = EXP_ACQUIRE_UP;
};

Job_Table[35] =
{
	occupationalCluster = "영웅";
	jobName = "팬텀";
	mainStat = LUK;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[36] =
{
	occupationalCluster = "레지스탕스";
	jobName = "데몬슬레이어";
	mainStat = STR;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[37] =
{
	occupationalCluster = "영웅";
	jobName = "아란";
	mainStat = STR;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[38] =
{
	occupationalCluster = "영웅";
	jobName = "에반";
	mainStat = INT;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[39] =
{
	occupationalCluster = "모험가";
	jobName = "캡틴";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[40] =
{
	occupationalCluster = "영웅";
	jobName = "메르세데스";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[41] =
{
	occupationalCluster = "레지스탕스";
	jobName = "와일드헌터";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

Job_Table[42] =
{
	occupationalCluster = "레지스탕스";
	jobName = "메카닉";
	mainStat = DEX;
	unionRaiderEffect = MESO_ACQUIRE_UP;
};

function GetJobInfo(id)
	API_GetJobInfo(Job_Table[id].occupationalCluster, Job_Table[id].jobName, Job_Table[id].mainStat, Job_Table[id].unionRaiderEffect);
end
