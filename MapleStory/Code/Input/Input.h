#pragma once
#include "../Macro.h"
#include "../Defines.h"
#include "../Collision/Collision.h"

constexpr int MAX_LEN = 256;

struct TextInfo
{
	TextInfo(unsigned char key, const wstring& text)
		: m_Key(key), m_Text(text) {}

	unsigned char m_Key;
	wstring m_Text;
};

constexpr int MAX_KEY_TYPE = 7;
enum KEY_TYPE 
{ 
	NONE = 0, 
	KEYBOARD_LEFT,
	KEYBOARD_RIGHT, 
	KEYBOARD_UP,
	KEYBOARD_DOWN,
	MOUSE_LBUTTON,
	MOUSE_RBUTTON 
};

struct KeyState
{
	KeyState() 
		: m_keyType(NONE), m_pushed(false), m_pushing(false), m_pop(false) {}

	int m_keyType;
	// Ű�� ���� ����
	bool m_pushed;
	// Ű�� ��� ������ ���� ��,
	bool m_pushing;
	// Ű�� ���� ����
	bool m_pop;
};

class Input
{
	SINGLE_TONE(Input)

	virtual bool Initialize();
	void Update(float);
	void Render();

	virtual LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM);

	LRESULT ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
	void ProcessMouseMessage(HWND, UINT, LPARAM);
	VECTOR2D ScreenPosition(int, int);

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

	const POINT& GetMousePos() const { return m_mousePos; }

	enum IMEMODE { ENGLISH = 0x0000, KOREAN };

	bool PushedKey(KEY_TYPE key)	const { return m_keyStateList[key].m_pushed; }
	bool PushingKey(KEY_TYPE key)	const { return m_keyStateList[key].m_pushing; }
	bool PopKey(KEY_TYPE key)		const { return m_keyStateList[key].m_pop; }
	bool KeyOnceCheck(KEY_TYPE key);
private:
	void ProcessKeyEvent();

	bool m_isActive;
	unsigned long m_IMEMode;
	wstring m_comb;
	list<TextInfo> m_textList;

	float m_enableTime;
	bool m_isEnable;

	// ����
	float m_width;
	// ����
	float m_height;
	//�� ����
	float m_gap;

	float m_startX;
	float m_startY;

	float m_endX;
	float m_endY;

	POINT m_mousePos;
	
	array<KeyState, MAX_KEY_TYPE> m_keyStateList;
	// ��ư�� ������ �� �˸�
	bool m_flag;
};