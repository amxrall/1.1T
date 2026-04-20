#include "StdAfx.h"

pDrawText2			MU_DrawTextOut = (pDrawText2)(iDraw_Text);
pLoadImage2			MU_LoadImage = (pLoadImage2)(iLoad_Image);
pLoadImage2			MU_LoadAlpha = (pLoadImage2)(iLoad_Alpha);
pDrawToolTip		MU_DrawToolTip = (pDrawToolTip)(iDraw_ToolTip);

sTime s_Time;

CInterface gInterface;

extern char g_FPSString[32];

CInterface::CInterface()
{
	this->ExToolTipShow = false;
}

void CInterface::Load()
{
	this->BindObject(eTest, 0x7902, 78, 78, -1, -1);

	SetHook((LPVOID)this->Work, (LPVOID)0x00596E7F, ASM::CALL);
}

#define UnknownFunc3 ((bool(__cdecl*)(char Arg1)) 0x0060CB90)

void CInterface::Work()
{
	// ---
	s_Time.Hour = 25;
	UnknownFunc3(1);
	gInterface.CordRun();
	// ---
	//gInterface.DrawExtraItemInfo();
	// ---
	pDrawInterface();
}

void CInterface::CordRun()
{
	/*char szBuffer[256] = {0};
	// ---
	pSetBlend(true);
	// ---
	sprintf(szBuffer, "Cord X : %d | Cord Y : %d", pCursorX, pCursorY);
	// ---
	pDrawText(0, 0, szBuffer);*/

	float StartX = (1 / 1) - (1 / 1);

	SYSTEMTIME t = { NULL };
	// ----
	GetLocalTime(&t);
	// ----
	if (gProtect.m_Data.Relogio == 1)
	{
		char szTemp[256] = { NULL };
		sprintf(szTemp, "Hora:[%02d:%02d:%02d]", t.wHour, t.wMinute, t.wSecond);

		// ----
		MU_DrawToolTip(39, 3, szTemp);
	}

	// FPS no canto superior direito
	MU_DrawToolTip((int)(gWindow.iSizeX - 80), 3, g_FPSString);

	/*float StartX111 = (100 / 10) - (1 / 1);
	char szTemp2[256] = { NULL };
	sprintf(szTemp2, "www.stylemu.net");
	MU_DrawTextOut(StartX111 + 100, 424, szTemp2, 0, 0, 0);*/

	// ---
	MU_LoadAlpha("Customs\\Interface\\Patente2.tga", eTest, 0x2600, 0x2900, 0, 1);
	//pDrawGUI(0x14, StartX + 370, + 60, 70.0, 70.0, 0, 0, 0.8000, 0.7000, 1, 1);
}

void CInterface::DrawGUI(int ObjectId, float X, float Y, float Width, float Height, float ScaleX, float ScaleY)
{
	pDrawGUI(ObjectId, X, Y, Width, Height, 0, 0, ScaleX, ScaleY, 1, 1);
}

void CInterface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick = 0;
	this->Data[MonsterID].OnClick = false;
	this->Data[MonsterID].OnShow = false;
	this->Data[MonsterID].ModelID = ModelID;
	this->Data[MonsterID].Width = Width;
	this->Data[MonsterID].Height = Height;
	this->Data[MonsterID].X = X;
	this->Data[MonsterID].Y = Y;
	this->Data[MonsterID].MaxX = X + Width;
	this->Data[MonsterID].MaxY = Y + Height;
	this->Data[MonsterID].Attribute = 0;
}

void CInterface::LoadImage(int Type, char * Folder, int ImageID)
{
	switch (Type)
	{
	case 0:
	{
		pLoadImage(Folder, ImageID, 0x2600, 0x2900, 0, 1); // -> JPG
														   //pLoadImage("Customs\\Interface\\Patente2.tga", eTest, 0x2601, 0x2901, 0, 1);
	}
	break;
	case 1:
	{
		pLoadImageTga(Folder, ImageID, 0x2600, 0x2900, 0, 1);// -> TGA
		pLoadImageTga("Customs\\Interface\\Patente2.tga", eTest, 0x2601, 0x2901, 0, 1);
		//pLoadImageTga("Customs\\Interface\\Patente2.tga", eTest, 0x2600, 0x2900, 0, 1); // -> TGA
	}
	break;
	}
}

bool CGetTime()
{
	if (s_Time.Second < 60)
	{
		++s_Time.Second;
		// ----
		if (s_Time.Second == 60)
		{
			s_Time.Second = NULL;
			// ----
			if (s_Time.Minute < 60)
			{
				++s_Time.Minute;
				// ----
				if (s_Time.Minute == 60)
				{
					s_Time.Minute = NULL;
					// ----
					if (s_Time.Hour < 24)
					{
						++s_Time.Hour;
						// ----
						if (s_Time.Hour == 24)
						{
							s_Time.Hour = NULL;
						}
					}
				}
			}
		}
		// ----
		return true;
	}
	// ----
	if (s_Time.Minute == 60)
	{
		// ----
		return true;
	}
	// ----
	return false;
}

bool CInterface::CheckWindowEx(int WindowID)
{
	return CheckWindows(WindowID);
}

bool CInterface::CheckWindowAll()
{
	if (CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(Character)
		|| CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(NPCShop)
		|| CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(Warehouse)
		|| CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(UnknownWindow1)// -> Maybe Trade
		|| CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(ChaosMachine)
		|| CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(PersonalStore)
		|| CheckWindowEx(PlayerInventory)
		&& CheckWindowEx(PetTrainer))
	{
		return false;
	}
	else if (CheckWindowEx(PlayerInventory))
	{
		return true;
	}
	// ----
	return false;
}

bool CInterface::BoundingBox(int cx1, int cx2, int cy1, int cy2)
{
	if (pCursorX > cx1 && pCursorX < cx2 && pCursorY > cy1 && pCursorY < cy2)
	{
		return true;
	}
	// ----
	return false;
}

void CInterface::DrawExtraItemInfo()
{
	if (this->CheckWindowAll() == true && this->BoundingBox(42, 86, 467, 506) && this->ExToolTipShow == true)
	{
		GLSwitch();
		SetBlend(true);
		glColor4f(1.0f, 1.0f, 1.0f, 0.800001f);
		gInterface.LoadImage(1, "Custom\\Interface\\ToolTip.tga", 0x50);
		// ----
		if (gWindow.iSizeX == 1024 && gWindow.iSizeY == 600)
		{
			gInterface.DrawGUI(0x50, 694.5f, 65.0f, 160.0f, 160.0f, 1.0f, 1.0f);
		}
		else if (gWindow.iSizeX == 1024 && gWindow.iSizeY == 768)
		{
			gInterface.DrawGUI(0x50, 694.5f, 65.0f, 160.0f, 160.0f, 1.0f, 1.0f);
		}
		else if (gWindow.iSizeX == 640 && gWindow.iSizeY == 480)
		{
			gInterface.DrawGUI(0x50, 418.5f, 55.0f, 160.f, 160.0f, 1.0f, 1.0f);
		}
		// ----
		GLSwitchBlend();
		glColor3f(1.0f, 1.0f, 1.0f);
		GLSwitch();
	}
}

DWORD WINAPI TimeThread(LPVOID lpParam)
{
	while (true)
	{
		if (s_Time.Hour != 25)
		{
			CGetTime();
		}
		// ----
		Sleep(1000);
	}
	// ----
	return TRUE;
}