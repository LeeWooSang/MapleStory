#pragma once
#include "../Macro.h"
#include "../Defines.h"
#include "../Collision/Collision.h"

constexpr int MAX_LEN = 256;

//struct TextInfo
//{
//	TextInfo(unsigned char key, const wstring& text)
//		: m_Key(key), m_Text(text) {}
//
//	unsigned char m_Key;
//	wstring m_Text;
//};

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

	virtual LRESULT CALLBACK ProcessWindowMessage(HWND, UINT, WPARAM, LPARAM);

	LRESULT ProcessKeyboardMessage(HWND, UINT, WPARAM, LPARAM);
	void ProcessMouseMessage(HWND, UINT, LPARAM);

	const POINT& GetMousePos() const { return m_mousePos; }

	bool PushedKey(KEY_TYPE key)	const { return m_keyStateList[key].m_pushed; }
	bool PushingKey(KEY_TYPE key)	const { return m_keyStateList[key].m_pushing; }
	bool PopKey(KEY_TYPE key)		const { return m_keyStateList[key].m_pop; }
	bool KeyOnceCheck(KEY_TYPE key);

private:
	void ProcessKeyEvent();

	POINT m_mousePos;
	
	array<KeyState, MAX_KEY_TYPE> m_keyStateList;
	// ��ư�� ������ �� �˸�
	bool m_flag;
};