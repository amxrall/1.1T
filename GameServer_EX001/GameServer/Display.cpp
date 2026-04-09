#include "StdAfx.h"
#include "GameMain.h"
#include "wsJoinServerCli.h"
#include "DSProtocol.h"

char * TitleText[1] =
{
#if(GS_CASTLE == 0)
	"GBTeam Emulador"
#else
    "[+            Castle            +]"
#endif
};



cDisplay::cDisplay()
{
	this->Font = CreateFont(110, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, "Times");
	this->Font1 = CreateFont(45, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_MODERN, "Times");
	this->Background = CreateSolidBrush(RGB(245, 168, 54)); // LOGO GBTEAM
	// ---

	this->Background1 = CreateSolidBrush(RGB(0, 255, 68)); // BLOCO 01 - Online
#if(PROTECT_STATE ==1)
	this->Background2 = CreateSolidBrush(RGB(245, 168, 54)); // BLOCO 02 - Premium
#else
	this->Background2 = CreateSolidBrush(RGB(0, 0, 0)); // BLOCO 02 - Free
#endif
	this->Background3 = CreateSolidBrush(RGB(245, 168, 54)); // BLOCO 03 - Updates
	this->Background4 = CreateSolidBrush(RGB(245, 168, 54)); // BLOCO 03 - Updates

}

cDisplay::~cDisplay()
{
	DeleteObject(this->Font);
	DeleteObject(this->Font1);
	DeleteObject(this->Background);
	DeleteObject(this->Background1);
	DeleteObject(this->Background2);
	DeleteObject(this->Background3);
	DeleteObject(this->Background4);
}

void cDisplay::ViewPaint(HWND hWnd)
{
	int MonsterCount = 0, FreeCount = 0, VipCount = 0, Staffers = 0, TotalCount = 0;

	for (int i = 0; i < OBJMAX; i++)
	{
		if (i < OBJ_STARTUSERINDEX)
		{
			if (gObj[i].Type != OBJ_USER && gObj[i].Connected == PLAYER_PLAYING)
			{
				MonsterCount++;
			}
		}
		else
		{
			if (gObj[i].Type == OBJ_USER && gObj[i].Connected == PLAYER_PLAYING)
			{
				if (gObj[i].Custom->VipCount == 0 && gObj[i].Authority == 1)
				{
					FreeCount++;
				}

				if (gObj[i].Custom->VipCount > 0 && gObj[i].Authority == 1)
				{
					VipCount++;
				}

				if (gObj[i].Authority > 1)
				{
					Staffers++;
				}

				TotalCount++;
			}
		}
	}

	gObjTotalUser = TotalCount;

	wsprintf(this->Buffer, "MONSTERS: %d       -       FREE PLAYERS: %d       -       VIP PLAYERS: %d       -       STAFFERS: %d       -       TOTAL ONLINE: %d       -       MAX DE USUÁRIOS: %d", MonsterCount, FreeCount, VipCount, Staffers, TotalCount, gServerMaxUser);

	RECT Rect;
	RECT Rect1;
	RECT Rect2;
	RECT Rect3;
	RECT Rect4;
	HDC Hdc = GetDC(hWnd);
	HDC Hdc1 = GetDC(hWnd);
	HDC Hdc2 = GetDC(hWnd);
	HDC Hdc3 = GetDC(hWnd);
	HDC Hdc4 = GetDC(hWnd);

	int OldBkMode = SetBkMode(Hdc, TRANSPARENT);
	int OldBkMode1 = SetBkMode(Hdc1, TRANSPARENT);
	int OldBkMode2 = SetBkMode(Hdc2, TRANSPARENT);
	int OldBkMode3 = SetBkMode(Hdc3, TRANSPARENT);
	int OldBkMode4 = SetBkMode(Hdc4, TRANSPARENT);

	GetClientRect(hWnd, &Rect);
	GetClientRect(hWnd, &Rect1);
	GetClientRect(hWnd, &Rect2);
	GetClientRect(hWnd, &Rect3);
	GetClientRect(hWnd, &Rect4);


	// GBTeam
	Rect.top = 0; // referente ao quadro 01
	Rect.bottom = 100;

	//Version
	Rect4.top = 430; // Cima
	Rect4.left = 1180; // esquerda
	Rect4.right = 1390; // direia
	Rect4.bottom = 480; // baixo

	// Servidor Online
	Rect1.top = 490; // Cima
	Rect1.left = 1180; // esquerda
	Rect1.right = 1390; // direia
	Rect1.bottom = 540; // baixo

	// Premium
	Rect2.top = 550; // Cima
	Rect2.left = 1180; // esquerda
	Rect2.right = 1390; // direia
	Rect2.bottom = 600; // baixo

	//Update
	Rect3.top = 610; // Cima
	Rect3.left = 1180; // esquerda
	Rect3.right = 1390; // direia
	Rect3.bottom = 660; // baixo



	SetTextColor(Hdc, RGB(255, 255, 255)); // monster ,vip e etc;;;
	TextOut(Hdc, 100, 100, this->Buffer, strlen(this->Buffer));


	FillRect(Hdc, &Rect, Display.Background);
	FillRect(Hdc1, &Rect1, Display.Background1);
	FillRect(Hdc2, &Rect2, Display.Background2);
	FillRect(Hdc3, &Rect3, Display.Background3);
	FillRect(Hdc4, &Rect4, Display.Background4);

	HFONT OldFont = (HFONT)SelectObject(Hdc, Display.Font);
	HFONT OldFont1 = (HFONT)SelectObject(Hdc1, Display.Font1);
	HFONT OldFont2 = (HFONT)SelectObject(Hdc2, Display.Font1);
	HFONT OldFont3 = (HFONT)SelectObject(Hdc3, Display.Font1);
	HFONT OldFont4 = (HFONT)SelectObject(Hdc4, Display.Font1);

	// GBTEAM
	SetTextColor(Hdc, RGB(255, 255, 255));
	DrawText(Hdc, TitleText[0], 15, &Rect, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
	// ----

	// Servidor Online
	SetTextColor(Hdc1, RGB(255, 255, 255));
	DrawText(Hdc1, "Online", 7, &Rect1, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);




#if(PROTECT_STATE==1)
	// Premium
	SetTextColor(Hdc2, RGB(255, 255, 255));
	DrawText(Hdc2, GAMESERVER_NAME, 8, &Rect2, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

#else
	// Free
	SetTextColor(Hdc2, RGB(255, 0, 0));
	DrawText(Hdc2, GAMESERVER_NAME, 5, &Rect2, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

#endif

	
	// Updates
	SetTextColor(Hdc3, RGB(255, 255, 255));
	DrawText(Hdc3, UPDATES, 11, &Rect3, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

	// Version
	SetTextColor(Hdc4, RGB(255, 255, 255));
	DrawText(Hdc4, Version_GS, 9, &Rect4, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

	SelectObject(Hdc, OldFont);
	SetBkMode(Hdc, OldBkMode);
	ReleaseDC(hWnd, Hdc);

	//Online
	SelectObject(Hdc1, OldFont1);
	SetBkMode(Hdc1, OldBkMode1);
	ReleaseDC(hWnd, Hdc1);

	//Premium
	SelectObject(Hdc2, OldFont2);
	SetBkMode(Hdc2,OldBkMode2);
	ReleaseDC(hWnd, Hdc2);



	//Updates
	SelectObject(Hdc3, OldFont3);
	SetBkMode(Hdc3, OldBkMode3);
	ReleaseDC(hWnd, Hdc3);
	
	SelectObject(Hdc4, OldFont4);
	SetBkMode(Hdc4, OldBkMode4);
	ReleaseDC(hWnd, Hdc4);
}

cDisplay Display;