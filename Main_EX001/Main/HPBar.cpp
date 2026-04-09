#include "StdAfx.h"

std::vector<HEALTH_BAR> HealthBar;

void cHPBar::Clear()
{
	HealthBar.clear();
}

void cHPBar::Insert(short Index, BYTE Rate)
{
	HEALTH_BAR Bar;

	Bar.Index = Index;
	Bar.Rate = Rate;

	HealthBar.push_back(Bar);
}

HEALTH_BAR* cHPBar::Get(short Index)
{
	for (std::vector<HEALTH_BAR>::iterator it = HealthBar.begin(); it != HealthBar.end(); ++it)
	{
		if (it->Index == Index)
		{
			return &(*it);
		}
	}

	return NULL;
}

void cHPBar::Draw()
{
	SelectObject(*(HDC*)(0x57504DC), *(HFONT*)(0x575053C));

	int X = 0, Y = 0, Width = 80;
	VAngle Angle;
	SIZE Size;
	HEALTH_BAR* NewHealthBar;

	for (int i = 0; i < 400; i++)
	{
		DWORD ViewPort = *(DWORD*)(0x7424644) + (i * 1060);

		if ((*(BYTE*)ViewPort != 0) && (*(BYTE*)(ViewPort + 132) == 2))
		{
			NewHealthBar = HPBar.Get(*(WORD*)(ViewPort + 484));

			if (NewHealthBar == 0)
			{
				continue;
			}

			if (Monster[0] == false)
			{
				continue;
			}

			Angle.X = *(float*)(ViewPort + 16);
			Angle.Y = *(float*)(ViewPort + 20);
			Angle.Z = *(float*)(ViewPort + 308) + *(float*)(ViewPort + 24) + 100.0f;

			GetPosFromAngle(&Angle, &X, &Y);

			X -= (int)(floor(Width / 2.f));

			SetBlend(true);

			glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
			DrawBarForm((float)(X - 1), (float)(Y - 12), 2.f + (float)(Width), 17.f);

			glColor3f(0.9f, 0.f, 0.f);

			DrawBarForm((float)(X), 1.f + Y, (float)((NewHealthBar->Rate * Width) / 100.0f), 3.0f);

			GLSwitchBlend();

			GetTextExtentPoint(*(HDC*)(0x57504DC), (char*)(ViewPort + 457), strlen((char*)(ViewPort + 457)), &Size);
			Size.cx = 80 - (LONG)((float)(Size.cx) / *(float*)(0x574FE90));

			if (Size.cx < 0)
			{
				Size.cx = 0;
			}
			else
			{
				Size.cx /= 2;
			}

			glColor4f(1.f, 1.f, 1.f, 1.f);

			X += Size.cx;
			Y -= 9;

			if ((X >= 0 && X <= (640 - (Size.cx / 2))) && (Y >= 0 && Y <= 480))
			{
				wsprintf(HPBar.Buffer, "%s", (char*)(ViewPort + 457));
				DrawTextOut(X, Y, HPBar.Buffer, 0, 0, 0);
			}

			GLSwitch();
		}
		else if ((*(BYTE*)ViewPort != 0) && (*(BYTE*)(ViewPort + 0x84) == eObjType::Player))
		{
			Angle.X = *(float*)(ViewPort + 16);

			Angle.Y = *(float*)(ViewPort + 20);

			Angle.Z = *(float*)(ViewPort + 308) + *(float*)(ViewPort + 24) + 100.0f;

			GetPosFromAngle(&Angle, &X, &Y);

				/*glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
				// ---
				pDrawLegend(0, 0, "");
				glColor3f(1.0, 0.8, 0.0);
				pDrawText(320, 30, "Novato");*/
				// --
				//pDrawLegend(0, 0, ""); // -> Evitar Bugs
				//					OBJID    X      Y    WTH  HGHT  ARG6  ARG7 WTH2 HGHT2 
				//gInterface.DrawGUI(eTest, X + 50, 50, 50.0, 50.0, 0.6, 0.6); // esse ta ok 
				//gInterface.DrawGUI(eTest, X + 50, 50, 50, 50, -1, -1);
				//(int ObjectId, float X, float Y, float Width, float Height, int Arg6, int Arg7, float Width2, float Height2, char Arg10, float Arg11)) 0x0060DCF0) // 0x0060DCF0
		}

		GLSwitch();

		glColor3f(1.0f, 1.0f, 1.0f);
		// ----	

	}

	((void(*)())0x598350)();
}

cHPBar HPBar;