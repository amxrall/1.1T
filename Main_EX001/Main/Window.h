#pragma once

extern HWND(WINAPI* pCreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);

extern LONG(WINAPI* pChangeDisplaySettingsA)(DEVMODEA*, DWORD);

extern HICON(WINAPI* pLoadIconA)(HINSTANCE hInstance, LPCSTR lpIconName);

class cWindow
{
public:

	cWindow();

	~cWindow();

	void WindowModeLoad(HINSTANCE hins);

	int iSizeX;
	int iSizeY;

private:

	static HWND WINAPI dtCreateWindowExA(DWORD ExStyle, LPCSTR ClassName, LPCSTR WindowName, DWORD Style, int X, int Y, int Width, int Height, HWND Parent, HMENU Menu, HINSTANCE Instance, LPVOID Parameter);

	static LONG WINAPI dtChangeDisplaySettingsA(DEVMODEA* DevMode, DWORD Flag);

	static HICON WINAPI WindowIconHook(HINSTANCE hInstance, LPCSTR lpIconName);

	HINSTANCE Instance;

	int m_WindowMode;
};

extern cWindow gWindow;