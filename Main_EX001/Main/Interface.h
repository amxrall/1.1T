#ifndef _INTERFACE_H
#define _INTERFACE_H

#define iDraw_Text				0x00548620
#define iLoad_Image				0x0062C1E0
#define iLoad_Alpha				0x0062C670
#define iDraw_ToolTip			0x005487E0

#define MAX_OBJECT			250

enum ObjectID
{
	eFlag01 = 1,
	eFlag02,
	eFlag03,
	eFlag04,
	eFlag05,
	eFlag06,
	eFlag07,
	eFlag08,
	eFlag09,
	eFlag10,
	eFlag11,
	eFlag12,
	eFlag13,
	eFlag14,
	eFlag15,
	eFlag16,
	eFlag17,
	eFlag18,
	eFlag19,
	eFlag20,
	eFlag21,
	eFlag22,
	eTest,
};

struct InterfaceObject
{
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
};

class CInterface
{
public:
	CInterface();
	void Load();
	static void Work();
	void CordRun();
	// ------
	bool CheckWindowEx(int WindowID);
	bool BoundingBox(int cx1, int cx2, int cy1, int cy2);
	bool CheckWindowAll();
	void DrawExtraItemInfo();
	// ---
	void DrawGUI(int ObjectId, float X, float Y, float Width, float Height, float ScaleX, float ScaleY);
	void LoadImage(int Type, char * Folder, int ImageID);
	void BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y);
	InterfaceObject Data[MAX_OBJECT];
public:
	bool ExToolTipShow;
};

struct sTime
{
	int Second;
	int Minute;
	int Hour;
};
extern CInterface gInterface;

typedef char * (__cdecl *pDrawText2) (int x, int y, LPCSTR Text, int BackgroundWidth, int AlignCenter, int a6);
extern pDrawText2 MU_DrawTextOut;

typedef void(*pLoadImage2) (char * Folder, int ImageID, int BlendType, int a4, int a5, int a6);
extern pLoadImage2 MU_LoadImage, MU_LoadAlpha;

typedef void(*pDrawToolTip) (int x, int y, char * Text);
extern pDrawToolTip MU_DrawToolTip;

#endif