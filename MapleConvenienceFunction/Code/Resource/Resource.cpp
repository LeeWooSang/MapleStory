#include "Resource.h"
#include "../GameObject/Job/Job.h"
#include "../Script/Script.h"

INIT_INSTACNE(Resource)
Resource::Resource()
{
	m_normalItemInfoList.clear();
	m_cashItemInfoList.clear();
	m_jobInfoList.clear();
	m_characterInfoList.clear();
}

Resource::~Resource()
{
	SAFE_DELETE_MAP(m_normalItemInfoList);
	SAFE_DELETE_LIST(m_cashItemInfoList);
	SAFE_DELETE_MAP(m_jobInfoList);

	m_characterInfoList.clear();
}

bool Resource::Initialize()
{
	if (LoadNormalItemInfo() == false)
		return false;

	if (LoadCashItemInfo() == false)
		return false;

	if (LoadJobInfo() == false)
		return false;

	if (LoadCharacterInfo() == false)
		return false;

	return true;
}

bool Resource::LoadNormalItemInfo()
{
	Script* scr = new Script;
	if (scr->Initialize() == false)
	{
		delete scr;
		return false;
	}

	if (scr->LoadINormalInfoScript() == false)
	{
		delete scr;
		return false;
	}

	delete scr;

	cout << "노말 아이템 정보 파일 로딩 완료" << endl;
	return true;
}


bool Resource::LoadCashItemInfo()
{
	Script* scr = new Script;
	if (scr->Initialize() == false)
	{
		delete scr;
		return false;
	}

	if (scr->LoadICashtemInfoScript() == false)
	{
		delete scr;
		return false;
	}

	delete scr;

	cout << "캐시 아이템 정보 파일 로딩 완료" << endl;
	return true;
}

bool Resource::LoadJobInfo()
{
	Script* scr = new Script;
	if (scr->Initialize() == false)
	{
		delete scr;
		return false;
	}

	if (scr->LoadJobInfoScript() == false)
	{
		delete scr;
		return false;
	}

	delete scr;

	cout << "직업 정보 파일 로딩 완료" << endl;

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
