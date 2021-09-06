#define PI 3.14159265
#include "targetver.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
#include <time.h>
using namespace std;
#include "Bitmap.h"
#include "Texture.h"
#include "Vec3.h"
#include "Player.h"
#include "SceneObject.h"
#include "Skydome.h"
#include "Terrain.h"
#include "Wall.h"
#include "Sphere.h"
#include "Cube.h"
#include "Lufa.h"
#include "Scene.h"
#include "Gra.h"
extern double T;
extern int mouseX;
extern int mouseY;
extern bool captureMouse;
extern bool free3DMovement;
extern float mouseSensitivity;
extern CScene * Scene;
extern bool keystate[256];
extern bool click;