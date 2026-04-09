#include "StdAfx.h"

cModel *&Models = *(cModel**)oModelsClassPointer;
vec34_t* BoneTransform = (vec34_t*)(oBoneTransformPointer); // MAX BONE 200

cModel::cModel()
{
}

void cModel::TransformPosition(vec34_t Matrix, vec3_t Position, vec3_t WorldPosition, bool Translate)
{
	pTransformPosition(this, Matrix, Position, WorldPosition, Translate);
}