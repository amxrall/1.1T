#include "stdafx.h"
#include "resource.h"
#include "TrayMode.h"
#include <Shellapi.h>

CTrayMode gTrayMode;

CTrayMode::CTrayMode()
{

}

CTrayMode::~CTrayMode()
{

}

void CTrayMode::Init(HINSTANCE hins)
{
	this->m_TrayIcon = (HICON)LoadImage(hins, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);

	this->m_MainWndProc = 0;
}

void CTrayMode::Toggle()
{
	if (this->GetMainWndProc() != 0)
	{
		if (IsWindowVisible(pGameWindow) == 0)
		{
			ShowWindow(pGameWindow, SW_SHOW);

			this->ShowNotify(0);
			
		}
		else
		{
			ShowWindow(pGameWindow, SW_HIDE); // SW_HIDE

			this->ShowNotify(1);

			this->ShowMessage(NIIF_INFO, gProtect.m_Data.WindowName, "Foi Minimizado.");
		}
	}
}

void CTrayMode::ShowMessage(DWORD Type, char* Title, char* Message)
{
	NOTIFYICONDATA Icon = { 0 };

	Icon.cbSize = sizeof(NOTIFYICONDATA);

	Icon.uID = WM_TRAY_MODE_ICON;

	Icon.hWnd = pGameWindow;

	Icon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_INFO;

	Icon.hIcon = this->m_TrayIcon;

	Icon.uCallbackMessage = WM_TRAY_MODE_MESSAGE;

	Icon.dwInfoFlags = Type;

	Icon.uTimeout = 5000;

	strcpy_s(Icon.szInfo, Message);

	strcpy_s(Icon.szInfoTitle, Title);

	Shell_NotifyIcon(NIM_MODIFY, &Icon);
}

LONG CTrayMode::GetMainWndProc()
{
	return ((this->m_MainWndProc == 0) ? ((LONG)(this->m_MainWndProc = (WNDPROC)SetWindowLong(pGameWindow, GWL_WNDPROC, (LONG)CTrayMode::TrayModeWndProc))) : ((LONG)this->m_MainWndProc));
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

	wsprintf(nid.szTip, gProtect.m_Data.WindowName);

	Shell_NotifyIcon(((mode == 0) ? NIM_DELETE : NIM_ADD), &nid);
}

LRESULT CALLBACK CTrayMode::TrayModeWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TRAY_MODE_MESSAGE:
	{
		switch (lParam)
		{
		case WM_LBUTTONDBLCLK:
		{
			gTrayMode.Toggle();

			break;
		}

		default:
		{
			break;
		}
		}
	}

	default:
	{
		break;
	}
	}

	return CallWindowProc((WNDPROC)gTrayMode.GetMainWndProc(), hWnd, message, wParam, lParam);
}