#include "stdafx.h"

CScene::CScene(void)
{
}
CScene::~CScene(void)
{
	if (Skydome != NULL)
	{
		delete Skydome;
	}
	if (Terrain != NULL)
	{
		delete Terrain;
	}
	for (int i = 0; i < Objects->size(); i++)
		delete Objects->at(i);
	Objects->clear();
	for (int i = 0; i < Spheres->size(); i++)
		delete Spheres->at(i);
	Spheres->clear();
	for (int i = 0; i < Cubes->size(); i++)
		delete Cubes->at(i);
	Cubes->clear();
}
int CScene::random(int min, int max)
{
	int tmp;
	if (max >= min)
	{
		max -= min;
	}
	else
	{
		tmp = min - max;
		min = max;
		max = tmp;
	}
	return(max ? (rand() % max + min) : min);
}
void CScene::Initialize(void)
{
	_button1Texture = new CTexture("Resources\\nowagra.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_button1Texture->Load();
	_button2Texture = new CTexture("Resources\\kontynuuj.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_button2Texture->Load();
	_button3Texture = new CTexture("Resources\\kontynuujnieaktywny.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_button3Texture->Load();
	_button4Texture = new CTexture("Resources\\koniec.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_button4Texture->Load();
	_info1Texture = new CTexture("Resources\\przegralem.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_info1Texture->Load();
	_info2Texture = new CTexture("Resources\\wygrana.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_info2Texture->Load();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_FOG);
	float gl_fogcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, gl_fogcolor);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, 3.0f);
	player.pos.x = 0.0f;
	player.pos.y = 1.0f;
	player.pos.z = 4.0f;
	player.dir.x = 0.0f;
	player.dir.y = 0.9999999f;
	player.dir.z = -1.0f;
	player.speed = 0.4f;
	Skydome = new CSkydome();
	Skydome->Initialize();
	Terrain = new CTerrain();
	Terrain->Initialize();
	Lufa = new CLufa();
	Lufa->Initialize();
	Objects = new vector<CSceneObject *>();
	vec3 walls[][4] = {
	{ vec3(7.0f,  0.0f, -3.0f), vec3(7.0f,  1.0f, -3.0f), vec3(6.0f,  1.0f, -3.0f), vec3(6.0f,  0.0f, -3.0f) },
	{ vec3(6.0f,  0.0f, -3.0f), vec3(6.0f,  1.0f, -3.0f), vec3(5.0f,  1.0f, -3.0f), vec3(5.0f,  0.0f, -3.0f) },
	{ vec3(5.0f,  0.0f, -3.0f), vec3(5.0f,  1.0f, -3.0f), vec3(4.0f,  1.0f, -3.0f), vec3(4.0f,  0.0f, -3.0f) },
	{ vec3(4.0f,  0.0f, -3.0f), vec3(4.0f,  1.0f, -3.0f), vec3(3.0f,  1.0f, -3.0f), vec3(3.0f,  0.0f, -3.0f) },
	{ vec3(3.0f,  0.0f, -3.0f), vec3(3.0f,  1.0f, -3.0f), vec3(2.0f,  1.0f, -3.0f), vec3(2.0f,  0.0f, -3.0f) },
	{ vec3(2.0f,  0.0f, -3.0f), vec3(2.0f,  1.0f, -3.0f), vec3(1.0f,  1.0f, -3.0f), vec3(1.0f,  0.0f, -3.0f) },
	{ vec3(1.0f,  0.0f, -3.0f), vec3(1.0f,  1.0f, -3.0f), vec3(0.0f,  1.0f, -3.0f), vec3(0.0f,  0.0f, -3.0f) },
	{ vec3(0.0f,  0.0f, -3.0f), vec3(0.0f,  1.0f, -3.0f), vec3(-1.0f,  1.0f, -3.0f), vec3(-1.0f,  0.0f, -3.0f) },
	{ vec3(-1.0f,  0.0f, -3.0f), vec3(-1.0f,  1.0f, -3.0f), vec3(-2.0f,  1.0f, -3.0f), vec3(-2.0f,  0.0f, -3.0f) },
	{ vec3(-2.0f,  0.0f, -3.0f), vec3(-2.0f,  1.0f, -3.0f), vec3(-3.0f,  1.0f, -3.0f), vec3(-3.0f,  0.0f, -3.0f) },
	{ vec3(-3.0f,  0.0f, -3.0f), vec3(-3.0f,  1.0f, -3.0f), vec3(-4.0f,  1.0f, -3.0f), vec3(-4.0f,  0.0f, -3.0f) },
	{ vec3(-4.0f,  0.0f, -3.0f), vec3(-4.0f,  1.0f, -3.0f), vec3(-5.0f,  1.0f, -3.0f), vec3(-5.0f,  0.0f, -3.0f) },
	{ vec3(-5.0f,  0.0f, -3.0f), vec3(-5.0f,  1.0f, -3.0f), vec3(-6.0f,  1.0f, -3.0f), vec3(-6.0f,  0.0f, -3.0f) },
	{ vec3(-6.0f,  0.0f, -3.0f), vec3(-6.0f,  1.0f, -3.0f), vec3(-7.0f,  1.0f, -3.0f), vec3(-7.0f,  0.0f, -3.0f) },
	{ vec3(-7.0f,  0.0f, -3.0f), vec3(-7.0f,  1.0f, -3.0f), vec3(-7.0f,  1.0f, -1.0f), vec3(-7.0f,  0.0f, -1.0f) },
	{ vec3(-7.0f,  0.0f, -1.0f), vec3(-7.0f,  1.0f, -1.0f), vec3(-7.0f,  1.0f, 1.0f), vec3(-7.0f,  0.0f, 1.0f) },
	{ vec3(-7.0f,  0.0f, 1.0f), vec3(-7.0f,  1.0f, 1.0f), vec3(-7.0f,  1.0f, 3.0f), vec3(-7.0f,  0.0f, 3.0f) },
	{ vec3(-7.0f,  0.0f, 3.0f), vec3(-7.0f,  1.0f, 3.0f), vec3(-7.0f,  1.0f, 5.0f), vec3(-7.0f,  0.0f, 5.0f) },
	{ vec3(-7.0f,  0.0f, 5.0f), vec3(-7.0f,  1.0f, 5.0f), vec3(-7.0f,  1.0f, 7.0f), vec3(-7.0f,  0.0f, 7.0f) },
	{ vec3(-7.0f,  0.0f, 7.0f), vec3(-7.0f,  1.0f, 7.0f), vec3(-7.0f,  1.0f, 9.0f), vec3(-7.0f,  0.0f, 9.0f) },
	{ vec3(-7.0f,  0.0f, 9.0f), vec3(-7.0f,  1.0f, 9.0f), vec3(-7.0f,  1.0f, 11.0f), vec3(-7.0f,  0.0f, 11.0f) },
	{ vec3(-7.0f,  0.0f, 11.0f), vec3(-7.0f,  1.0f, 11.0f), vec3(-7.0f,  1.0f, 13.0f), vec3(-7.0f,  0.0f, 13.0f) },
	{ vec3(7.0f,  0.0f, -1.0f), vec3(7.0f,  1.0f, -1.0f), vec3(7.0f,  1.0f, -3.0f), vec3(7.0f,  0.0f, -3.0f) },
	{ vec3(7.0f,  0.0f, 1.0f), vec3(7.0f,  1.0f, 1.0f), vec3(7.0f,  1.0f, -1.0f), vec3(7.0f,  0.0f, -1.0f) },
	{ vec3(7.0f,  0.0f, 3.0f), vec3(7.0f,  1.0f, 3.0f), vec3(7.0f,  1.0f, 1.0f), vec3(7.0f,  0.0f, 1.0f) },
	{ vec3(7.0f,  0.0f, 5.0f), vec3(7.0f,  1.0f, 5.0f), vec3(7.0f,  1.0f, 3.0f), vec3(7.0f,  0.0f, 3.0f) },
	{ vec3(7.0f,  0.0f, 7.0f), vec3(7.0f,  1.0f, 7.0f), vec3(7.0f,  1.0f, 5.0f), vec3(7.0f,  0.0f, 5.0f) },
	{ vec3(7.0f,  0.0f, 9.0f), vec3(7.0f,  1.0f, 9.0f), vec3(7.0f,  1.0f, 7.0f), vec3(7.0f,  0.0f, 7.0f) },
	{ vec3(7.0f,  0.0f, 11.0f), vec3(7.0f,  1.0f, 11.0f), vec3(7.0f,  1.0f, 9.0f), vec3(7.0f,  0.0f, 9.0f) },
	{ vec3(7.0f,  0.0f, 13.0f), vec3(7.0f,  1.0f, 13.0f), vec3(7.0f,  1.0f, 11.0f), vec3(7.0f,  0.0f, 11.0f) },
	{ vec3(6.0f,  0.0f, 13.0f), vec3(6.0f,  1.0f, 13.0f), vec3(7.0f,  1.0f, 13.0f), vec3(7.0f,  0.0f, 13.0f) },
	{ vec3(5.0f,  0.0f, 13.0f), vec3(5.0f,  1.0f, 13.0f), vec3(6.0f,  1.0f, 13.0f), vec3(6.0f,  0.0f, 13.0f) },
	{ vec3(4.0f,  0.0f, 13.0f), vec3(4.0f,  1.0f, 13.0f), vec3(5.0f,  1.0f, 13.0f), vec3(5.0f,  0.0f, 13.0f) },
	{ vec3(3.0f,  0.0f, 13.0f), vec3(3.0f,  1.0f, 13.0f), vec3(4.0f,  1.0f, 13.0f), vec3(4.0f,  0.0f, 13.0f) },
	{ vec3(2.0f,  0.0f, 13.0f), vec3(2.0f,  1.0f, 13.0f), vec3(3.0f,  1.0f, 13.0f), vec3(3.0f,  0.0f, 13.0f) },
	{ vec3(1.0f,  0.0f, 13.0f), vec3(1.0f,  1.0f, 13.0f), vec3(2.0f,  1.0f, 13.0f), vec3(2.0f,  0.0f, 13.0f) },
	{ vec3(0.0f,  0.0f, 13.0f), vec3(0.0f,  1.0f, 13.0f), vec3(1.0f,  1.0f, 13.0f), vec3(1.0f,  0.0f, 13.0f) },
	{ vec3(-1.0f,  0.0f, 13.0f), vec3(-1.0f,  1.0f, 13.0f), vec3(0.0f,  1.0f, 13.0f), vec3(0.0f,  0.0f, 13.0f) },
	{ vec3(-2.0f,  0.0f, 13.0f), vec3(-2.0f,  1.0f, 13.0f), vec3(-1.0f,  1.0f, 13.0f), vec3(-1.0f,  0.0f, 13.0f) },
	{ vec3(-3.0f,  0.0f, 13.0f), vec3(-3.0f,  1.0f, 13.0f), vec3(-2.0f,  1.0f, 13.0f), vec3(-2.0f,  0.0f, 13.0f) },
	{ vec3(-4.0f,  0.0f, 13.0f), vec3(-4.0f,  1.0f, 13.0f), vec3(-3.0f,  1.0f, 13.0f), vec3(-3.0f,  0.0f, 13.0f) },
	{ vec3(-5.0f,  0.0f, 13.0f), vec3(-5.0f,  1.0f, 13.0f), vec3(-4.0f,  1.0f, 13.0f), vec3(-4.0f,  0.0f, 13.0f) },
	{ vec3(-6.0f,  0.0f, 13.0f), vec3(-6.0f,  1.0f, 13.0f), vec3(-5.0f,  1.0f, 13.0f), vec3(-5.0f,  0.0f, 13.0f) },
	{ vec3(-7.0f,  0.0f, 13.0f), vec3(-7.0f,  1.0f, 13.0f), vec3(-6.0f,  1.0f, 13.0f), vec3(-6.0f,  0.0f, 13.0f) }
	};
	for (int i = 0; i < 44; ++i)
	{
		CWall *w = new CWall(walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
		w->Initialize();
		Objects->push_back(w);
	}
	Spheres = new vector<CSceneObject *>();
	Cubes = new vector<CSceneObject *>();
	T = 0.0;
	N = 0;
	spawn = true;
	wygrana = false;
	przegrana = false;
	start = true;
	info = false;
	licznik = 0;
	globallicznik = 0;
	tlicz = 0;
}
void CScene::Update(void)
{
	srand(time(0));
	T = glutGet(GLUT_ELAPSED_TIME);
	if (info)
	{
		player.dir.y = 0.9999999f;
	}
	if (przegrana)
	{
		float gl_fogcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glEnable(GL_FOG);
		player.dir.y = 0.0f;
		wygrana = false;
		for (int i = 0; i < Cubes->size(); i++)
			delete Cubes->at(i);
		Cubes->clear();
	}
	else if (wygrana)
	{
		float gl_fogcolor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glEnable(GL_FOG);
		player.dir.y = 0.0f;
		for (int i = 0; i < Cubes->size(); i++)
			delete Cubes->at(i);
		Cubes->clear();
	}
	else
	{
		glDisable(GL_FOG);
	}
	if (spawn)
	{
		for (int i = 0; i < N; i++)
		{
			CCube *Cube = new CCube();
			Cube->Initialize();
			do
			{
				Cube->Position.x = random(-7, 7);
			} while (abs(player.pos.x - Cube->Position.x) < 1.5f);
			Cube->Position.y = 1.0f;
			do
			{
				Cube->Position.z = random(-3, 13);
			} while (abs(player.pos.z - Cube->Position.z) < 1.5f);
			Cubes->push_back(Cube);
		}
		spawn = false;
	}
	if (click)
	{
		CSphere *Sphere = new CSphere();
		Sphere->Initialize();
		Sphere->Position = Lufa->Position + player.dir;
		Sphere->Position.y -= 1.0f;
		Sphere->force = player.dir;
		Sphere->radiusChangePerUpdate = -0.005f;
		Spheres->push_back(Sphere);
		click = false;
	}
	if (captureMouse)
	{
		if (!start && !wygrana && !przegrana && !info)
		{
			player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
			player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
	if (keystate['w'])
	{
		player.velM = player.speed;
	}
	if (keystate['s'])
	{
		player.velM = -player.speed;
	}
	if (keystate['a'])
	{
		player.velS = -player.speed;
	}
	if (keystate['d'])
	{
		player.velS = player.speed;
	}
	if (keystate['q'])
	{
		player.velRY = -player.speed;
	}
	if (keystate['e'])
	{
		player.velRY = player.speed;
	}
	if (keystate['f'])
	{
		player.velRX = -player.speed;
	}
	if (keystate['c'])
	{
		player.velRX = player.speed;
	}
	float T = acos(player.dir.y);
	float G = atan2(player.dir.z, player.dir.x);
	T -= player.velRX * .03f;
	G += player.velRY * .03f;
	player.dir.x = sin(T) * cos(G);
	player.dir.y = cos(T);
	player.dir.z = sin(T) * sin(G);
	vec3 per;
	per.x = -player.dir.z;
	per.y = 0;
	per.z = player.dir.x;
	vec3 nextPlayerPos = player.pos;
	player.pos.x += player.dir.x * player.velM * .1f;
	if (free3DMovement)
	{
		player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
		player.pos.y -= .1f;
	}
	player.pos.z += player.dir.z * player.velM * .1f;
	player.pos.x += per.x * player.velS * .1f;
	if (free3DMovement)
	{
		player.pos.y += player.dir.y * player.velM * .1f;
	}
	player.pos.z += per.z * player.velS * .1f;
	player.pos.x = __max(-6.5f, player.pos.x);
	player.pos.x = __min(6.5f, player.pos.x);
	player.pos.y = __max(1.0f, player.pos.y);
	player.pos.z = __max(-2.5f, player.pos.z);
	player.pos.z = __min(12.5f, player.pos.z);
	player.dir.y = __max(0.1f, player.dir.y);
	player.velRX /= 1.2;
	player.velRY /= 1.2;
	player.velM /= 1.2;
	player.velS /= 1.2;
	for (int i = 0; i < Objects->size(); ++i)
	{
		Objects->at(i)->Update();
	}
	for (int i = 0; i < Spheres->size(); ++i)
	{
		Spheres->at(i)->Update();
		if (Spheres->at(i)->isAlive)
		{
			for (int j = 0; j < Cubes->size(); j++)
			{
				if (Cubes->at(j)->isAlive)
				{
					if (abs(Spheres->at(i)->Position.x - Cubes->at(j)->Position.x) < 0.5f && abs(Spheres->at(i)->Position.z - Cubes->at(j)->Position.z) < 0.5f && abs(Spheres->at(i)->Position.y - Cubes->at(j)->Position.y) < 0.5f)
					{
						Cubes->at(j)->isAlive = false;
						Spheres->at(i)->isAlive = false;
						break;
					}
				}
			}
		}
	}
	bool x = true;
	for (int i = 0; i < Cubes->size(); ++i)
	{
		if (Cubes->at(i)->isAlive)
		{
			x = true;
			break;
		}
		else
		{
			x = false;
		}
	}
	if (!x)
	{
		wygrana = true;
	}
	if (!przegrana)
	{
		tlicz = 0;
	}
	for (int i = 0; i < Cubes->size(); ++i)
	{
		Cubes->at(i)->force.x = -player.dir.x;
		Cubes->at(i)->force.z = -player.dir.z;
		Cubes->at(i)->Update();
		if (Cubes->at(i)->isAlive)
		{
			tlicz++;
			if (abs(player.pos.x - Cubes->at(i)->Position.x) < 0.5f && abs(player.pos.z - Cubes->at(i)->Position.z) < 0.5f && abs(player.pos.y - Cubes->at(i)->Position.y) < 0.5f)
			{
				przegrana = true;
			}
		}
	}
	licznik = N - tlicz + globallicznik;
	Skydome->Update();
	Terrain->Update();
	Lufa->Update();
	if (player.dir.z < 0)
	{
		Lufa->Rotation.y = -player.dir.x * 75;
		Lufa->Rotation.x = player.dir.y * 100;
	}
	else
	{
		Lufa->Rotation.y = player.dir.x * 75;
		Lufa->Rotation.x = -player.dir.y * 100;
	}
	Lufa->Rotation.z = 0.0f;
	Lufa->Position = player.pos + player.dir;
}
void CScene::Render(void)
{
	Menu();
	Info();
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z,
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
		0.0f, 1.0f, 0.0f
	);
	float l0_amb[] = { 0.2f, 0.2f, 0.2f };
	float l0_dif[] = { 0.6f, 0.6f, 0.6f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 0.0f, 5.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
	float l1_amb[] = { 0.8f, 0.0f, 0.0f, 1.0f };
	float l1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l1_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l1_pos[] = { player.pos.x, player.pos.y, player.pos.z, 1.0f };
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.5f);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	for (int i = 0; i < Objects->size(); ++i)
	{
		Objects->at(i)->Render();
	}
	for (int i = 0; i < Spheres->size(); ++i)
	{
		Spheres->at(i)->Render();
	}
	for (int i = 0; i < Cubes->size(); ++i)
	{
		Cubes->at(i)->Render();
	}
	Skydome->Position = player.pos;
	Skydome->Render();
	Terrain->Render();
	if (!start && !wygrana && !przegrana && !info)
	{
		Lufa->Render();
	}
}
void renderBitmapString(float x, float y, char* text)
{
	char *c;
	glRasterPos3f(x, y, 0);
	for (c = text; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}
void CScene::Menu()
{
	if (wygrana || przegrana || start)
	{
		if (!start)
		{
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glDisable(GL_LIGHTING);
			glDisable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_2D);
			if (przegrana)
			{
				glBindTexture(GL_TEXTURE_2D, _info1Texture->GetId());
			}
			else if (wygrana)
			{
				glBindTexture(GL_TEXTURE_2D, _info2Texture->GetId());
			}
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBegin(GL_QUADS);
			glColor3f(0, 0, 0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(70, 98);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(70, 85);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(30, 85);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(30, 98);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			char text[50];
			sprintf(text, "Punkty: %d", (int)licznik);
			if (wygrana)
			{
				glColor3f(1, 0, 0);
			}
			else
			{
				glColor3f(1, 1, 0);
			}
			renderBitmapString(47, 80, text);
			glEnable(GL_LIGHTING);
			glEnable(GL_CULL_FACE);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _button1Texture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(69, 77);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(69, 61);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(31, 61);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(31, 77);
		glColor3f(0, 0.3, 0);
		glVertex2f(70, 78);
		glVertex2f(70, 60);
		glVertex2f(30, 60);
		glVertex2f(30, 78);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		if (wygrana)
		{
			glBindTexture(GL_TEXTURE_2D, _button2Texture->GetId());
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, _button3Texture->GetId());
		}
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(69, 57);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(69, 41);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(31, 41);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(31, 57);
		glColor3f(0, 0.3, 0);
		glVertex2f(70, 58);
		glVertex2f(70, 40);
		glVertex2f(30, 40);
		glVertex2f(30, 58);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _button4Texture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(69, 37);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(69, 21);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(31, 21);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(31, 37);
		glColor3f(0, 0.3, 0);
		glVertex2f(70, 38);
		glVertex2f(70, 20);
		glVertex2f(30, 20);
		glVertex2f(30, 38);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	else
	{
		if (!info)
		{
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0, 100, 0, 100);
			glDisable(GL_LIGHTING);
			glDisable(GL_CULL_FACE);
			glColor3f(1, 1, 0);
			char text[50];
			sprintf(text, "Punkty: %d", (int)licznik);
			renderBitmapString(85, 95, text);
			glEnable(GL_LIGHTING);
			glEnable(GL_CULL_FACE);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
	}
}
void CScene::Info()
{
	if (info)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glColor3f(1, 1, 1);
		renderBitmapString(25, 90, "Opis gry:");
		renderBitmapString(25, 85, "Gra polega na zdobywaniu punktow poprzez zabijanie robotow.");
		renderBitmapString(25, 80, "Gra konczy sie w momencie zabicia gracza przez robota.");
		renderBitmapString(25, 70, "Sterowanie:");
		renderBitmapString(25, 65, "poruszanie sie - w, a, s, d");
		renderBitmapString(25, 60, "strzelanie - lewy przycisk myszy");
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex2f(80, 98);
		glVertex2f(80, 40);
		glVertex2f(20, 40);
		glVertex2f(20, 98);
		glEnd();
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 100, 0, 100);
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _button2Texture->GetId());
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(69, 37);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(69, 21);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(31, 21);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(31, 37);
		glColor3f(0, 0.3, 0);
		glVertex2f(70, 38);
		glVertex2f(70, 20);
		glVertex2f(30, 20);
		glVertex2f(30, 38);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
}