#pragma once
#define SAFE_DELETE(p)				if(p != nullptr)	{ delete p; p = nullptr; }

#define SAFE_DELETE_ARRAY(p)	if(p != nullptr)	{ delete[] p; p = nullptr; }

#define SAFE_DELETE_LIST(p) \
for(auto iter = p.begin(); iter != p.end(); ) \
{ \
	delete (*iter); \
	iter = p.erase(iter); \
} \
p.clear(); \

#define SAFE_DELETE_MAP(p) \
for(auto iter = p.begin(); iter != p.end(); ) \
{ \
	delete (*iter).second; \
	iter = p.erase(iter); \
} \
p.clear(); \

//  싱글톤 매크로
#define SINGLE_TONE(T)	\
	static T* m_Instance; \
public: \
			T(); \
			~T(); \
			static T* GetInstance() \
			{ \
				if (m_Instance == nullptr) \
					m_Instance = new T; \
				return m_Instance; \
			} \
			static void Release() \
			{ \
				SAFE_DELETE(m_Instance); \
			} \

// static 변수인 instance 초기화
#define INIT_INSTACNE(T)	T* T::m_Instance = nullptr;

// 객체 얻어오는 매크로
#define GET_INSTANCE(T)	T::GetInstance()

#define KEY_DOWN(VK_CODE)	((GetAsyncKeyState(VK_CODE) & 0x8000) ? 1 : 0)
#define KEY_UP(VK_CODE)			((GetAsyncKeyState(VK_CODE) & 0x8000) ? 0 : 1)