#pragma once
#include "../Macro.h"
#include "../Defines.h"

constexpr int MAX_LEN = 256;

struct TextInfo
{
	TextInfo(unsigned char key, const wstring& text)
		: m_Key(key), m_Text(text) {}

	unsigned char m_Key;
	wstring m_Text;
};

class Input
{
	SINGLE_TONE(Input)

	bool Initialize();

	LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM);

	LRESULT ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
	void ProcessMouseMessage(HWND, UINT, WPARAM, LPARAM);

	void ProcessEnglish(HWND, WPARAM);
	void ProcessKorean(HWND, LPARAM);

	void DeleteText();
	void ChangeIMEMode(HWND, bool);
	void ControlCaret(WPARAM);

	const wstring& GetComb() const { return m_Comb; }
	wstring GetText() const;

	enum IMEMODE { ENGLISH = 0x0000, KOREAN };

private:
	unsigned long m_IMEMode;
	bool m_IsActive;
	wstring m_Comb;
	list<TextInfo> m_TextList;
	unsigned char m_CaretPos;
};