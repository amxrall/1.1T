#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "MathLib.h"
#include "Models.h"
#include "StdAfx.h"

typedef struct
{
	int		ObjectId;
	int		EffectId;
	int		BoneId;
	vec_t	Scale;
	vec3_t	Color;
	vec_t	Position;
	int		SubType;
} pSpriteEffect, *lpSpriteEffect;

typedef struct
{
	int		ObjectId;
	int		EffectId;
	int		BoneId;
	vec3_t	Color;
	int		SubType;
	vec_t	Scale;
} pCreateEffects, *lpCreateEffects;

typedef struct
{
	int		ObjectId;
	int		EffectId;
	int		BoneId;
	vec3_t	Color;
	int		SubType;
	vec_t	Scale;
} pParticleEffect, *lpParticleEffect;

typedef struct
{
	int		ObjectId;
	int		EffectId;
	int		BoneId;
	vec_t	Scale;
	vec3_t	Color;
	vec_t	Position;
	int		SubType;
} pPetSpriteEffect, *lpPetSpriteEffect;

typedef struct
{
	int		ObjectId;
	int		EffectId;
	int		BoneId;
	vec3_t	Color;
	int		SubType;
	vec_t	Scale;
} pPetCreateEffects, *lpPetCreateEffects;

typedef struct
{
	int		ObjectId;
	int		EffectId;
	int		BoneId;
	vec3_t	Color;
	int		SubType;
	vec_t	Scale;
} pPetParticleEffect, *lpPetParticleEffect;

typedef struct
{
	DWORD	Type;
	DWORD	Index;
	CHAR	Name[32];
	BOOL	IsFlyer;
}CustomPets, *lpCustomPets;

typedef struct	//-> Complete (size: 80)
{
	/*+0*/		WORD	Index;
	/*+2*/		int		Level;
	/*+6*/		char	Unknown6;
	/*+7*/		char	Unknown7;
	/*+8*/		char	Unknown8;
	/*+9*/		short	DamageMin;
	/*+11*/		short	DamageMax;
	/*+13*/		char	Unknown13;
	/*+14*/		short	Unknown14;
	/*+16*/		short	Unknown16;
	/*+18*/		char	Unknown18;
	/*+19*/		char	Unknown19;
	/*+20*/		short	Unknown20;
	/*+22*/		char	Durability;
	/*+23*/		char	ExcellentOption;
	/*+24*/		char	AncientOption;
	/*+25*/		short	ReqStrenght;
	/*+27*/		short	ReqDextirity;
	/*+29*/		short	ReqEnergy;
	/*+31*/		short	ReqVitality;
	/*+33*/		short	ReqCommand;
	/*+35*/		short	ReqLevel;
	/*+37*/		char    SpecialCount;
	/*+38*/		WORD	SpecialType[8];
	/*+54*/		BYTE	SpecialValue[8];
	/*+62*/		int		UniqueID;
	/*+66*/		char	ActiveSlot;
	/*+67*/		char 	PosX;
	/*+68*/		char 	PosY;
	BYTE gap[11];
	/*+80*/		BYTE	Unknown80;
}tagITEM, *lpITEM;

// -> 1.01.46 (Total size: ???)
typedef struct
{
	BYTE		gap00[2];
	/*+2*/		DWORD		dwObjectID;
	BYTE		gap01[1];
	/*+4*/		BYTE		IsRender;
	BYTE		gap02[12];
	/*+16*/		vec3_t		Position;
	/*+28*/		vec3_t		Angle;
	BYTE		gap03[224];
	/*+260*/	vec3_t		WorldPos;
	BYTE		gap04[503];
	/*+776*/	WORD		PetSlot;
	BYTE		gap05[201];
	/*+978*/	BYTE		IsSafeZone;
}OBJMODEL, *LPOBJMODEL;//Character_Struct

// Class: 7D14050 Size: 452
typedef struct
{
	/*+1*/		char		IsItem;
	/*+2*/		short		ItemID;
	/*+4*/		BYTE		IsBug;
	/*+5*/		BYTE		Unknown5;
	/*+6*/		BYTE		Unknown6;
	/*+7*/		BYTE		Unknown7;
	/*+8*/		BYTE		Unknown8;
	/*+12*/		float		Size;
	/*+16*/		vec3_t		Position;
	/*+28*/		vec3_t		Angle;
	/*+36*/		char		OwnerName[32];
	BYTE		gap00[19];
	/*+88*/		BYTE		Unknown88;
	BYTE		gap01[7];
	/*+96*/		int			OwnerObj;		//Unknown96
	/*+100*/	BYTE		Unknown100;
	/*+104*/	float		Unknown104;
	BYTE		gap02[103];
	/*+212*/	vec3_t		Unknown212;		// +212 // +216 // +220
	BYTE		gap03[3];
	/*+228*/	BYTE		Unknown228;
	BYTE		gap04[7];
	/*+236*/	BYTE		Unknown236;
	/*+240*/	vec3_t		Unknown240;		// +240 // +244 // +248
	/*+252*/	vec3_t		Unknown252;		// +252 // +256 // +260
	/*+264*/	vec3_t		Unknown264;		// +264 // +268 // +272
	/*+276*/	BYTE		Unknown276;
	BYTE		gap05[2];
	/*+280*/	BYTE		Unknown280;
	BYTE		gap06[79];
	/*+360*/	BYTE		Unknown360;
	/*+361*/	BYTE		Unknown361;
	/*+364*/	vec3_t		Unknown364;		// +364 // +368 // +372
	BYTE		gap07[75];					// Total Size: +452
}CHARACTERSTRUCT, *LPCHARACTERSTRUCT;

// Total Size: ???
typedef struct
{
	BYTE		gap[4];
	/*+4*/		vec3_t		PetPosition;	// +4 // +8 // +12
}PETSTRUCT, *LPPETSTRUCT;//Pet_Struct

// Total Size: ???
typedef struct
{
	BYTE		gap[12];
	/*+16*/		vec3_t		SkeletonPosition;	// +16 // +20 // +24
	/*+24*/		vec3_t		SkeletonAngle;		// +24 // +28 // +32
	/*+36*/		BYTE		Unknown36;
}CHARACTERMACHINESTRUCT, *LPCHARACTERMACHINESTRUCT;

#endif	// __STRUCTS_H__