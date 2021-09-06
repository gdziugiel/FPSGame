#include "stdafx.h"
CLufa::CLufa(void) : CSceneObject()
{
}
CLufa::~CLufa(void)
{
}
void CLufa::Initialize(void)
{
	radius = 1.0f;
}
void CLufa::Update(void)
{

}
void CLufa::Render(void)
{
	float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glPushMatrix();
	glTranslatef(Position.x, Position.y - 0.5f, Position.z);
	glRotatef(Rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(0.15f, 0.15f, 0.55f);
	glutSolidCube(radius);
	glPopMatrix();
}