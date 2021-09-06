#include "stdafx.h"
bool CCube::_isLoaded = false;
CTexture * CCube::_roboTexture = NULL;
CCube::CCube(void) : CSceneObject()
{
}
CCube::~CCube(void)
{
}
void CCube::Initialize(void)
{
	x = true;
	speed = 0.05f;
	strona = 1;
	rot = 0.0f;
	pos = 0.0f;
	
	_displayListId = glGenLists(1);
	glNewList(_displayListId, GL_COMPILE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();
	glEndList();
	if (_isLoaded)
	{
		return;
	}
	_isLoaded = true;
	_roboTexture = new CTexture("Resources\\tekstura.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_roboTexture->Load();
}
void CCube::Update(void)
{
	Position.x += force.x * speed;
	Position.y += force.y * speed;
	Position.z += force.z * speed;
	Position.x = __max(-6.5f, Position.x);
	Position.x = __min(6.5f, Position.x);
	Position.z = __max(-2.5f, Position.z);
	Position.z = __min(12.5f, Position.z);
	if (!isAlive)
	{
		if (Rotation.z < 90)
		{
			Rotation.z += 1.0f;
		}
		if (Position.y > -1)
		{
			Position.y -= 0.025f;
		}
		if (Position.y <= -1)
		{
			x = false;
		}
	}
	Rotation.y += 0.5f;
	if (strona)
	{
		rot -= 1.0f;
		pos -= 0.01f;
		if (rot < -35)
		{
			strona = 0;
		}
	}
	else
	{
		rot += 1.0f;
		pos += 0.01f;
		if (rot > 35)
		{
			strona = 1;
		}
	}
}
void CCube::Render(void)
{
	float m_amb[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	if (x)
	{
		glPushMatrix();
		glTranslatef(Position.x, Position.y, Position.z);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Position.x + pos, Position.y - 0.85f, Position.z + 0.25f);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(rot, 0.0f, 0.0f, 1.0f);
		glScalef(0.25f, 1.0f, 0.25f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Position.x - pos, Position.y - 0.85f, Position.z - 0.25f);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(-rot, 0.0f, 0.0f, 1.0f);
		glScalef(0.25f, 1.0f, 0.25f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Position.x, Position.y + 0.55f, Position.z);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glScalef(0.15f, 0.15f, 0.15f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Position.x, Position.y + 0.75f, Position.z);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(Rotation.y, 0.0f, 1.0f, 0.0f);
		glScalef(0.25f, 0.25f, 0.25f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Position.x, Position.y, Position.z + 0.6f);
		glRotatef(force.x, 1.0f, 0.0f, 0.0f);
		glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.25f, 1.0f, 0.25f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(Position.x, Position.y, Position.z - 0.6f);
		glRotatef(Rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.25f, 1.0f, 0.25f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _roboTexture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glCallList(_displayListId);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}