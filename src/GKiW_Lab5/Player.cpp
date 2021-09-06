#include "stdafx.h"
CPlayer::CPlayer()
{
	pos.x = 0.0f;
	pos.y = 1.0f;
	pos.z = 4.0f;
	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = -1.0f;
	speed = 0.4f;
	velRX = 0.0f;
	velRY = 0.0f;
	velM = 0.0f;
	velS = 0.0f;
}