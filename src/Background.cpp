/*
 *	Background (sky)
 */

#include<Background.h>

Background::Background(){
	WX = 500;
	WY = 500;
	Array = 100;
	skyR = new float[Array];
	skyG = new float[Array];
	skyB = new float[Array];
	float hue[3] = {.6,.7,1.};
	for(int i=0;i<Array;++i){
		skyR[i] = (float)((1-hue[0])*i+hue[0]*Array)/Array;
		skyG[i] = (float)((1-hue[1])*i+hue[1]*Array)/Array;
		skyB[i] = (float)((1-hue[2])*i+hue[2]*Array)/Array;
	}
	time = 0.0;
	tmax = 100;
}

Background::~Background(){
	delete[] skyR;
	delete[] skyG;
	delete[] skyB;
}

void Background::Resize(int windowW, int windowH){
	WX = windowW;
	WY = windowH;
}

#define GRD ((time/tmax-0.8)/0.2)
void Background::Draw(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WX, WY, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_QUADS);
	double hbin = (double)WY/Array;
	int i = 0;
	for(double h=0.0;h<WY;h+=hbin){
		if(tmax*0.8<time)
			glColor3d(GRD+(1-GRD)*skyR[i],skyG[i],(1-GRD)+GRD*skyB[i]);
		else
			glColor3d(skyR[i],skyG[i],skyB[i]);
		glVertex2d(0 ,h);
		glVertex2d(WX,h);
		glVertex2d(WX,h+hbin);
		glVertex2d(0 ,h+hbin);
		++i;
	}
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	time += 0.01;
	if(tmax<time) time = 0.0;
}
#undef GRD

float Background::GetTime(){
	return time;
}


