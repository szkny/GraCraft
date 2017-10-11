/*
 *	Object List
 */

#include<vector>
#include<GRAPPA.h>
#include<Object.h>
#include<Background.h>
#include<AngleSetting.h>

using namespace std;

manager Mng;
vector<cube> cubes;
vector<tube> tubes;
vector<pipe> pipes;
extern GRAPPA Grp;
extern Background Bkg;
extern AngleSetting Agl;

void ObjectsInit(void){
	cubes.reserve(100);
	tubes.reserve(100);
	pipes.reserve(100);
	// sea & island
	float Isize = 500.0;
	cubes.push_back(cube( Isize, 0.0,-Isize/2, 0.0)); //island
	cubes.push_back(cube(4000.0, 0.0, -2010.0, 0.0)); //sea
	cubes[0].colorMS(ms_Island);
	cubes[1].colorMS(ms_Sea);
	// pillars
	for(int i=0;i<4;++i){
		tubes.push_back(tube(5,2000,pow(-1,i)*(Isize/2-5),1000,pow(-1,i/2)*(Isize/2-5)));
		tubes[i].roll(ZAXIS,90);
		tubes[i].colorMS(ms_Island);
	}
	Agl.Init();
}

void ObjectsDraw(void){
	cubes[0].draw();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	cubes[1].draw();
	glDisable(GL_BLEND);
	for(int i=0;i<4;++i)
		tubes[i].draw();

	Mng.Draw(Grp.GetGFLAG());
}

void ObjectsResize(int WX, int WY){
	Mng.Resize(WX,WY);
	for(unsigned int i=0;i<cubes.size();++i)
		cubes[i].resize(WX,WY);
	for(unsigned int i=0;i<tubes.size();++i)
		tubes[i].resize(WX,WY);
}


/************* Light Setting ***************/

void glLightInit(void){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);
}

void glLightSetting(void){
	/* Light Color */
	static GLfloat LightClr0[]  = { 0.2, 0.2, 0.2, 1.0 };
	static GLfloat LightClr1[]  = { 0.7, 0.7, 0.7, 1.0 };
	static GLfloat LightClr2[]  = { 1.0, 1.0, 1.0, 1.0 };
	/* Light Position */
	static GLfloat LightPos0[]  = {    0.0, 5000.0,-1500.0, 1.0 };
	static GLfloat LightPos1[]  = { 5000.0, 5000.0, 3500.0, 1.0 };
	static GLfloat LightPos2[]  = { 5000.0, 5000.0,-6500.0, 1.0 };
	static GLfloat LightPos3[]  = {-5000.0, 5000.0, 3500.0, 1.0 };
	static GLfloat LightPos4[]  = {-5000.0, 5000.0,-6500.0, 1.0 };
	/* Ambient Light */
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LightClr0);
	/* Diffused Light */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  LightClr1);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPos1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE,  LightClr1);
	glLightfv(GL_LIGHT3, GL_POSITION, LightPos2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE,  LightClr1);
	glLightfv(GL_LIGHT4, GL_POSITION, LightPos3);
	glLightfv(GL_LIGHT4, GL_DIFFUSE,  LightClr1);
	glLightfv(GL_LIGHT7, GL_POSITION, LightPos4);
	glLightfv(GL_LIGHT7, GL_DIFFUSE,  LightClr1);
	/* Specular Light */
	glLightfv(GL_LIGHT5, GL_POSITION, LightPos1);
	glLightfv(GL_LIGHT5, GL_SPECULAR, LightClr2);
	glLightfv(GL_LIGHT6, GL_POSITION, LightPos4);
	glLightfv(GL_LIGHT6, GL_SPECULAR, LightClr2);
	/* Draw Sun */
	static float time = 0.0;
	time = Bkg.GetTime()*PI/100;
	static GLfloat emission[4];
	emission[0] = 1.0;
	emission[1] = 1.0;
	emission[2] = 0.5;
	emission[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glSphere(50, 0, 2000*sin(time), 2000*cos(time));
	emission[0] = 0.0;
	emission[1] = 0.0;
	emission[2] = 0.0;
	emission[3] = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
/*******************************************/

