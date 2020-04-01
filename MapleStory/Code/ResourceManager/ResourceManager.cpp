#include "ResourceManager.h"
#include "Texture/Texture.h"

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
	m_textureList.emplace("BackButton", tex18);
	if (tex18->Initialize(L"../Resource/Textures/UI/WorldSelect/BackButton.png", 81, 35, 1, 1, 0, 0) == false)
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
	m_textureList.emplace("ChannelButton1", tex21);
	if (tex21->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelButton1.png", 68, 27, 1, 1, 0, 0) == false)
		return false;

	Texture* tex22 = new Texture;
	m_textureList.emplace("ChannelButton2", tex22);
	if (tex22->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelButton2.png", 68, 27, 1, 1, 0, 0) == false)
		return false;

	Texture* tex23 = new Texture;
	m_textureList.emplace("ChannelButton3", tex23);
	if (tex23->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelButton3.png", 68, 27, 1, 1, 0, 0) == false)
		return false;

	Texture* tex24 = new Texture;
	m_textureList.emplace("ChannelButton4", tex24);
	if (tex24->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelButton4.png", 68, 27, 1, 1, 0, 0) == false)
		return false;

	Texture* tex25 = new Texture;
	m_textureList.emplace("ChannelButton5", tex25);
	if (tex25->Initialize(L"../Resource/Textures/UI/ChannelSelect/ChannelButton5.png", 68, 27, 1, 1, 0, 0) == false)
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
