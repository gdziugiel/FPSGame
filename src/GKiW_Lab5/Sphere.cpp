#include "stdafx.h"
CSphere::CSphere(void) : CSceneObject()
{
}
CSphere::~CSphere(void)
{
}
void CSphere::Initialize(void)
{
	weight = 2;
	radius = 0.5;
	radiusChangePerUpdate = 0;
}
void CSphere::Update(void)
{
	Position.x += force.x / weight;
	Position.y += force.y / weight;
	Position.z += force.z / weight;
	radius += radiusChangePerUpdate;
	if (radius <= 0)
	{
		isAlive = false;
	}
}
void CSphere::Render(void)
{
	float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	if (isAlive)
	{
		glutSolidSphere(radius, 24, 24);
	}
	
	glPopMatrix();
}
