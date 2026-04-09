// CannonTower.h: interface for the CCannonTower class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CANNONTOWER_H__DD8C3ABB_D613_4E50_B4F1_0127230C40BC__INCLUDED_)
#define AFX_CANNONTOWER_H__DD8C3ABB_D613_4E50_B4F1_0127230C40BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if (GS_CASTLE==1)

struct PMSG_DURATION_MAGIC_SEND
{
	/*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
	/*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char MagicNumber;
	/*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberH;
	/*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char NumberL;
	/*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char X;
	/*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char Y;
	/*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Dir;
};
// <size 0x9>

class CCannonTower
{
public:
	CCannonTower();
	virtual ~CCannonTower();
	void CannonTowerAct(int iIndex);
};

extern CCannonTower g_CsNPC_CannonTower;

#endif

#endif // !defined(AFX_CANNONTOWER_H__DD8C3ABB_D613_4E50_B4F1_0127230C40BC__INCLUDED_)
