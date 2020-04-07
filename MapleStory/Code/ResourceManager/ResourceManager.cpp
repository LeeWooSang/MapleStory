#include "ResourceManager.h"
#include "Texture/Texture.h"
//#include "../../../GameServer/Code/Protocol.h"

INIT_INSTACNE(ResourceManager)
ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	SAFE_DELETE_MAP(m_textureList);
}

bool ResourceManager::Initialize()
{
	if (LoadTexture() == false)
		return false;


	return true;
}

bool ResourceManager::LoadTexture()
{
	Texture* tex1 = new Texture;
	m_textureList.emplace("LoginBackground", tex1);
	if (tex1->Initialize(L"../Resource/Textures/UI/Login/LoginBackground.png", 800, 600, 1, 1, 0, 0) == false)
		return false;

	Texture* tex2 = new Texture;
	m_textureList.emplace("Frame", tex2);
	if (tex2->Initialize(L"../Resource/Textures/UI/Login/Frame.png", 800, 600, 1, 1, 0, 0) == false)
		return false;

	Texture* tex3 = new Texture;
	m_textureList.emplace("LoginGameGrade", tex3);
	if (tex3->Initialize(L"../Resource/Textures/UI/Login/LoginGameGrade.png", 65, 75, 1, 1, 0, 0) == false)
		return false;

	Texture* tex4 = new Texture;
	m_textureList.emplace("LoginLogo", tex4);
	if (tex4->Initialize(L"../Resource/Textures/UI/Login/LoginLogo.png", 352, 173, 1, 1, 0, 0) == false)
		return false;

	Texture* tex5 = new Texture;
	m_textureList.emplace("LoginInputBackground", tex5);
	if (tex5->Initialize(L"../Resource/Textures/UI/Login/LoginInputBackground.png", 244, 158, 1, 1, 0, 0) == false)
		return false;

	Texture* tex6 = new Texture;
	m_textureList.emplace("LoginInputButton", tex6);
	if (tex6->Initialize(L"../Resource/Textures/UI/Login/LoginInputButton.png", 50, 50, 1, 1, 0, 0) == false)
		return false;

	Texture* tex7 = new Texture;
	m_textureList.emplace("LoginIDInput", tex7);
	if (tex7->Initialize(L"../Resource/Textures/UI/Login/LoginIDInput.png", 160, 23, 1, 1, 0, 0) == false)
		return false;

	Texture* tex8 = new Texture;
	m_textureList.emplace("LoginPWInput", tex8);
	if (tex8->Initialize(L"../Resource/Textures/UI/Login/LoginPWInput.png", 160, 23, 1, 1, 0, 0) == false)
		return false;

	Texture* tex9 = new Texture;
	m_textureList.emplace("LoginQuitButton", tex9);
	if (tex9->Initialize(L"../Resource/Textures/UI/Login/LoginQuitButton.png", 69, 30, 1, 1, 0, 0) == false)
		return false;

	Texture* tex10 = new Texture;
	m_textureList.emplace("NoticeBackground", tex10);
	if (tex10->Initialize(L"../Resource/Textures/UI/Login/NoticeBackground.png", 249, 142, 1, 1, 0, 0) == false)
		return false;

	Texture* tex11 = new Texture;
	m_textureList.emplace("NoticeIDNotCorrect", tex11);
	if (tex11->Initialize(L"../Resource/Textures/UI/Login/NoticeIDNotCorrect.png", 215, 86, 1, 1, 0, 0) == false)
		return false;

	Texture* tex12 = new Texture;
	m_textureList.emplace("NoticePWNotCorrect", tex12);
	if (tex12->Initialize(L"../Resource/Textures/UI/Login/NoticePWNotCorrect.png", 215, 86, 1, 1, 0, 0) == false)
		return false;

	Texture* tex13 = new Texture;
	m_textureList.emplace("NoticeYesButton", tex13);
	if (tex13->Initialize(L"../Resource/Textures/UI/Login/NoticeYesButton.png", 50, 23, 1, 1, 0, 0) == false)
		return false;

	Texture* tex14 = new Texture;
	m_textureList.emplace("NoticeNoButton", tex14);
	if (tex14->Initialize(L"../Resource/Textures/UI/Login/NoticeNoButton.png", 50, 23, 1, 1, 0, 0) == false)
		return false;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Texture* tex15 = new Texture;
	m_textureList.emplace("WorldSelectBackground", tex15);
	if (tex15->Initialize(L"../Resource/Textures/UI/WorldSelect/WorldSelectBackground.png", 800, 600, 1, 1, 0, 0) == false)
		return false;

	Texture* tex16 = new Texture;
	m_textureList.emplace("WorldSelectFrame", tex16);
	if (tex16->Initialize(L"../Resource/Textures/UI/WorldSelect/WorldSelectFrame.png", 126, 525, 1, 1, 0, 0) == false)
		return false;

	Texture* tex17 = new Texture;
	m_textureList.emplace("WorldSelectLogo", tex17);
	if (tex17->Initialize(L"../Resource/Textures/UI/WorldSelect/WorldSelectLogo.png", 127, 42, 1, 1, 0, 0) == false)
		return false;

	Texture* tex18 = new Texture;
	m_textureList.emplace("GoLoginSceneButton", tex18);
	if (tex18->Initialize(L"../Resource/Textures/UI/WorldSelect/GoLoginSceneButton.png", 81, 35, 1, 1, 0, 0) == false)
		return false;

	Texture* tex19 = new Texture;
	m_textureList.emplace("WorldButton0", tex19);
	if (tex19->Initialize(L"../Resource/Textures/UI/WorldSelect/WorldButton0.png", 96, 32, 1, 1, 0, 0) == false)
		return false;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Texture* tex20 = new Texture;
	m_textureList.emplace("ChannelSelectBackground", tex20);
	if (tex20->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelSelectBackground.png", 396, 335, 1, 1, 0, 0) == false)
		return false;
	
	Texture* tex21 = new Texture;
	m_textureList.emplace("ChannelWorldLogo", tex21);
	if (tex21->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelWorldLogo.png", 132, 44, 1, 1, 0, 0) == false)
		return false;

	Texture* tex22 = new Texture;
	m_textureList.emplace("ChannelSelectButton", tex22);
	if (tex22->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelSelectButton.png", 131, 31, 1, 1, 0, 0) == false)
		return false;

	Texture* tex23 = new Texture;
	m_textureList.emplace("ChannelGauge", tex23);
	if (tex23->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelGauge.png", 56, 5, 1, 1, 0, 0) == false)
		return false;

	for (int i = 0; i < 5; ++i)
	{
		string s = "ChannelButton" + to_string(i + 1);
		wstring ws = L"ChannelButton" + to_wstring(i + 1) + L".png";

		Texture* tex = new Texture;
		m_textureList.emplace(s, tex);
		if (tex->Initialize(L"../Resource/Textures/UI/ChannelSelect/" + ws, 68, 27, 1, 1, 0, 0) == false)
			return false;
	}

	Texture* tex24 = new Texture;
	m_textureList.emplace("CharacterSelectBackground", tex24);
	if (tex24->Initialize(L"../Resource/Textures/UI/CharacterSelect/CharacterSelectBackground.png", 800, 600, 1, 1, 0, 0) == false)
		return false;

	Texture* tex25 = new Texture;
	m_textureList.emplace("GoWorldSelectSceneButton", tex25);
	if (tex25->Initialize(L"../Resource/Textures/UI/CharacterSelect/GoWorldSelectSceneButton.png", 81, 35, 1, 1, 0, 0) == false)
		return false;

	Texture* tex26 = new Texture;
	m_textureList.emplace("CharacterSelectLogo", tex26);
	if (tex26->Initialize(L"../Resource/Textures/UI/CharacterSelect/CharacterSelectLogo.png", 127, 42, 1, 1, 0, 0) == false)
		return false;

	Texture* tex27 = new Texture;
	m_textureList.emplace("WorldLogoBackground", tex27);
	if (tex27->Initialize(L"../Resource/Textures/UI/CharacterSelect/WorldLogoBackground.png", 190, 89, 1, 1, 0, 0) == false)
		return false;

	Texture* tex28 = new Texture;
	m_textureList.emplace("WorldLogoIcon", tex28);
	if (tex28->Initialize(L"../Resource/Textures/UI/CharacterSelect/WorldLogoIcon.png", 44, 48, 1, 1, 0, 0) == false)
		return false;

	Texture* tex29 = new Texture;
	m_textureList.emplace("WorldLogoName", tex29);
	if (tex29->Initialize(L"../Resource/Textures/UI/CharacterSelect/WorldLogoName.png", 81, 25, 1, 1, 0, 0) == false)
		return false;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Texture* tex30 = new Texture;
	m_textureList.emplace("FrontHead", tex30);
	if (tex30->Initialize(L"../Resource/Textures/Character/Head/FrontHead.png", 39, 35, 1, 1, 0, 0, 2.5f, 0.f) == false)
		return false;

	Texture* tex31 = new Texture;
	m_textureList.emplace("BackHead", tex31);
	if (tex31->Initialize(L"../Resource/Textures/Character/Head/BackHead.png", 41, 35, 1, 1, 0, 0) == false)
		return false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Texture* tex32 = new Texture;
	m_textureList.emplace("IdleBody0", tex32);
	if (tex32->Initialize(L"../Resource/Textures/Character/Body/Idle/IdleBody0.png", 21, 31, 1, 1, 0, 0, 0.f, 30.f) == false)
		return false;

	Texture* tex33 = new Texture;
	m_textureList.emplace("IdleBody1", tex33);
	if (tex33->Initialize(L"../Resource/Textures/Character/Body/Idle/IdleBody1.png", 22, 31, 1, 1, 0, 0, -0.5f, 30.f) == false)
		return false;

	Texture* tex34 = new Texture;
	m_textureList.emplace("IdleBody2", tex34);
	if (tex34->Initialize(L"../Resource/Textures/Character/Body/Idle/IdleBody2.png", 23, 31, 1, 1, 0, 0, -1.f, 30.f) == false)
		return false;

	Texture* tex35 = new Texture;
	m_textureList.emplace("IdleArm0", tex35);
	if (tex35->Initialize(L"../Resource/Textures/Character/Arm/Idle/IdleArm0.png", 10, 19, 1, 1, 0, 0, 9.f, 25.f) == false)
		return false;

	Texture* tex36 = new Texture;
	m_textureList.emplace("IdleArm1", tex36);
	if (tex36->Initialize(L"../Resource/Textures/Character/Arm/Idle/IdleArm1.png", 10, 19, 1, 1, 0, 0, 9.f, 25.f) == false)
		return false;

	Texture* tex37 = new Texture;
	m_textureList.emplace("IdleArm2", tex37);
	if (tex37->Initialize(L"../Resource/Textures/Character/Arm/Idle/IdleArm2.png", 11, 19, 1, 1, 0, 0, 9.f, 25.f) == false)
		return false;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Texture* tex38 = new Texture;
	m_textureList.emplace("WalkBody0", tex38);
	if (tex38->Initialize(L"../Resource/Textures/Character/Body/Walk/WalkBody0.png", 27, 32, 1, 1, 0, 0, 0.f, 30.f) == false)
		return false;

	Texture* tex39 = new Texture;
	m_textureList.emplace("WalkBody1", tex39);
	if (tex39->Initialize(L"../Resource/Textures/Character/Body/Walk/WalkBody1.png", 26, 32, 1, 1, 0, 0, 2.f, 30.f) == false)
		return false;

	Texture* tex40 = new Texture;
	m_textureList.emplace("WalkBody2", tex40);
	if (tex40->Initialize(L"../Resource/Textures/Character/Body/Walk/WalkBody2.png", 24, 32, 1, 1, 0, 0, -1.5f, 30.f) == false)
		return false;

	Texture* tex41 = new Texture;
	m_textureList.emplace("WalkBody3", tex41);
	if (tex41->Initialize(L"../Resource/Textures/Character/Body/Walk/WalkBody3.png", 29, 31, 1, 1, 0, 0, -0.5f, 30.f) == false)
		return false;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Texture* tex42 = new Texture;
	m_textureList.emplace("WalkArm0", tex42);
	if (tex42->Initialize(L"../Resource/Textures/Character/Arm/Walk/WalkArm0.png", 12, 17, 1, 1, 0, 0, 12.f, 25.f) == false)
		return false;

	Texture* tex43 = new Texture;
	m_textureList.emplace("WalkArm1", tex43);
	if (tex43->Initialize(L"../Resource/Textures/Character/Arm/Walk/WalkArm1.png", 13, 17, 1, 1, 0, 0, 5.f, 25.f) == false)
		return false;

	Texture* tex44 = new Texture;
	m_textureList.emplace("WalkArm2", tex44);
	if (tex44->Initialize(L"../Resource/Textures/Character/Arm/Walk/WalkArm2.png", 12, 17, 1, 1, 0, 0, 12.f, 25.f) == false)
		return false;

	Texture* tex45 = new Texture;
	m_textureList.emplace("WalkArm3", tex45);
	if (tex45->Initialize(L"../Resource/Textures/Character/Arm/Walk/WalkArm3.png", 14, 15, 1, 1, 0, 0, 12.f, 25.f) == false)
		return false;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Texture* tex46 = new Texture;
	m_textureList.emplace("JumpBody0", tex46);
	if (tex46->Initialize(L"../Resource/Textures/Character/Body/Jump/JumpBody0.png", 35, 30, 1, 1, 0, 0, 0.f, 30.f) == false)
		return false;

	Texture* tex47 = new Texture;
	m_textureList.emplace("JumpArm0", tex47);
	if (tex47->Initialize(L"../Resource/Textures/Character/Arm/Jump/JumpArm0.png", 13, 11, 1, 1, 0, 0, 9.f, 25.f) == false)
		return false;

	return true;
}

Texture* ResourceManager::GetTexture(const string& key)
{
	auto iter = m_textureList.find(key);
	if (iter == m_textureList.end())
		return nullptr;

	return (*iter).second;
}
