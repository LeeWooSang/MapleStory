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
		cout << "������ ���� ������ �������� �ʽ��ϴ�." << endl;
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

	cout << "������ ���� ���� �ε� �Ϸ�" << endl;
	return true;
}

bool Resource::SaveItemInfo()
{
	ofstream out("../Resource/ItemInfo.txt");
	//for (auto data : m_itemList)
	//	out << data->GetName() << '\t' << data->GetCash() << endl;

	out.close();

	cout << "������ ���� ���� ��� �Ϸ�" << endl;
	return true;
}

bool Resource::LoadJobInfo()
{
	ifstream in("../Resource/JobInfo.txt");
	if (!in)
	{
		cout << "���� ���� ������ �������� �ʽ��ϴ�." << endl;
		return false;
	}

	string name = "";
	int mainStat = 0;

	while (in >> name >> mainStat)
		m_jobInfoList.emplace(name, mainStat);

	in.close();

	cout << "���� ���� ���� �ε� �Ϸ�" << endl;

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

	m_jobInfoList.emplace("�����", STR);
	m_jobInfoList.emplace("�ȶ��", STR);
	m_jobInfoList.emplace("��ũ����Ʈ", STR);
	m_jobInfoList.emplace("������", STR);
	m_jobInfoList.emplace("ĳ����", STR);
	m_jobInfoList.emplace("�ҿ︶����", STR);
	m_jobInfoList.emplace("������", STR);
	m_jobInfoList.emplace("��Ʈ����Ŀ", STR);
	m_jobInfoList.emplace("������", STR);
	m_jobInfoList.emplace("���󽽷��̾�", STR);
	m_jobInfoList.emplace("�ƶ�", STR);
	m_jobInfoList.emplace("����", STR);
	m_jobInfoList.emplace("ī����", STR);
	m_jobInfoList.emplace("����", STR);
	m_jobInfoList.emplace("�Ƶ�", STR);
	m_jobInfoList.emplace("��ũ", STR);

	m_jobInfoList.emplace("���츶����", DEX);
	m_jobInfoList.emplace("�ű�", DEX);
	m_jobInfoList.emplace("�н����δ�", DEX);
	m_jobInfoList.emplace("ĸƾ", DEX);
	m_jobInfoList.emplace("����극��Ŀ", DEX);
	m_jobInfoList.emplace("���ϵ�����", DEX);
	m_jobInfoList.emplace("��ī��", DEX);
	m_jobInfoList.emplace("�޸�������", DEX);
	m_jobInfoList.emplace("������������", DEX);

	m_jobInfoList.emplace("����", INT);
	m_jobInfoList.emplace("�ҵ�", INT);
	m_jobInfoList.emplace("���", INT);
	m_jobInfoList.emplace("�÷������ڵ�", INT);
	m_jobInfoList.emplace("��Ʋ������", INT);
	m_jobInfoList.emplace("����", INT);
	m_jobInfoList.emplace("��̳ʽ�", INT);
	m_jobInfoList.emplace("Ű�׽ý�", INT);
	m_jobInfoList.emplace("�ϸ���", INT);

	m_jobInfoList.emplace("����Ʈ�ε�", LUK);
	m_jobInfoList.emplace("������", LUK);
	m_jobInfoList.emplace("�����̵�", LUK);
	m_jobInfoList.emplace("����Ʈ��Ŀ", LUK);
	m_jobInfoList.emplace("����", LUK);
	m_jobInfoList.emplace("ī����", LUK);
	m_jobInfoList.emplace("ȣ��", LUK);

	m_jobInfoList.emplace("����", STR_DEX_LUK);
	m_jobInfoList.emplace("������", HP);

	for (auto data : m_jobInfoList)
		out << data.first << '\t' << static_cast<int>(data.second) << endl;

	out.close();

	cout << "���� ���� ���� ��� �Ϸ�" << endl;

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

bool Resource::LoadUnionRaiderEffectInfo()
{
	ifstream in("../Resource/UnionRaiderEffectInfo.txt");
	if (!in)
	{
		cout << "���Ͽ� ���ݴ�� ȿ�� ���� ������ �������� �ʽ��ϴ�." << endl;
		return false;
	}

	string name = "";
	int effect = 0;
	while (in >> name >> effect)
		m_unionRaiderEffectList.emplace(name, effect);

	in.close();

	cout << "���Ͽ� ���ݴ�� ȿ�� ���� ���� �ε� �Ϸ�" << endl;

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

	//m_unionRaiderEffectList.emplace("�����", STR);
	//m_unionRaiderEffectList.emplace("�ȶ��", STR);
	//m_unionRaiderEffectList.emplace("������", STR);
	//m_unionRaiderEffectList.emplace("ĳ����", STR);
	//m_unionRaiderEffectList.emplace("��ũ", STR);
	//m_unionRaiderEffectList.emplace("��Ʈ����Ŀ", STR);
	//m_unionRaiderEffectList.emplace("�Ƶ�", STR);
	//m_unionRaiderEffectList.emplace("ī����", STR);

	//m_unionRaiderEffectList.emplace("���츶����", DEX);
	//m_unionRaiderEffectList.emplace("�н����δ�", DEX);
	//m_unionRaiderEffectList.emplace("����극��Ŀ", DEX);
	//m_unionRaiderEffectList.emplace("������������", DEX);

	//m_unionRaiderEffectList.emplace("����", INT);
	//m_unionRaiderEffectList.emplace("���", INT);
	//m_unionRaiderEffectList.emplace("�÷������ڵ�", INT);
	//m_unionRaiderEffectList.emplace("Ű�׽ý�", INT);
	//m_unionRaiderEffectList.emplace("��̳ʽ�", INT);
	//m_unionRaiderEffectList.emplace("�ϸ���", INT);
	//m_unionRaiderEffectList.emplace("��Ʋ������", INT);

	//m_unionRaiderEffectList.emplace("����Ʈ�ε�", LUK);
	//m_unionRaiderEffectList.emplace("�����̵�", LUK);
	//m_unionRaiderEffectList.emplace("����Ʈ��Ŀ", LUK);
	//m_unionRaiderEffectList.emplace("������", LUK);
	//m_unionRaiderEffectList.emplace("ȣ��", LUK);
	//m_unionRaiderEffectList.emplace("ī����", LUK);

	m_unionRaiderEffectList.emplace("����", tempSTR_DEX_LUK);
	m_unionRaiderEffectList.emplace("��ũ����Ʈ", tempMax_HP_Percent);
	m_unionRaiderEffectList.emplace("�ҵ�", tempMax_MP_Percent);
	m_unionRaiderEffectList.emplace("�ҿ︶����", tempMax_HP);
	m_unionRaiderEffectList.emplace("������", tempMax_HP);
	m_unionRaiderEffectList.emplace("����Ʈ�ε�", tempCritical);
	m_unionRaiderEffectList.emplace("�ű�", tempCritical);
	m_unionRaiderEffectList.emplace("����", tempCriticalDamage);
	m_unionRaiderEffectList.emplace("������", tempBossDamage);
	m_unionRaiderEffectList.emplace("������", tempDefenceIgnore);
	m_unionRaiderEffectList.emplace("����", tempExp);
	m_unionRaiderEffectList.emplace("����", tempMeso);

	for (auto data : m_unionRaiderEffectList)
		out << data.first << '\t' << data.second << endl;

	out.close();

	cout << "���Ͽ� ���ݴ�� ȿ�� ���� ���� ��� �Ϸ�" << endl;

	return true;
}
