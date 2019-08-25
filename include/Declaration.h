#ifndef DECLARATION_h_
#define DECLARATION_h_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<Command.h>
#include<Object.h>
#include<AngleSetting.h>
#include<Background.h>

#include<vector>
using namespace std;

/* Function Prototype Declaration */
void Init(void);
void WindowCanvas(void);
void Controler(void);
void KeyboardMode(void);
void KeyboardMode_SP(void);
void PopUpMenu(void);
void Display(void);
void Timer(int value);
void Resize(int w, int h);
void MouseClick(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void ObjectsInit(void);
void ObjectsDraw(void);
void ObjectsResize(int WX, int WY);
void glLightInit();
void glLightSetting();

/* Declaration of class */
GRAPPA Grp;
Command Cmd;
ColorBar Clb;
AngleSetting Agl;
Background Bkg;
extern manager Mng;

#endif //DECLARATION_h_
