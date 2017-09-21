/*
 *	Angle Setting class
 */

#include<AngleSetting.h>

extern manager Mng;
extern vector<cube> cubes;
extern vector<tube> tubes;

AngleSetting::AngleSetting(){
	size    = 5.0;
	windowW = 500;
	windowH = 500;
	Rspeed  = 0.2;
	Tspeed  = 2.0;
	dstnc   = 80;
	theta   = 0.0;
	phi     = PI/12;
	p.x     = 0.0;
	p.y     = size;
	p.z     = 0.0;
	v.x     = 0.0;
	v.y     = 0.0;
	v.z     = 0.0;
}

AngleSetting::~AngleSetting(){
}

void AngleSetting::Init(){
	Ncube = cubes.size();
	Ntube = tubes.size();
	cubes.push_back(cube(size*2/3,p.x,p.y+size/3,p.z));
	tubes.push_back(tube(size/4,size,p.x,p.y-size/2,p.z));
	cubes[Ncube].colorMS(ms_ruby);
	tubes[Ntube].colorMS(ms_ruby);
	tubes[Ntube].roll(ZAXIS,90);
}

void AngleSetting::Reset(){
	dstnc = 80;
	theta = 0.0;
	phi   = PI/12;
}

void AngleSetting::Resize(int WX, int WY){
	windowW = WX;
	windowH = WY;
}

void AngleSetting::SetCamera(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// p.x = Mng.GetPos().x;
	// p.y = Mng.GetPos().y;
	// p.z = Mng.GetPos().z;
	double ex = p.x+dstnc*cos(phi)*sin(theta);
	double ey = p.y+dstnc*sin(phi);
	double ez = p.z+dstnc*cos(phi)*cos(theta);
	if(ey<1.) ey = 1.;
	gluLookAt(ex,ey,ez,p.x,p.y,p.z,0,1,0);
}

void AngleSetting::Rotate(double dx, double dy){
	theta += dx*PI/180*Rspeed;
	cubes[Ncube].roll(YAXIS,dx*Rspeed);
	if(theta>2*PI) theta -= 2*PI;
	if(theta<0)    theta += 2*PI;
	phi   += -dy*PI/180*Rspeed;
	if(phi> PI*3/7) phi = PI*3/7;
	if(phi<-PI*3/7) phi =-PI*3/7;
}

void AngleSetting::Zoom(){
	dstnc -= dstnc/20;
	if(dstnc<size) dstnc = size;
}

void AngleSetting::UnZoom(){
	dstnc += dstnc/20;
	if(800.<dstnc) dstnc = 800.;
}

void AngleSetting::Move(int key){
	switch(key){
		case GLUT_KEY_UP:
			p.x -= sin(theta)*Tspeed;
			p.z -= cos(theta)*Tspeed;
			break;
		case GLUT_KEY_DOWN:
			p.x += sin(theta)*Tspeed;
			p.z += cos(theta)*Tspeed;
			break;
		case GLUT_KEY_RIGHT:
			p.x += cos(-theta)*Tspeed;
			p.z += sin(-theta)*Tspeed;
			break;
		case GLUT_KEY_LEFT:
			p.x -= cos(-theta)*Tspeed;
			p.z -= sin(-theta)*Tspeed;
			break;
	}
}

void AngleSetting::Fall(){
	v.y -= 0.1;
	p.y += v.y;
	if(p.y<size){
		v.y = 0.0;
		p.y = size;
	}
}

void AngleSetting::Jump(){
	if(p.y==size){
		v.y = 2.0; 
		p.y += v.y;
	}
}

void AngleSetting::Player(){
	Fall();
	cubes[Ncube].locate(p.x,p.y+size/3,p.z);
	tubes[Ntube].locate(p.x,p.y-size/2,p.z);
}

void AngleSetting::Draw(bool GFLAG){
	glMaterialColor(ms_ruby);
	cubes[Ncube].draw();
	tubes[Ntube].draw();
	if(!GFLAG){
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowW, windowH, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	
		glColor3d(1,1,1);
		char s[64];
		sprintf(s,"dist : %5.1f",dstnc);
		glDrawString(s,windowW-110,40);
		sprintf(s,"theta: %+5.1f",theta*180/PI);
		glDrawString(s,windowW-110,55);
		sprintf(s,"phi  : %+5.1f",phi*180/PI);
		glDrawString(s,windowW-110,70);
	
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
	}
	SetCamera();
	Player();
}

Position AngleSetting::GetPos(){
	float dist = 15.0;
	Position tmp = {
		p.x-sin(theta)*dist,
		p.y,
		p.z-cos(theta)*dist
	};
	return tmp;
}

