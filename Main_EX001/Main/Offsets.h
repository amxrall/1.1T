#pragma once


#define Naked					__declspec(naked)
#define GLOW_FILE				".\\Data\\Customs\\Glow.gbt"
#define EFFECT_FILE				".\\Data\\Customs\\Effect.gbt"
#define EFFECTPET_FILE			".\\Data\\Customs\\PetsEffect.gbt"
#define MUUNPET_FILE			".\\Data\\Customs\\PetsLoad.gbt"

// ---
#define FOLDER_ITEM							"Data\\Item\\"
#define FOLDER_PLAYER						"Data\\Player\\"
#define FOLDER_SKILL						"Data\\Skill\\"

#define pShowModel							((int(*)(int, int, char, int, float*, int, char))(0x5CF110))
#define pLoadModel							((void(*)(int, const char*, const char*, int))(0x5FACA0))
#define pLoadTexture						((void(*)(int, const char*, GLint, GLint, GLsizei))(0x5FA860))
#define pLoadModels							((void(*)())(0x5FD0E0))
#define pLoadTextures						((void(*)())(0x5FE910))
#define pLoadInterfaces						((void(*)())(0x6096B0))

#define pMaxTexture							*(DWORD*)(0x7D16FE8)

#define MakePreviewCharSet	    ((void(__cdecl*)(int aIndex,BYTE *CharSet,int Struct,int Mode))0x50A590)
#define ItemSetOptionAdd        ((void(*)(LPVOID, unsigned __int8, unsigned __int8, BYTE)) 0x540A50)
#define	pLoadItemModel			((void(*)(int,char*,char*,int))0x005FACA0)	  // 1.1t
#define	pLoadItemTexture		((void(*)(int,char*,int,int,int))0x005FA860)  // 1.1t

// ----

#define MAX_DYNAMIC_WING_EFFECT 3000
#define MAX_CUSTOM_WING_EFFECT 3000
#define ITEM_BASE_MODEL 0x203
#define MAX_CUSTOM_ITEMS		256


#define ITEMGET(X,Y)            ((X) * 512 + (Y))
#define ITEM_ID(X,Y)	        ((X  * 512) + Y + 515)
#define ITEMTYPE(x)			    ((x) / 512)
#define ITEMINDEX(x)		    ((x) % 512)
#define MAIN_RESOLUTION         0x5750320
#define MAIN_RESOLUTION_X       0x6C4158
#define MAIN_RESOLUTION_Y       0x6C415C
#define MAIN_FONT_SIZE          0x773D130
#define MAKE_NUMBERW(x,y)		((WORD)(((BYTE)((y)&0xFF)) | ((BYTE)((x)&0xFF) << 8)))

// ---
#define ITEM_ATTRIBUTE_ADDR 0x203
#define MAX_ITEM_TYPE 512
#define GET_ITEM_MODEL(x,y) ((((x)*MAX_ITEM_TYPE)+(y))+ITEM_ATTRIBUTE_ADDR)
// ---
#define pDrawGUI				((void(__cdecl*)(int ObjectId, float X, float Y, float Width, float Height, int Arg6, int Arg7, float Width2, float Height2, char Arg10, float Arg11)) 0x0060DCF0) // 0x0060DCF0
#define pDrawInterface			((void(__cdecl*)()) 0x00598C30)
#define pLoadImage				((void(*)(char * Folder, int ImageID, int BlendType, int a4, int a5, int a6)) 0x0062C1E0)
#define pLoadImageTga			((void(*)(char * Folder, int ImageID, int BlendType, int a4, int a5, int a6)) 0x0062C670)
#define pDrawImage              ((void(__cdecl*)(int ImageID, float X, float Y, float Width, float Height, int Arg6, int Arg7, float Width2, float Height2, char Arg10, float Arg11)) 0x0062C670) //5E0C03
#define pGameWindow	*(HWND*)0x0575052C

// -------
#define oModelsClassPointer		0x05756AB8
#define oBoneTransformPointer	0x0689E7FC
#define pTransformPosition		((int(__thiscall*)(void *This,vec34_t Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate))0x004E4610)
#define pTransformPositionEx	((int(__thiscall*)(LPVOID This,int Matrix,vec3_t Position,vec3_t WorldPosition,bool Translate))0x004E4610)
#define pCreateSprite			((int(__cdecl*)(int Type,vec3_t Position,float Scale,vec3_t Light,LPOBJMODEL Owner,float Rotation,int SubType))0x0053DE20)
#define pCreateEffect			((void(__cdecl*)(int Type,vec3_t WorldPosition,vec3_t Angle,vec3_t Light,int SubType,LPOBJMODEL Owner,short PKKey,BYTE Skill,float Scale,BYTE SkillSerial,vec3_t SkillAngle))0x0050F3E0)	// ? 0x00526280
#define pCreateParticle			((int(__cdecl*)(int Type,vec3_t Position,vec3_t Angle,vec3_t Light,int SubType,float Scale,LPOBJMODEL Owner))0x005353B0)
#define pPlayerState			*(int*)0x006C41C0
#define oRenderEffect_Call01	0x0050074D
#define oRenderEffect_Call02	0x005FA6BB
#define pRenderPartObjectEffect	((void(__cdecl*)(LPOBJMODEL Owner,int ObjectId,vec3_t Light,float Alpha,int ItemLevel,int NewOption,int SetOption,int Select,int RenderType))0x005F8640)

// ---

#define	pCursorX				*(int*)0x7D17158
#define	pCursorY				*(int*)0x7D1715C
#define pDrawText				((int(*)(int PosX, int PosY, LPCSTR lpText)) 0x0060FAC0)
#define pDrawLegend				((char(*)(int PosX, int PosY, LPCSTR lpText)) 0x005487E0)

// ---
#define WndProc                 (WNDPROC)(0x4A9BD0)
#define CharView		        *(DWORD*)0x6C42C8  
#define DrawBar                 ((double(__cdecl*)(float a1, float a2, int a3, float a4, float a5)) 0x60DA80)
#define DrawTab                 ((int(__cdecl*)(signed int a1, signed int a2, LPCSTR lpMultiByteStr)) 0x5487E0)
#define DrawInfo                ((int(__cdecl*)(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)) 0x548620)
#define DrawDamage              ((void(__cdecl*)(int a1, int a2, int a3, float a4, char a5, char a6)) 0x53DA80)
#define ProtocolCore	        ((BOOL(*)(int, LPBYTE, int, int)) 0x4DB720)
#define MainSpeedFrame1			(float*)(0x6A79D0)
#define MainSpeedFrame2			(float*)(0x6A79A4)
#define LevelUpAddPoint         ((void(*)(struct PMSG_LVPOINTADDRESULT*))(0x4CC570))
#define LevelUpRecv             ((void(*)(struct PMSG_LEVELUP*))(0x4CC240))
#define AllowStaticEffect		((void(__thiscall*)(float *a1, float *a2, float *a3, vec3_t *VecPos, char a5)) 0x4E4610)
#define PlayDynamicEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, int Arg2, float * Color, int Arg4, float Arg5, int Arg6)) 0x5353B0)
#define PlayStaticEffect		((int(__cdecl*)(DWORD ModelID, int a2, int a3, int a4, float *a5, int a6)) 0x4FFFD0)
#define GetPosFromAngle		    ((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY)) 0x60C740)
#define SetBlend				((void(__cdecl*)(BYTE Mode)) 0x60CB90)
#define GLSwitchBlend			((void(__cdecl*)()) 0x60CC20)
#define GLSwitch				((void(__cdecl*)()) 0x60CB10)
#define DrawBarForm			    ((void(__cdecl*)(float PosX, float PosY, float Width, float Height)) 0x60DC30)
#define pDrawBarForm			((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x60DC30)
#define ItemText                ((int(*)(int Arg1, const char * Text, ...)) 0x68EFC7)
#define DrawTextOut				((int(*)(int, int, char* Text, int, int, int)) 0x548620)
#define pDrawInfo				((int(__cdecl*)(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)) 0x00548620)// 1.01t ok

//#define SelectChar			    ((char(__cdecl*)()) 0x43FE20)
#define MakePreviewCharSet	    ((void(__cdecl*)(int aIndex,BYTE *CharSet,int Struct,int Mode))0x50A590)
#define ItemSetOptionAdd        ((void(*)(LPVOID, unsigned __int8, unsigned __int8, BYTE)) 0x540A50)


// ---
// Offsets Descrição
#define pDrawColorText			((int(__cdecl*)(char * Text, int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align)) oItemText_Color)
#define oItemText_Color			0x7641DD4 //1.04j
#define oItemText_Weight		0x7670800 //1.04j
#define oItemText_Line			0x788C850 //1.01t
#define oItemText_Index			0x785A110 //1.01t
// ---
#define NONE					-1

enum eObjType
{
	Player = 1,
	pMonster = 2,
	NPC = 4,
	None = 8,
};

enum ObjWindow		// -> Complete
{
	FriendList = 1,
	MoveList = 2,
	//Party			= 3,
	//Quest			= 4,
	//Guild			= 6,
	Trade = 7,
	//Warehouse		= 8,
	Quest = 8,
	//ChaosBox		= 9,
	//CommandWindow	= 10,
	//PetInfo		= 11,
	//Shop			= 12,
	//PlayerInventory= 13,
	//Store			= 14,
	//OtherStore	= 15,
	//Character		= 16,
	ChatWindow = 33,
	Options = 35,
	Help = 36,
	FastDial = 39,
	Warehouse = 64,
	ChaosMachine = 256,
	UnknownWindow2 = 262144,
	PetTrainer = 32768,
	PlayerInventory = 67108864,
	CommandWindow = 512,
	PetInfo = 1024,
	UnknownWindow1 = 2048,
	Character = 33554432,
	PersonalStore = 131072,
	NPCShop = 65536,
	UnknownWindow3 = 524288,
	UnknownWindow4 = 4096,
	Guild = 16,
	Party = 4,
	UnknownWindow5 = 1048576,
	UnknownWindow = 16384,
};

