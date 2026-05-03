#include "stdafx.h"
#include "resource.h"
#include "TrayMode.h"

CTrayMode gTrayMode;

CTrayMode::CTrayMode()
{
	this->m_TrayIcon = 0;
	this->m_MainWndProc = 0;
}

CTrayMode::~CTrayMode()
{
}

void CTrayMode::Init(HINSTANCE hins)
{
	this->m_TrayIcon = (HICON)LoadImage(hins, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);

	if (pGameWindow != 0 && this->m_MainWndProc == 0)
	{
		this->m_MainWndProc = (WNDPROC)SetWindowLongPtr(pGameWindow, GWLP_WNDPROC, (LONG_PTR)CTrayMode::TrayModeWndProc);
	}
}

void CTrayMode::Toggle()
{
	if (pGameWindow == 0)
	{
		return;
	}

	if (IsWindowVisible(pGameWindow) == 0)
	{
		ShowWindow(pGameWindow, SW_SHOW);
		ShowWindow(pGameWindow, SW_RESTORE);
		SetForegroundWindow(pGameWindow);
		this->ShowNotify(false);
	}
	else
	{
		this->ShowNotify(true);
		ShowWindow(pGameWindow, SW_HIDE);
	}
}

WNDPROC CTrayMode::GetMainWndProc()
{
	return this->m_MainWndProc;
}

void CTrayMode::ShowNotify(bool mode)
{
	NOTIFYICONDATA nid;

	memset(&nid, 0, sizeof(nid));

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = pGameWindow;
	nid.uID = WM_TRAY_MODE_ICON;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_TRAY_MODE_MESSAGE;
	nid.hIcon = this->m_TrayIcon;

	strcpy_s(nid.szTip, sizeof(nid.szTip), gProtect.m_Data.WindowName);

	Shell_NotifyIcon((mode == false) ? NIM_DELETE : NIM_ADD, &nid);
}

void CTrayMode::ShowMessage(DWORD Type, char* Title, char* Message)
{
	NOTIFYICONDATA Icon;

	memset(&Icon, 0, sizeof(Icon));

	Icon.cbSize = sizeof(NOTIFYICONDATA);
	Icon.uID = WM_TRAY_MODE_ICON;
	Icon.hWnd = pGameWindow;
	Icon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_INFO;
	Icon.hIcon = this->m_TrayIcon;
	Icon.uCallbackMessage = WM_TRAY_MODE_MESSAGE;
	Icon.dwInfoFlags = Type;
	Icon.uTimeout = 5000;

	strcpy_s(Icon.szInfo, sizeof(Icon.szInfo), Message);
	strcpy_s(Icon.szInfoTitle, sizeof(Icon.szInfoTitle), Title);

	Shell_NotifyIcon(NIM_MODIFY, &Icon);
}

LRESULT CALLBACK CTrayMode::TrayModeWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TRAY_MODE_MESSAGE:
	{
		if (lParam == WM_LBUTTONDBLCLK)
		{
			gTrayMode.Toggle();
			return 0;
		}
	}
	break;

	case WM_SYSCOMMAND:
	{
		if ((wParam & 0xFFF0) == SC_MINIMIZE)
		{
			gTrayMode.Toggle();
			return 0;
		}
	}
	break;

	case WM_CLOSE:
	{
		gTrayMode.Toggle();
		return 0;
	}
	}

	if (gTrayMode.GetMainWndProc() != 0)
	{
		return CallWindowProc(gTrayMode.GetMainWndProc(), hWnd, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}