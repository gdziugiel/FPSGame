#include "stdafx.h"
int mouseX = 0;
int mouseY = 0;
bool captureMouse = true;
bool free3DMovement = false;
bool click = false;
float mouseSensitivity = .15f;
CScene * Scene;
bool keystate[256];
int main(int argc, char * argv[])
{
	PlaySound(L"Resources\\muzyka.wav", NULL, SND_ASYNC | SND_LOOP);
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Gra");
	glutFullScreen();
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);
	glutTimerFunc(17, OnTimer, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);
	Scene = new CScene();
	Scene->Initialize();
	glutMainLoop();
	return 0;
}
void OnKeyPress(unsigned char key, int x, int y)
{
	printf("KeyPress: %c\n", key);
	if (!keystate[key])
	{
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}
void OnKeyDown(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		glutLeaveMainLoop();
	}
	if (key == 'm' || key == 'M')
	{
		if (captureMouse)
		{
			captureMouse = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else {
			captureMouse = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}
	if (key == 'l' || key == 'L')
	{
		free3DMovement = !free3DMovement;
	}
	if (Scene->wygrana || Scene->przegrana || Scene->start)
	{
		if (key == '1')
		{
			Scene->start = false;
			Scene->wygrana = false;
			Scene->przegrana = false;
			Scene->N = 5;
			Scene->licznik = 0;
			Scene->globallicznik = 0;
			Scene->info = true;
		}
		if (key == '3')
		{
			glutLeaveMainLoop();
		}
	}
	if (Scene->wygrana)
	{
		if (key == '2')
		{
			Scene->globallicznik = Scene->licznik;
			Scene->start = false;
			Scene->wygrana = false;
			Scene->przegrana = false;
			Scene->N += 5;
			Scene->spawn = true;
		}
	}
}
void OnKeyUp(unsigned char key, int x, int y)
{
	printf("KeyUp: %c\n", key);
	keystate[key] = false;
}
void OnMouseMove(int x, int y)
{
	mouseX = x;
	mouseY = y;
}
void OnMouseClick(int button, int state, int x, int y)
{
	if (captureMouse)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (Scene->wygrana || Scene->przegrana || Scene->start)
			{
				if (mouseX > glutGet(GLUT_WINDOW_WIDTH) / 3 && mouseX < glutGet(GLUT_WINDOW_WIDTH) / 1.5 && mouseY > glutGet(GLUT_WINDOW_HEIGHT) / 4.5 && mouseY < glutGet(GLUT_WINDOW_HEIGHT) / 2.75)
				{
					Scene->start = false;
					Scene->wygrana = false;
					Scene->przegrana = false;
					Scene->N = 5;
					Scene->licznik = 0;
					Scene->globallicznik = 0;
					Scene->info = true;
				}
				if (mouseX > glutGet(GLUT_WINDOW_WIDTH) / 3 && mouseX < glutGet(GLUT_WINDOW_WIDTH) / 1.5 && mouseY > glutGet(GLUT_WINDOW_HEIGHT) / 1.6 && mouseY < glutGet(GLUT_WINDOW_HEIGHT) / 1.25)
				{
					glutLeaveMainLoop();
				}
				if (Scene->wygrana)
				{
					if (mouseX > glutGet(GLUT_WINDOW_WIDTH) / 3 && mouseX < glutGet(GLUT_WINDOW_WIDTH) / 1.5 && mouseY > glutGet(GLUT_WINDOW_HEIGHT) /2.3 && mouseY < glutGet(GLUT_WINDOW_HEIGHT) / 1.7)
					{
						Scene->globallicznik = Scene->licznik;
						Scene->start = false;
						Scene->wygrana = false;
						Scene->przegrana = false;
						Scene->N += 5;
						Scene->spawn = true;
					}
				}
			}
			else if (Scene->info)
			{
				if (mouseX > glutGet(GLUT_WINDOW_WIDTH) / 3 && mouseX < glutGet(GLUT_WINDOW_WIDTH) / 1.5 && mouseY > glutGet(GLUT_WINDOW_HEIGHT) / 1.6 && mouseY < glutGet(GLUT_WINDOW_HEIGHT) / 1.25)
				{
					Scene->info = false;
					Scene->spawn = true;
				}
			}
			else
			{
				click = true;
			}
		}
	}
}
void OnTimer(int id)
{
	glutTimerFunc(17, OnTimer, 0);
	Scene->Update();
}
void OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Scene->Render();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void OnReshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);
}
