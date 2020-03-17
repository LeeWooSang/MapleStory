#include "Resource.h"
#include "../GameObject/Job/Job.h"
#include "../Script/Script.h"

INIT_INSTACNE(Resource)
Resource::Resource()
{
	m_cashItemInfoList.clear();
	m_jobInfoList.clear();
	m_characterInfoList.clear();
	m_unionRaiderEffectList.clear();
}

Resource::~Resource()
{
	SAFE_DELETE_LIST(m_cashItemInfoList);
	
	m_jobInfoList.clear();
	m_characterInfoList.clear();
	m_unionRaiderEffectList.clear();
}

bool Resource::Initialize()
{
	if (LoadItemInfo() == false)
		return false;

	if (LoadJobInfo() == false)
		return false;

	if (LoadCharacterInfo() == false)
		return false;

	if (LoadUnionRaiderEffectInfo() == false)
		return false;

	return true;
}

bool Resource::LoadItemInfo()
{
	/*ifstream in("../Resource/ItemInfo.txt");
	if (!in)
	{
		cout << "아이템 정보 파일이 존재하지 않습니다." << endl;
		return false;
	}

	string name = "";
	int cash = 0;

	while (in >> name >> cash)
		m_itemInfoList.emplace_back(new ItemInfo(name, cash));

	in.close();*/

	Script* cashItemScript = new Script;
	if (cashItemScript->Initialize() == false)
	{
		delete cashItemScript;
		return false;
	}

	delete cashItemScript;

	cout << "아이템 정보 파일 로딩 완료" << endl;
	return true;
}

bool Resource::SaveItemInfo()
{
	ofstream out("../Resource/ItemInfo.txt");
	//for (auto data : m_itemList)
	//	out << data->GetName() << '\t' << data->GetCash() << endl;

	out.close();

	cout << "아이템 정보 파일 출력 완료" << endl;
	return true;
}

bool Resource::LoadJobInfo()
{
	ifstream in("../Resource/JobInfo.txt");
	if (!in)
	{
		cout << "직업 정보 파일이 존재하지 않습니다." << endl;
		return false;
	}

	string name = "";
	int mainStat = 0;

	while (in >> name >> mainStat)
		m_jobInfoList.emplace(name, mainStat);

	in.close();

	cout << "직업 정보 파일 로딩 완료" << endl;

	return true;
}

bool Resource::SaveJobInfo()
{
	ofstream out("../Resource/JobInfo.txt");

	int STR = 0x0001;
	int DEX = 0x0002;
	int INT = 0x0004;
	int LUK = 0x0008;
	int STR_DEX_LUK = 0x0010;
	int HP = 0x0020;

	m_jobInfoList.emplace("히어로", STR);
	m_jobInfoList.emplace("팔라딘", STR);
	m_jobInfoList.emplace("다크나이트", STR);
	m_jobInfoList.emplace("바이퍼", STR);
	m_jobInfoList.emplace("캐논슈터", STR);
	m_jobInfoList.emplace("소울마스터", STR);
	m_jobInfoList.emplace("미하일", STR);
	m_jobInfoList.emplace("스트라이커", STR);
	m_jobInfoList.emplace("블래스터", STR);
	m_jobInfoList.emplace("데몬슬레이어", STR);
	m_jobInfoList.emplace("아란", STR);
	m_jobInfoList.emplace("은월", STR);
	m_jobInfoList.emplace("카이저", STR);
	m_jobInfoList.emplace("제로", STR);
	m_jobInfoList.emplace("아델", STR);
	m_jobInfoList.emplace("아크", STR);

	m_jobInfoList.emplace("보우마스터", DEX);
	m_jobInfoList.emplace("신궁", DEX);
	m_jobInfoList.emplace("패스파인더", DEX);
	m_jobInfoList.emplace("캡틴", DEX);
	m_jobInfoList.emplace("윈드브레이커", DEX);
	m_jobInfoList.emplace("와일드헌터", DEX);
	m_jobInfoList.emplace("메카닉", DEX);
	m_jobInfoList.emplace("메르세데스", DEX);
	m_jobInfoList.emplace("엔젤릭버스터", DEX);

	m_jobInfoList.emplace("썬콜", INT);
	m_jobInfoList.emplace("불독", INT);
	m_jobInfoList.emplace("비숍", INT);
	m_jobInfoList.emplace("플레임위자드", INT);
	m_jobInfoList.emplace("배틀메이지", INT);
	m_jobInfoList.emplace("에반", INT);
	m_jobInfoList.emplace("루미너스", INT);
	m_jobInfoList.emplace("키네시스", INT);
	m_jobInfoList.emplace("일리움", INT);

	m_jobInfoList.emplace("나이트로드", LUK);
	m_jobInfoList.emplace("섀도어", LUK);
	m_jobInfoList.emplace("듀얼블레이드", LUK);
	m_jobInfoList.emplace("나이트워커", LUK);
	m_jobInfoList.emplace("팬텀", LUK);
	m_jobInfoList.emplace("카데나", LUK);
	m_jobInfoList.emplace("호영", LUK);

	m_jobInfoList.emplace("제논", STR_DEX_LUK);
	m_jobInfoList.emplace("데몬어벤져", HP);

	for (auto data : m_jobInfoList)
		out << data.first << '\t' << static_cast<int>(data.second) << endl;

	out.close();

	cout << "직업 정보 파일 출력 완료" << endl;

	return true;
}

bool Resource::LoadCharacterInfo()
{
	ifstream in("../Resource/CharacterInfo.txt");
	if (!in)
	{
		cout << "캐릭터 정보 파일이 존재하지 않습니다." << endl;
		return false;
	}

	string nickName = "";
	string jobName = "";
	int level = 0;

	while (in >> nickName >> jobName >> level)
		m_characterInfoList.emplace(nickName, CharacterInfo(jobName, level));

	in.close();

	cout << "캐릭터 정보 파일 로딩 완료" << endl;

	return true;
}

bool Resource::SaveCharacterInfo()
{
	ofstream out("../Resource/CharacterInfo.txt");

	m_characterInfoList.emplace("창원기전", CharacterInfo("히어로", 237));
	m_characterInfoList.emplace("씽즌", CharacterInfo("팔라딘", 211));
	m_characterInfoList.emplace("빙설각", CharacterInfo("팬텀", 200));
	m_characterInfoList.emplace("우가돈촌", CharacterInfo("데몬어벤져", 200));
	m_characterInfoList.emplace("카르페디엠YJ", CharacterInfo("나이트로드", 200));
	m_characterInfoList.emplace("프랭크D루나", CharacterInfo("엔젤릭버스터", 200));
	m_characterInfoList.emplace("비주얼2017", CharacterInfo("썬콜", 200));
	m_characterInfoList.emplace("HANS케익", CharacterInfo("제로", 200));
	
	for (auto data : m_characterInfoList)
		out << data.first << '\t' << data.second.m_jobName << '\t' << static_cast<int>(data.second.m_level) << endl;

	out.close();

	cout << "캐릭터 정보 파일 출력 완료" << endl;

	return true;
}

bool Resource::LoadUnionRaiderEffectInfo()
{
	ifstream in("../Resource/UnionRaiderEffectInfo.txt");
	if (!in)
	{
		cout << "유니온 공격대원 효과 정보 파일이 존재하지 않습니다." << endl;
		return false;
	}

	string name = "";
	int effect = 0;
	while (in >> name >> effect)
		m_unionRaiderEffectList.emplace(name, effect);

	in.close();

	cout << "유니온 공격대원 효과 정보 파일 로딩 완료" << endl;

	return true;
}

bool Resource::SaveUnionRaiderEffectInfo()
{
	ofstream out("../Resource/UnionRaiderEffectInfo.txt", ios::app);

	int STR = 0x0020;
	int DEX = 0x0040;
	int INT = 0x0080;
	int LUK = 0x0100;
	int tempSTR_DEX_LUK = 0x00000200;
	int tempMax_HP_Percent = 0x00000400;
	int tempMax_MP_Percent = 0x00000800;
	int tempMax_HP = 0x00001000;
	int tempCritical = 0x00002000;
	int tempCriticalDamage = 0x00004000;
	int tempBossDamage = 0x00008000;
	int tempDefenceIgnore = 0x00010000;
	int tempExp = 0x00020000;
	int tempMeso = 0x00040000;

	//m_unionRaiderEffectList.emplace("히어로", STR);
	//m_unionRaiderEffectList.emplace("팔라딘", STR);
	//m_unionRaiderEffectList.emplace("바이퍼", STR);
	//m_unionRaiderEffectList.emplace("캐논슈터", STR);
	//m_unionRaiderEffectList.emplace("아크", STR);
	//m_unionRaiderEffectList.emplace("스트라이커", STR);
	//m_unionRaiderEffectList.emplace("아델", STR);
	//m_unionRaiderEffectList.emplace("카이저", STR);

	//m_unionRaiderEffectList.emplace("보우마스터", DEX);
	//m_unionRaiderEffectList.emplace("패스파인더", DEX);
	//m_unionRaiderEffectList.emplace("윈드브레이커", DEX);
	//m_unionRaiderEffectList.emplace("엔젤릭버스터", DEX);

	//m_unionRaiderEffectList.emplace("썬콜", INT);
	//m_unionRaiderEffectList.emplace("비숍", INT);
	//m_unionRaiderEffectList.emplace("플레임위자드", INT);
	//m_unionRaiderEffectList.emplace("키네시스", INT);
	//m_unionRaiderEffectList.emplace("루미너스", INT);
	//m_unionRaiderEffectList.emplace("일리움", INT);
	//m_unionRaiderEffectList.emplace("배틀메이지", INT);

	//m_unionRaiderEffectList.emplace("나이트로드", LUK);
	//m_unionRaiderEffectList.emplace("듀얼블레이드", LUK);
	//m_unionRaiderEffectList.emplace("나이트워커", LUK);
	//m_unionRaiderEffectList.emplace("섀도어", LUK);
	//m_unionRaiderEffectList.emplace("호영", LUK);
	//m_unionRaiderEffectList.emplace("카데나", LUK);

	m_unionRaiderEffectList.emplace("제논", tempSTR_DEX_LUK);
	m_unionRaiderEffectList.emplace("다크나이트", tempMax_HP_Percent);
	m_unionRaiderEffectList.emplace("불독", tempMax_MP_Percent);
	m_unionRaiderEffectList.emplace("소울마스터", tempMax_HP);
	m_unionRaiderEffectList.emplace("미하일", tempMax_HP);
	m_unionRaiderEffectList.emplace("나이트로드", tempCritical);
	m_unionRaiderEffectList.emplace("신궁", tempCritical);
	m_unionRaiderEffectList.emplace("은월", tempCriticalDamage);
	m_unionRaiderEffectList.emplace("데몬어벤져", tempBossDamage);
	m_unionRaiderEffectList.emplace("블래스터", tempDefenceIgnore);
	m_unionRaiderEffectList.emplace("제로", tempExp);
	m_unionRaiderEffectList.emplace("팬텀", tempMeso);

	for (auto data : m_unionRaiderEffectList)
		out << data.first << '\t' << data.second << endl;

	out.close();

	cout << "유니온 공격대원 효과 정보 파일 출력 완료" << endl;

	return true;
}
