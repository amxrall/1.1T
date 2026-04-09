#include "StdAfx.h"
// ---
CGlowManager gGlowManager;
// ---

void CGlowManager::Init()
{
	this->iCount = NULL;
	memset(this->m_Data, NONE, sizeof(this->m_Data));
}

void CGlowManager::Load()
{
	if (gEncode.Load(GLOW_FILE))
	{
		WZSMDToken Token = gEncode.GetToken();
		// ----
		this->Init();
		// ----
		while (TRUE)
		{
			Token = gEncode.GetToken();
			// ----
			if ((Token == END)) break;
			// ----
			this->m_Data[this->iCount].iType = gEncode.GetInt();
			// ----
			Token = gEncode.GetToken();
			this->m_Data[this->iCount].iIndex = gEncode.GetInt();
			// ----
			Token = gEncode.GetToken();
			this->m_Data[this->iCount].fRed = gEncode.GetFloat();
			// ----
			Token = gEncode.GetToken();
			this->m_Data[this->iCount].fGreen = gEncode.GetFloat();
			// ----
			Token = gEncode.GetToken();
			this->m_Data[this->iCount].fBlue = gEncode.GetFloat();
			// ----
			this->iCount++;
		}
		// ----
		if (this->iCount > NULL)
		{
			SetOp((LPVOID)0x005069A2, this->gObjItemGlowEx, ASM::CALL);
			SetOp((LPVOID)0x005F8445, this->gObjItemGlowEx, ASM::CALL);
			SetOp((LPVOID)0x005F85E0, this->gObjItemShineEx, ASM::CALL);
		}
	}
	else
	{
		MessageBox(NULL, "Glow.paq file not found", "Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(NULL);
	}
}

void CGlowManager::gObjItemShineEx(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool BalrogMode)
{
	for (int i = 0; i <= gGlowManager.iCount; i++)
	{
		if (ObjectId == ITEM_ID(gGlowManager.m_Data[i].iType, gGlowManager.m_Data[i].iIndex))
		{
			Vector(gGlowManager.m_Data[i].fRed, gGlowManager.m_Data[i].fGreen, gGlowManager.m_Data[i].fBlue, Color);
			break;
		}
		else
		{
			gObjItemShine(ObjectId, Arg2, Arg3, Color, BalrogMode);
		}
	}
}

void CGlowManager::gObjItemGlowEx(int ObjectId, float Arg2, float Arg3, vec3_t Color, bool BalrogMode)
{
	for (int i = 0; i <= gGlowManager.iCount; i++)
	{
		if (ObjectId == ITEM_ID(gGlowManager.m_Data[i].iType, gGlowManager.m_Data[i].iIndex))
		{
			Vector(gGlowManager.m_Data[i].fRed, gGlowManager.m_Data[i].fGreen, gGlowManager.m_Data[i].fBlue, Color);
			break;
		}
		else
		{
			gObjItemGlow(ObjectId, Arg2, Arg3, Color, BalrogMode);
		}
	}
}