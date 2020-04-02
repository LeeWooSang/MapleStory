#pragma once
#include "../Scene.h"

class WorldSelectScene : public Scene
{
public:
	WorldSelectScene();
	virtual ~WorldSelectScene();

	virtual bool Initialize();
	virtual void Update(float);
	virtual void Render();

	virtual void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);

	void SeleIsWorldSelect(bool isWorldSelect) { m_isWorldSelect = isWorldSelect; }

private:
	bool m_isWorldSelect;
	class ChannelSelectLayer* m_channelSelectLayer;
};

