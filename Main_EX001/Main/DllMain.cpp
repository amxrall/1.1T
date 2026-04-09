#include "StdAfx.h"
#include "Offsets.h"

HINSTANCE hins;

extern "C" __declspec(dllexport) void GBTeam()
{
}

BOOL APIENTRY DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		{
		hins = (HINSTANCE)Instance;
		gWindow.WindowModeLoad(hins);

			DWORD OldProtect;
			if (VirtualProtect((LPVOID)(0x401000), 2834430, PAGE_EXECUTE_READWRITE, &OldProtect) == TRUE)
			{
				PROTECT_DATA m_Data;

				if (gProtect.Load("Main.amx") == 0)
				{
					ExitProcess(0);
				}

				if (gProtect.m_Data.SelectCharAnime == 1)
				{
					gSelectChar.Load();
				}

				if (gProtect.m_Data.LoadingWhite == 1)
				{
					LoadWebzenLogo();
				}

				// MiniMap

				if (gProtect.m_Data.MiniMapCheck == 1)
				{
					ReadyMiniMap();
				}

				PlayerLoad();
				gProtect.CheckClientFile();

				gProtect.CheckPlugin1File();

				gProtect.CheckPlugin2File();

				gCustomItem.Load(gProtect.m_Data.CustomItemInfo);

				gCustomJewel.Load(gProtect.m_Data.CustomJewelInfo);

				gCustomWing.Load(gProtect.m_Data.CustomWingInfo);

				gCustomItemDescription.Load(gProtect.m_Data.CustomDescriptionInfo);

				// ---
				Initialize();

				m_Mouse = SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());
				m_Keyboard1 = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, GetCurrentThreadId());
				//m_Keyboard2 = SetWindowsHookEx(WH_KEYBOARD_LL, LL_KeyboardProc, NULL, GetCurrentThreadId());
				// ---
				Wing.Load();
				Smoke.Load();
				gGlowManager.Load();
				gInterface.Load();
				Interface2.Load();
				gTrayMode.Init(hins);
				// ---
				gCustomItemDescription.Init();
				gEffects.Load();
				ItemView();
				InitItem();
				InitJewel();
				Texture.Load();
				gModel.Hook();
				Bow.Load();
				gPetsManager.Load();
			}
		}
		break;
	case DLL_PROCESS_DETACH:
		{
		    UnhookWindowsHookEx(m_Keyboard1);
		    UnhookWindowsHookEx(m_Keyboard2);

		    if (m_Glow)
		    {
			    FreeLibrary(m_Glow);
		    }
		}
		break;
	}

	return TRUE;
}