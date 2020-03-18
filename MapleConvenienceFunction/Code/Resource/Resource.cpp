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

	cout << "�븻 ������ ���� ���� �ε� �Ϸ�" << endl;
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

	cout << "ĳ�� ������ ���� ���� �ε� �Ϸ�" << endl;
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

	cout << "���� ���� ���� �ε� �Ϸ�" << endl;

	return true;
}

bool Resource::LoadCharacterInfo()
{
	ifstream in("../Resource/CharacterInfo.txt");
	if (!in)
	{
		cout << "ĳ���� ���� ������ �������� �ʽ��ϴ�." << endl;
		return false;
	}

	string nickName = "";
	string jobName = "";
	int level = 0;

	while (in >> nickName >> jobName >> level)
		m_characterInfoList.emplace(nickName, CharacterInfo(jobName, level));

	in.close();

	cout << "ĳ���� ���� ���� �ε� �Ϸ�" << endl;

	return true;
}

bool Resource::SaveCharacterInfo()
{
	ofstream out("../Resource/CharacterInfo.txt");

	m_characterInfoList.emplace("â������", CharacterInfo("�����", 237));
	m_characterInfoList.emplace("����", CharacterInfo("�ȶ��", 211));
	m_characterInfoList.emplace("������", CharacterInfo("����", 200));
	m_characterInfoList.emplace("�찡����", CharacterInfo("������", 200));
	m_characterInfoList.emplace("ī�����YJ", CharacterInfo("����Ʈ�ε�", 200));
	m_characterInfoList.emplace("����ũD�糪", CharacterInfo("������������", 200));
	m_characterInfoList.emplace("���־�2017", CharacterInfo("����", 200));
	m_characterInfoList.emplace("HANS����", CharacterInfo("����", 200));
	
	for (auto data : m_characterInfoList)
		out << data.first << '\t' << data.second.m_jobName << '\t' << static_cast<int>(data.second.m_level) << endl;

	out.close();

	cout << "ĳ���� ���� ���� ��� �Ϸ�" << endl;

	return true;
}
