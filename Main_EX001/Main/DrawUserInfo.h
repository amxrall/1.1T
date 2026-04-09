#ifndef _DRAW_USER_INFO_H
#define _DRAW_USER_INFO_H

struct DRAW_USER_DATA
{
	bool bEnabled;
	bool bSelect;
	bool bLayout;
	bool bWindow;
	// ---
	WORD m_Index;
	DWORD m_Resets;
	DWORD m_MResets;
	WORD m_Level;
	DWORD m_Kills;
	DWORD m_Deads;
	WORD m_For;
	WORD m_Vit;
	WORD m_Ene;
	WORD m_Agi;
	WORD m_Com;
	WORD m_Classe;
	WORD m_Rank;
	char m_Vip[20];
	BOOL m_Enabled;
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;
	char szTitleRank[20];
};
enum TextColor
{
	White = 0x00,
	Blue = 0x01,
	Red = 0x02,
	Gold = 0x03,
	Green = 0x04,
	WhiteRed = 0x05,
	Violet = 0x06,
	WhiteBlue = 0x07,
	WhiteBeige = 0x08,
	GreenBlue = 0x09,
	Gray = 0x0A,
	DarkViolet = 0x0B,
};
class CDrawUserInfo
{
public:
	void Run();
	void InitView();
	void Patente();
	// ---
	DRAW_USER_DATA m_Data;
};

extern CDrawUserInfo gDrawUserInfo;

#endif