#include "StdAfx.h"
#include <mmsystem.h>
#include <stdio.h>

#pragma comment(lib, "winmm.lib")

static int g_FPSLimit = 120; // 60 / 75 / 100 / 120

int g_CurrentFPS = 0;
int g_FrameCounter = 0;
DWORD g_FPSLastTick = 0;
char g_FPSString[32] = "FPS: 0";

void LimitFrameRate()
{
	static bool Init = false;
	static LARGE_INTEGER Frequency;
	static LARGE_INTEGER Last;

	if (g_FPSLimit <= 0)
	{
		return;
	}

	if (Init == false)
	{
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&Last);
		timeBeginPeriod(1);

		g_FPSLastTick = GetTickCount();
		Init = true;
		return;
	}

	LONGLONG Target = (Frequency.QuadPart / g_FPSLimit);

	while (true)
	{
		LARGE_INTEGER Now;
		QueryPerformanceCounter(&Now);

		LONGLONG Elapsed = (Now.QuadPart - Last.QuadPart);

		if (Elapsed >= Target)
		{
			Last = Now;
			break;
		}

		DWORD WaitMs = (DWORD)(((Target - Elapsed) * 1000) / Frequency.QuadPart);

		if (WaitMs > 1)
		{
			Sleep(1);
		}
		else
		{
			SwitchToThread();
		}
	}

	g_FrameCounter++;

	DWORD Tick = GetTickCount();

	if ((Tick - g_FPSLastTick) >= 1000)
	{
		g_CurrentFPS = g_FrameCounter;
		g_FrameCounter = 0;
		g_FPSLastTick = Tick;

		wsprintf(g_FPSString, "FPS: %d", g_CurrentFPS);
	}
}

void Initialize()
{
	// - Crack.

	*(BYTE*)(0x4B4305) = 0xEB;
	*(BYTE*)(0x4B47FE) = 0x75;
	*(BYTE*)(0x4B4856) = 0xE9;
	*(BYTE*)(0x4B4857) = 0xA6;
	*(BYTE*)(0x4B4858) = 0x00;
	*(BYTE*)(0x4B485B) = 0x90;
	*(BYTE*)(0x4BEA9F) = 0xEB;
	*(BYTE*)(0x40ABE3) = 0xEB;
	*(BYTE*)(0x40ADD6) = 0xEB;
	*(BYTE*)(0x53E994) = 0xEB;
	*(BYTE*)(0x53ECD4) = 0xEB;
	*(BYTE*)(0x53F8B3) = 0xEB;
	*(BYTE*)(0x540593) = 0xEB;

	// SERIAL
	WriteMemory((LPVOID)pMain_Serial, gProtect.m_Data.Serial, sizeof(gProtect.m_Data.Serial));

	// VERSÃO
	WriteMemory((LPVOID)pMain_Version, gProtect.m_Data.Version, sizeof(gProtect.m_Data.Version));

	// IP
	WriteMemory((LPVOID)pMain_IP, gProtect.m_Data.IP, sizeof(gProtect.m_Data.IP));

	// IpPort
	SetWord(0x006C41BC, (gProtect.m_Data.IpAddressPort)); // IpAddressPort

														  //  Window

	*(DWORD*)(0x4B375A + 1) = (DWORD)(gProtect.m_Data.WindowName);//4B375A
																  // - Screenshots.
																  //CreateDirectory("ScreenShot", NULL);
																  //*(DWORD*)(0x00628B89, (DWORD)gProtect.m_Data.ScreenShotPath); //Screenshot
	SetDword(0x00628B89, (DWORD)gProtect.m_Data.ScreenShotPath); //Screenshot

																 // - Acentuação.

	*(BYTE*)(0x6B6654) = 0xA0;

	// - Antialiased.

	*(BYTE*)(0x4B4E6D + 1) = ANTIALIASED_QUALITY;
	*(BYTE*)(0x4B4DED + 1) = ANTIALIASED_QUALITY;
	*(BYTE*)(0x4B4E2D + 1) = ANTIALIASED_QUALITY;

	// - Select char.
	*(DWORD*)(0x62590A) = (DWORD)(&"");
	*(DWORD*)(0x625918) = (DWORD)(&"");
	*(DWORD*)(0x62593C) = (DWORD)(&"");
	*(DWORD*)(0x625957) = (DWORD)(&"");
	*(DWORD*)(0x625964) = (DWORD)(&"");
	*(DWORD*)(0x625988) = (DWORD)(&"");
	*(DWORD*)(0x6259A3) = (DWORD)(&"");
	*(DWORD*)(0x6259B0) = (DWORD)(&"");
	*(DWORD*)(0x6259D4) = (DWORD)(&"");

	// - Serverlist.

	*(DWORD*)(0x61F3DA) = 0xFF;
	*(DWORD*)(0x61F3E0) = 0xFF;
	*(DWORD*)(0x61F431) = 0x120;
	*(BYTE*)(0x61F463) = 0x4C;
	*(DWORD*)(0x61F7E0) = 0xFC;
	*(DWORD*)(0x61F814) = 0x16D;
	*(DWORD*)(0x61F81F) = 0x1F3;
	*(DWORD*)(0x61FE1D) = 0xFF;
	*(DWORD*)(0x61FE24) = 0xFF;
	*(DWORD*)(0x61FE8F) = 0x118;
	*(DWORD*)(0x61FE9E) = 0x127;
	*(DWORD*)(0x61FEC7) = 0x127;
	*(DWORD*)(0x61FE8F) = 0x11D;
	*(DWORD*)(0x61FF12) = 0x3F700000;
	*(DWORD*)(0x6201B7) = 0x3F700000;
	*(DWORD*)(0x6201D6) = 0x43B68000;
	*(DWORD*)(0x620251) = 0x1B0;
	*(float*)(0x6A9788) = 383.0f;

	// - Modo Janela.

	*(DWORD*)(0x4B36EB) = (DWORD)(&WndProcEx);

	// - Remover Balão de GM
	if (gProtect.m_Data.BALAOGM == 1)
	{
		*(BYTE*)(0x00603405 + 1) = 0x2F;
	}
	// - Recuo.
	if (gProtect.m_Data.Recuo == 1)
	{
		*(BYTE*)(0x4ECA80) = 0xC3;
	}
	// - Optimize.

	HookJump(0x628F99, Optimize);

	// - Cursor.

	*(BYTE*)(0x4CBC47) = 0x90;

	for (DWORD i = 0x4CBC65; i < 0x4CBC6C; i++)
	{
		*(BYTE*)(i) = 0x90;
	}

	*(BYTE*)(0x4CE934) = 0x90;
	*(BYTE*)(0x4CE958) = 0x90;

	for (BYTE i = 0; i < 6; i++)
	{
		*(BYTE*)(0x4CE96B + i) = 0x90;
	}

	// - Visual.

	Visual.Load();

	// - Protocol.

	HookCall(0x4DB63D, cProtocol::ProtocolCoreEx);
	HookJump(0x4CC640, cProtocol::UpdateCharacterNoEffect);
	HookJump(0x4CC3C1, cProtocol::UpdateCharacterEffect);
	HookJump(0x5DEE89, cProtocol::LevelUpPoints);
	HookCall(0x56FE81, cProtocol::Skills);

	// - Title.

	SetNop(0x5A22A3 + 5, 5);
	HookJump(0x5A22A3, cTitle::Load);

	// - Brilho.

	*(BYTE*)(0x506FAD + 1) = 0x8C;
	*(BYTE*)(0x5F9CC2 + 2) = 0x10;

	// - Slide.

	*(BYTE*)(0x42FB81) = 0xEB;
	*(BYTE*)(0x42FB81 + 1) = 0x41;
	*(BYTE*)(0x42FB83) = 0x90;
	*(BYTE*)(0x42FB84) = 0x90;
	*(BYTE*)(0x42FB85) = 0x90;
	*(BYTE*)(0x42FB86) = 0x90;
	*(BYTE*)(0x42FB87) = 0x90;

	// - HP Bar.

	SetNop(0x5AAB8D, 5);
	HookCall(0x596CEA, cHPBar::Draw);

	// - MuError.

	*(BYTE*)(0x41DBB0) = 0xC3;
	*(BYTE*)(0x4B4160) = 0xC3;

	// - Skills.

	*(BYTE*)(0x5951F9 + 1) = 0x2B;
	*(BYTE*)(0x5951FE + 1) = 0x26;
	*(BYTE*)(0x595203 + 1) = 0x21;
	*(BYTE*)(0x595208 + 1) = 0x1C;
	*(BYTE*)(0x59520D + 1) = 0x17;
	*(BYTE*)(0x5956D5 + 2) = 0x00;
	*(BYTE*)(0x5956DA + 2) = 0x00;
	*(BYTE*)(0x5956DF + 2) = 0x00;
	*(BYTE*)(0x5956E4 + 2) = 0x00;
	*(BYTE*)(0x5956E9 + 2) = 0x00;
	*(BYTE*)(0x5956EE + 2) = 0x00;
	*(BYTE*)(0x595212) = 0xEB;
	*(BYTE*)(0x5956F1) = 0xEB;

	// - SetWindowsHookEx.

	*(BYTE*)(0x4519F8) = 0x02;

	//==========================================================//
	// # Click do Botão direito
	//==========================================================//

	HookCall(0x005B798F, CheckClick);
	HookCall(0x005B7A08, CheckClick);
	HookCall(0x005B79B4, ItemPosicion);

	//==========================================================//
	// # Itens +15 Opcionais
	//==========================================================//
	if (gProtect.m_Data.ItemLevel15 == 1)
	{
		gcItem.ItemLoad();
	}

	//==========================================================//
	// # Sistema transparência 100%
	//==========================================================//
	if (gProtect.m_Data.Transparencia == 1)
	{
		MemorySet(0x005F9D6D, 0x90, 0x5);
		MemorySet(0x005F9D4E, 0x90, 0x5);
		MemorySet(0x005F9D31, 0x90, 0x5);
		MemorySet(0x005F9C9B, 0x90, 0x5);
		MemorySet(0x005F9D09, 0x90, 0x5);
	}
	//Inicia a transparência a partir do level 12
	if (gProtect.m_Data.Transparencia12 == 1)
	{
		SetByte(0x005F9C5C + 2, 13);
		SetByte(0x005F9BC8 + 2, 12);
	}
	////Inicia a transparência a partir do level 14
	if (gProtect.m_Data.Transparencia14 == 1)
	{
		SetByte(0x005F9CB9 + 2, 14);
		SetByte(0x005F9C5C + 2, 14);
		SetByte(0x005F9BC8 + 2, 14);
	}
	//==========================================================//
	// # Interface 97d
	//==========================================================//

	if (gProtect.m_Data.InterfaceType == 1)
	{
		SetDword(0x006097CA + 1, (DWORD)"Interface\\Menu011_new.jpg");
		SetDword(0x00609802 + 1, (DWORD)"Interface\\Menu013_new.jpg");
	}
	//==========================================================//
	// # CS SKILL
	//==========================================================//
	if (gProtect.m_Data.CSSkillCheck == 1)
	{
		SetByte(0x005956D5 + 2, 0x00);
		SetByte(0x005956DA + 2, 0x00);
		SetByte(0x005956DF + 2, 0x00);
		SetByte(0x005956E4 + 2, 0x00);
		SetByte(0x005956E9 + 2, 0x00);
		SetByte(0x005956EE + 2, 0x00);
		//----
		SetByte(0x005951F6 + 2, 0x00);
		SetByte(0x005951FB + 2, 0x00);
		SetByte(0x00595200 + 2, 0x00);
		SetByte(0x00595205 + 2, 0x00);
		SetByte(0x0059520A + 2, 0x00);
		SetByte(0x0059520F + 2, 0x00);
	}
	//==========================================================//
	// Character dragging - ao atacar não deslizar
	//==========================================================//
	if (gProtect.m_Data.RemoveDraggingSkill == 1)
	{
		SetByte(0x550B25, 0xE9);
		SetByte(0x550B26, 0xEE);
		SetByte(0x550B27, 0x00);
		SetByte(0x550B28, 0x00);
		SetByte(0x550B29, 0x00);
		SetByte(0x550B2A, 0x90);
	}
	//=================================================
	// - [] [Fix] Wing level 1
	//=================================================
	/*(BYTE*)(0x005A237B + 3) = 0x00;		// [#] - Wings lvl 1 Full
	*(BYTE*)(0x005A393E + 3) = 0x00;		// [#] - deixa a cor das wings level 1 normal
	*(BYTE*)(0x00541A9C + 3) = 0x80;*/		// [#] - retira o nome excellente
}

__declspec(naked) void Optimize()
{
	static DWORD Return = 0x628F9F;

	__asm
	{
		CALL LimitFrameRate
		PUSH 1
		CALL DWORD PTR DS : [0x6A7148]
		CALL DWORD PTR DS : [0x6A7144]
		JMP Return
	}
}

HWND            Window;
HHOOK           m_Mouse = NULL;
HHOOK           m_Keyboard1 = NULL;
HHOOK           m_Keyboard2 = NULL;
HMODULE			m_Glow = NULL;
BYTE            MouseState = NULL;
int             MouseX = NULL;
int             MouseY = NULL;
bool            MoveCamera = false;
bool            AutoClick[3] = { false, false, false };
bool            Monster[2] = { false, false };
bool            Active[3] = { false, false, false };

LRESULT CALLBACK KeyboardProc(int Code, WPARAM wParam, LPARAM lParam)
{
	if (((lParam >> 31) & 1) && (Code == HC_ACTION))
	{
		if (wParam == VK_F5) // camera 3d
		{
			if (Active[1] == false)
			{
				Active[2] = !Active[2];

				Active[1] = true;
			}
			else
			{
				Active[2] = !Active[2];

				Active[1] = false;

				Reset();
			}
		}

		if (wParam == VK_F6)
		{
			if (Monster[0] == false)
			{
				Monster[1] = !Monster[1];

				Monster[0] = true;
			}
			else
			{
				Monster[1] = !Monster[1];

				Monster[0] = false;
			}
		}

		if (wParam == VK_F7) // lado esquerdo ( andar)
		{
			if (AutoClick[1] == false) // Right
			{
				AutoClick[0] = !AutoClick[0];
				AutoClick[2] = false;

				if (AutoClick[0] == false)  // Left
				{
					KillTimer(Window, AUTOCLICK_LEFT);
					SendMessage(Window, WM_LBUTTONUP, NULL, NULL);
				}
				else
				{
					SetTimer(Window, AUTOCLICK_LEFT, 10, NULL);
				}
			}
		}

		if (wParam == VK_F8) // lado direito ( poder )
		{
			if (AutoClick[0] == false) // Left
			{
				AutoClick[1] = !AutoClick[1];
				AutoClick[2] = false;

				if (AutoClick[1] == false)  // Right
				{
					KillTimer(Window, AUTOCLICK_RIGHT);
					SendMessage(Window, WM_RBUTTONUP, NULL, NULL);
				}
				else
				{
					SetTimer(Window, AUTOCLICK_RIGHT, 10, NULL);
				}
			}
		}
	}

	switch (wParam)
	{
	case VK_F9:
	{
		if (GetForegroundWindow() == pGameWindow)
		{
			gTrayMode.Toggle();
		}

		break;
	}
	break;
	default:
		return CallNextHookEx(NULL, Code, wParam, lParam);
		break;
	}

	return CallNextHookEx(m_Keyboard1, Code, wParam, lParam);
}

LRESULT CALLBACK WndProcEx(HWND Window, UINT Message, WPARAM W, LPARAM L)
{
	if (::Window == NULL)
	{
		::Window = Window;
	}

	switch (Message)
	{
	case WM_NCACTIVATE:
	{
		return FALSE;
	}
	break;
	// ----
	case WM_TIMER:
	{
		switch (W)
		{
		case AUTOCLICK_LEFT:
		{
			if (AutoClick[0] == true)
			{
				SendMessage(Window, (AutoClick[2] == true) ? WM_LBUTTONUP : WM_LBUTTONDOWN, NULL, NULL);
				AutoClick[2] = !AutoClick[2];
			}
		}
		break;
		case AUTOCLICK_RIGHT:
		{
			if (AutoClick[1] == true)
			{
				SendMessage(Window, (AutoClick[2] == true) ? WM_RBUTTONUP : WM_RBUTTONDOWN, NULL, NULL);
				AutoClick[2] = !AutoClick[2];
			}
		}
		break;
		}
	}
	break;
	}

	return CallWindowProc(WndProc, Window, Message, W, L);
}