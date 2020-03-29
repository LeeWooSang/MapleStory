#pragma once
#include "../UI.h"
#include "../../../Defines.h"

class TextUI : public UI
{
public:
	TextUI(const string&);
	virtual ~TextUI();

	virtual bool Initialize(TextureInfo);
	virtual void Update(float);
	virtual void Render();

	void ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
	void ProcessEnglish(HWND, WPARAM);
	void ProcessKorean(HWND, LPARAM);
	void DeleteText();
	void ChangeIMEMode(HWND, bool);
	string ConvertTextToString();
	wstring GetText() const;

	void SetIsActive(bool isActive) { m_isActive = isActive; }

private:
	bool m_isActive;
	float m_enableTime;
	bool m_isEnable;

	struct TextInfo
	{
		TextInfo(unsigned char key, const wstring& text)
			: m_Key(key), m_Text(text) {}

		unsigned char m_Key;
		wstring m_Text;
	};

	enum IMEMODE { ENGLISH = 0x0000, KOREAN };

	list<TextInfo> m_textList;
	unsigned long m_IMEMode;
	wstring m_comb;

	enum CHECK_TYPE
	{
		IS_ACTIVE = 0x0001,
		IS_EMPTY = 0x0002
	};

	int m_flag;
};

