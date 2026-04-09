#pragma once

void Initialize();
void Optimize();

static SHORT(WINAPI* HookGetAsyncKeyState)(int vKey);

#define AUTOCLICK_LEFT		70001
#define AUTOCLICK_RIGHT		70002

#define pMain_IP		0x006B6694
#define pMain_Version	0x006B7248
#define pMain_Serial	0x006B7250
#define pMain_Title	    0x004B375A // test 4B375A


extern HWND         Window;
extern HHOOK        m_Mouse;
extern HHOOK        m_Keyboard1;
extern HHOOK        m_Keyboard2;
extern HMODULE		m_Glow;
extern BYTE         MouseState;
extern int          MouseX;
extern int          MouseY;
extern bool         MoveCamera;
extern bool         AutoClick[3];
extern bool         Monster[2];
extern bool         Active[3];


LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcEx(HWND Window, UINT Message, WPARAM W, LPARAM L);