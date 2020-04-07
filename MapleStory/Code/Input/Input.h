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

constexpr int MAX_KEY_TYPE = 11;
enum KEY_TYPE 
{ 
	NONE = 0, 

	KEYBOARD_LEFT,
	KEYBOARD_RIGHT, 
	KEYBOARD_UP,
	KEYBOARD_DOWN,

	KEYBOARD_TAB,
	KEYBOARD_ENTER,

	KEYBOARD_CONTROL,
	KEYBOARD_ALT,

	MOUSE_LBUTTON,
	MOUSE_RBUTTON 
};

struct KeyState
{
	KeyState() 
		: m_keyType(NONE), m_pushed(false), m_pushing(false), m_pop(false) {}

	int m_keyType;
	// 키를 누른 순간
	bool m_pushed;
	// 키를 계속 누르고 있을 때,
	bool m_pushing;
	// 키를 떼는 순간
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
	
	void ProcessKeyEvent();
	bool KeyOnceCheck(KEY_TYPE);

	bool GetIsPushed(KEY_TYPE key)	const { return m_keyStateList[key].m_pushed; }
	bool GetIsPushing(KEY_TYPE key)	const { return m_keyStateList[key].m_pushing; }
	bool GetIsPop(KEY_TYPE key)	const { return m_keyStateList[key].m_pop; }

private:

	POINT m_mousePos;
	
	array<KeyState, MAX_KEY_TYPE> m_keyStateList;
	// 버튼이 눌렀을 때 알림
	bool m_flag;
};