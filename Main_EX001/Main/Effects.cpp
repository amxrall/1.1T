#include "StdAfx.h"

cEffects gEffects;

cEffects::cEffects()
{
	// -> Constructor
	this->Init();
}

cEffects::~cEffects()
{
	// -> Destructor
}

void cEffects::Init()
{
	this->m_Sprite.clear();
	this->m_Effect.clear();
	this->m_Particle.clear();
}

void cEffects::Draw(LPOBJMODEL Owner, int ObjectId, vec3_t Light, float Alpha, int ItemLevel, int NewOption, int SetOption, int Select, int RenderType)
{
	vec3_t WorldPosition = { 0.0f,0.0f,0.0f };
	vec3_t Position = { 0.0f,0.0f,0.0f };
	vec3_t vColor = { 0.0f,0.0f,0.0f };
	vec3_t vAngle = { 0.0f,0.0f,0.0f };
	// ----
	cModel *Obj = &Models[ObjectId];
	// ----
	for (std::vector<pSpriteEffect>::iterator it = gEffects.m_Sprite.begin(); it != gEffects.m_Sprite.end(); it++)
	{
		if (it->ObjectId == ObjectId)
		{
			Obj->TransformPosition(BoneTransform[it->BoneId], Position, WorldPosition, true);
			Vector(it->Color[0], it->Color[1], it->Color[2], vColor);
			// ----
			pCreateSprite(it->EffectId, WorldPosition, it->Scale, vColor, Owner, it->Position, it->SubType);
		}
	}
	// ----
	for (std::vector<pCreateEffects>::iterator it = gEffects.m_Effect.begin(); it != gEffects.m_Effect.end(); it++)
	{
		if (it->ObjectId == ObjectId)
		{
			Obj->TransformPosition(BoneTransform[it->BoneId], Position, WorldPosition, true);
			Vector(it->Color[0], it->Color[1], it->Color[2], vColor);
			// ----
			pCreateEffect(it->EffectId, WorldPosition, Owner->Angle, vColor, it->SubType, Owner, NONE, NULL, NULL, NULL, NULL);
		}
	}
	// ----
	for (std::vector<pParticleEffect>::iterator it = gEffects.m_Particle.begin(); it != gEffects.m_Particle.end(); it++)
	{
		if (it->ObjectId == ObjectId)
		{
			Obj->TransformPosition(BoneTransform[it->BoneId], Position, WorldPosition, true);
			Vector(it->Color[0], it->Color[1], it->Color[2], vColor);
			// ----
			pCreateParticle(it->EffectId, WorldPosition, Owner->Angle, vColor, it->SubType, it->Scale, Owner);
		}
	}
	// ----
	pRenderPartObjectEffect(Owner, ObjectId, Light, Alpha, ItemLevel, NewOption, SetOption, Select, RenderType);
}

void cEffects::Load()
{
	if (gEncode.Load(EFFECT_FILE))
	{
		WZSMDToken Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 0))
		{
			MessageBox(NULL, "Section: 0 Sprites", EFFECT_FILE, MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
		}
		// ----
		this->Init();
		// ----
		int Group = 0;
		int Index = 0;
		// ----
		pSpriteEffect Sprite;
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			memset(&Sprite, NULL, sizeof(Sprite));
			// ----
			Group = gEncode.GetInt();		Token = gEncode.GetToken();
			Index = gEncode.GetInt();		Token = gEncode.GetToken();
			// ----
			Sprite.ObjectId = ITEM_ID(Group, Index);
			// ----
			Sprite.EffectId = gEncode.GetInt();		Token = gEncode.GetToken();
			Sprite.BoneId = gEncode.GetInt();		Token = gEncode.GetToken();
			Sprite.Scale = gEncode.GetFloat();	Token = gEncode.GetToken();
			Sprite.Color[0] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Sprite.Color[1] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Sprite.Color[2] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Sprite.Position = gEncode.GetFloat();	Token = gEncode.GetToken();
			Sprite.SubType = gEncode.GetInt();

			this->m_Sprite.push_back(Sprite);
		}
		// ----
		Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 1))
		{
			MessageBox(NULL, "Section 1: Effects", EFFECT_FILE, MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
		}
		// ----
		pCreateEffects Effect;
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			memset(&Effect, NULL, sizeof(Effect));
			// ----
			Group = gEncode.GetInt();		Token = gEncode.GetToken();
			Index = gEncode.GetInt();		Token = gEncode.GetToken();
			// ----
			Effect.ObjectId = ITEM_ID(Group, Index);
			// ----
			Effect.EffectId = gEncode.GetInt();		Token = gEncode.GetToken();
			Effect.BoneId = gEncode.GetInt();		Token = gEncode.GetToken();
			Effect.Color[0] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Effect.Color[1] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Effect.Color[2] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Effect.SubType = gEncode.GetInt();		Token = gEncode.GetToken();
			Effect.Scale = gEncode.GetFloat();
			// ----
			this->m_Effect.push_back(Effect);
		}
		// ----
		Token = gEncode.GetToken();
		// ----
		if ((Token == END) || (gEncode.GetInt() != 2))
		{
			MessageBox(NULL, "Section: 2 Particles", EFFECT_FILE, MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
		}
		// ----
		pParticleEffect Particle;
		// ----
		while (true)
		{
			Token = gEncode.GetToken();
			// ----
			if (Token == END || lstrcmpi(gEncode.GetString(), "end") == 0)
			{
				break;
			}
			// ----
			memset(&Particle, NULL, sizeof(Particle));
			// ----
			Group = gEncode.GetInt();		Token = gEncode.GetToken();
			Index = gEncode.GetInt();		Token = gEncode.GetToken();
			// ----
			Particle.ObjectId = ITEM_ID(Group, Index);
			Particle.EffectId = gEncode.GetInt();		Token = gEncode.GetToken();
			Particle.BoneId = gEncode.GetInt();		Token = gEncode.GetToken();
			Particle.Color[0] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Particle.Color[1] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Particle.Color[2] = gEncode.GetFloat();	Token = gEncode.GetToken();
			Particle.SubType = gEncode.GetInt();		Token = gEncode.GetToken();
			Particle.Scale = gEncode.GetFloat();
			// ----
			this->m_Particle.push_back(Particle);
		}
		// ----
		if (this->m_Sprite.size() || this->m_Effect.size() || this->m_Particle.size())
		{
			SetOp((LPVOID)oRenderEffect_Call01, this->Draw, ASM::CALL);
			SetOp((LPVOID)oRenderEffect_Call02, this->Draw, ASM::CALL);
		}
		// ----
		gEncode.Close();
	}
	else
	{
		MessageBox(NULL, EFFECT_FILE, "Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
}