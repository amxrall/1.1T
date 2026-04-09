#include "StdAfx.h"

CDrawUserInfo gDrawUserInfo;

void CDrawUserInfo::Run()
{
	VAngle Angle;
	// ---
	int PosX, PosY;
	// ---
	for (int i = 0; i < 400; i++)
	{
		DWORD pViewPort = (0x7424644 + 1060 * i);

		int index = *(WORD*)(pViewPort + 0x56);

		char* name = (char*)(pViewPort + 0x38); // corrigir
		// ---
		if ((*(BYTE*)pViewPort != 0) && (*(BYTE*)(pViewPort + 132) == 2))
		{
			Angle.X = *(float*)(pViewPort + 16);
			// ---
			Angle.Y = *(float*)(pViewPort + 20);
			// ---
			Angle.Z = *(float*)(pViewPort + 308) + *(float*)(pViewPort + 24) + 100.0f;
			// ---
			GetPosFromAngle(&Angle, &PosX, &PosY);
			// ---
			if ((pCursorX >= PosX) && ((float)pCursorX <= (float)PosX + 50) && (pCursorY >= PosY + 20) && (pCursorY < PosY + 85))
			{
				this->m_Data.bWindow = true;
			}
			else
			{
				this->m_Data.bWindow = false;
			}
		}
	}
	// ---
	this->InitView();
}
void CDrawUserInfo::InitView()
{
	if (this->m_Data.bWindow)
	{
		SetBlend(true);
		// ---
		glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
		// ---
		DrawBarForm(185.0f, 80.0f, 0.0f, 0);
		// ---
		LPCSTR MyString[] =
		{
			"Info Char",
		};
		// ---
		/*pDrawLegend(0, 0, "");
		glColor3f(1.0, 0.8, 0.0);
		pDrawText(-17, -70, MyString[0]);*/

		pDrawLegend(0, 0, "");
		glColor3f(1.0, 0.8, 0.0);
		pDrawText(300, 50, MyString[0]);
		// ---
		pDrawLegend(0, 0, "");
	}
}


void CDrawUserInfo::Patente()
{
// -----
	VAngle Angle;
	// ---
	int PosX, PosY;


	for (int i = 0; i < 400; i++)

	{
		DWORD pViewPort = *(DWORD*)(0x7424644) + (i * 1060);

		if ((*(BYTE*)(pViewPort + 132) == eObjType::Player))

			Angle.X = *(float*)(pViewPort + 864);

		Angle.Y = *(float*)(pViewPort + 868);

		Angle.Z = *(float*)(pViewPort + 872) + *(float*)(pViewPort + 0x344) + 100.0f;
		GetPosFromAngle(&Angle, &PosX, &PosY);
		// ----
		PosX -= 42;
		// ----
			SetBlend(true);
			// ---
			GLSwitchBlend();
			// antigo codigo
			LPCSTR MyString[] =
			{
				"Carrasco",
			};
			// ---
			pDrawLegend(0, 0, "");
			glColor3f(1.0, 0.8, 0.0);
			pDrawText(300, 70, MyString[0]);
			// ---
			pDrawLegend(0, 0, "");
			gInterface.DrawGUI(0x14, PosX + 370, +60, 70.0, 70.0, 0, 0); // imagem.
			pDrawGUI(0x14, PosX + 300, +60, 70.0, 70.0, 0, 0, 0.8000, 0.7000, 1, 1);
			// --
		}
}
