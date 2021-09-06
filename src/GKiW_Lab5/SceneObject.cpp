#include "stdafx.h"
CSceneObject::CSceneObject(void)
{
	Position.x = Position.y = Position.z = Rotation.x = Rotation.y = Rotation.z = 0.0f;
	isAlive = true;
}
CSceneObject::~CSceneObject(void)
{
}