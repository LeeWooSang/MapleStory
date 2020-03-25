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

	virtual bool Initialize();
	void Update(float);
	void Render();

	virtual LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM);

	LRESULT ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
	void ProcessMouseMessage(HWND, UINT, WPARAM, LPARAM);

	void ProcessEnglish(HWND, WPARAM);
	void ProcessKorean(HWND, LPARAM);

	void DeleteText();
	void ChangeIMEMode(HWND, bool);
	void ControlCaret(WPARAM);

	void SetIsActive(bool isActive) { m_isActive = isActive; }
	bool GetIsActive()	const { return m_isActive; }
	const wstring& GetComb() const { return m_comb; }
	wstring GetText() const;

	void WStringToString();

	enum IMEMODE { ENGLISH = 0x0000, KOREAN };

private:
	bool m_isActive;
	unsigned long m_IMEMode;
	wstring m_comb;
	list<TextInfo> m_textList;

	float m_enableTime;
	bool m_isEnable;

	// 굵기
	float m_width;
	// 높이
	float m_height;
	//글 간격
	float m_gap;

	float m_startX;
	float m_startY;

	float m_endX;
	float m_endY;
};