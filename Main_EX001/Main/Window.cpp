#include "StdAfx.h"
#include "resource.h"

cWindow	gWindow;

cWindow::cWindow()
{
	HKEY Key;

	if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Webzen\\MU\\Config", &Key) == ERROR_SUCCESS)
	{
		DWORD Size = sizeof(int);

		if (RegQueryValueEx(Key, "WindowMode", nullptr, nullptr, (LPBYTE)(&this->m_WindowMode), &Size) != ERROR_SUCCESS)
		{
			this->m_WindowMode = 0;
		}

		RegCloseKey(Key);
	}
}

cWindow::~cWindow()
{

}

void cWindow::WindowModeLoad(HINSTANCE hins)
{
	this->Instance = hins;

	if (this->m_WindowMode > 0)
	{
		DetourTransactionBegin();

		DetourUpdateThread(GetCurrentThread());

		DetourAttach((&(LPVOID&)(pCreateWindowExA)), dtCreateWindowExA);

		DetourAttach((&(LPVOID&)(pChangeDisplaySettingsA)), dtChangeDisplaySettingsA);

		DetourTransactionCommit();
	}

	DetourTransactionBegin();

	DetourUpdateThread(GetCurrentThread());

	DetourAttach((&(LPVOID&)(pLoadIconA)), WindowIconHook);

	DetourTransactionCommit();
}

HWND(WINAPI* pCreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID) = CreateWindowExA;

HWND WINAPI cWindow::dtCreateWindowExA(DWORD ExStyle, LPCSTR ClassName, LPCSTR WindowName, DWORD Style, int X, int Y, int Width, int Height, HWND Parent, HMENU Menu, HINSTANCE Instance, LPVOID Parameter)
{
	if (IS_INTRESOURCE(ClassName))
	{
		return pCreateWindowExA(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
	}

	if (_stricmp(ClassName, "MU") == 0)
	{
		int SizeX = Width;
		int SizeY = Height;

		int ScreenX = GetSystemMetrics(SM_CXSCREEN);
		int ScreenY = GetSystemMetrics(SM_CYSCREEN);

		int X2 = (ScreenX / 2) - (SizeX / 2);
		int Y2 = (ScreenY / 2) - (SizeY / 2);

		DWORD NewStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		HWND Window = pCreateWindowExA(
			0,
			ClassName,
			WindowName,
			NewStyle,
			X2,
			Y2,
			SizeX,
			SizeY + 28,
			0,
			0,
			Instance,
			Parameter
		);

		SetWindowPos(Window, NULL, X2, Y2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		return Window;
	}

	return pCreateWindowExA(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, Menu, Instance, Parameter);
}

LONG(WINAPI* pChangeDisplaySettingsA)(DEVMODEA*, DWORD) = ChangeDisplaySettingsA;

LONG WINAPI cWindow::dtChangeDisplaySettingsA(DEVMODEA* DevMode, DWORD Flag)
{
	UNREFERENCED_PARAMETER(DevMode);

	UNREFERENCED_PARAMETER(Flag);

	return DISP_CHANGE_SUCCESSFUL;
}

HICON(WINAPI* pLoadIconA)(HINSTANCE hInstance, LPCSTR lpIconName) = LoadIconA;

HICON WINAPI cWindow::WindowIconHook(HINSTANCE hInstance, LPCSTR lpIconName)
{
	return pLoadIconA(gWindow.Instance, MAKEINTRESOURCE(IDI_ICON1));
}