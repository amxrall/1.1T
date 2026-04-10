// GlowManager.cpp
#include "StdAfx.h"

CGlowManager gGlowManager;

void CGlowManager::Init()
{
	this->iCount = 0;
	memset(this->m_Data, 0, sizeof(this->m_Data));
}

void CGlowManager::Load()
{
	this->Init();

	if (gEncode.Load(GLOW_FILE) == 0)
	{
		MessageBox(NULL, "Glow.paq file not found", "Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
		return;
	}

	while (true)
	{
		WZSMDToken Token = gEncode.GetToken();

		if (Token == END)
		{
			break;
		}

		if (this->iCount >= 512)
		{
			MessageBox(NULL, "Glow.paq has more than 512 entries", "Error", MB_OK | MB_ICONERROR);
			break;
		}

		this->m_Data[this->iCount].iType = gEncode.GetInt();

		Token = gEncode.GetToken();
		this->m_Data[this->iCount].iIndex = gEncode.GetInt();

		Token = gEncode.GetToken();
		this->m_Data[this->iCount].fRed = gEncode.GetFloat();

		Token = gEncode.GetToken();
		this->m_Data[this->iCount].fGreen = gEncode.GetFloat();

		Token = gEncode.GetToken();
		this->m_Data[this->iCount].fBlue = gEncode.GetFloat();

		this->iCount++;
	}

	if (this->iCount > 0)
	{
		SetOp((LPVOID)0x005069A2, this->gObjItemGlowEx, ASM::CALL);
		SetOp((LPVOID)0x005F8445, this->gObjItemGlowEx, ASM::CALL);
		SetOp((LPVOID)0x005F85E0, this->gObjItemShineEx, ASM::CALL);
	}
}

void CGlowManager::gObjItemShineEx(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool BalrogMode)
{
	for (int i = 0; i < gGlowManager.iCount; i++)
	{
		if (ObjectId == ITEM_ID(gGlowManager.m_Data[i].iType, gGlowManager.m_Data[i].iIndex))
		{
			Vector(
				gGlowManager.m_Data[i].fRed,
				gGlowManager.m_Data[i].fGreen,
				gGlowManager.m_Data[i].fBlue,
				Color
			);
			return;
		}
	}

	gObjItemShine(ObjectId, Arg2, Arg3, Color, BalrogMode);
}

void CGlowManager::gObjItemGlowEx(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool BalrogMode)
{
	for (int i = 0; i < gGlowManager.iCount; i++)
	{
		if (ObjectId == ITEM_ID(gGlowManager.m_Data[i].iType, gGlowManager.m_Data[i].iIndex))
		{
			Vector(
				gGlowManager.m_Data[i].fRed,
				gGlowManager.m_Data[i].fGreen,
				gGlowManager.m_Data[i].fBlue,
				Color
			);
			return;
		}
	}

	gObjItemGlow(ObjectId, Arg2, Arg3, Color, BalrogMode);
}