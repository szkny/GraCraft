/*
 *	tube object class
 */

#include<Object.h>

tube::tube():utilobj(){
	setdata(size/2,size);
}

tube::tube(double r, double l, Position p):utilobj(l,p){
	setdata(r,l);
}

tube::tube(double r, double l, Position p, double ang):utilobj(l,p,ang){
	setdata(r,l);
}

tube::tube(double r, double l, double x, double y, double z):utilobj(l,x,y,z){
	setdata(r,l);
}

tube::tube(double r, double l, double x, double y, double z, double ang):utilobj(l,x,y,z,ang){
	setdata(r,l);
}

#define DELETE(VAR,M){\
	for(int i=0;i<M;++i){\
		delete[] VAR[i];\
		VAR[i] = 0;\
	}\
	delete[] VAR;\
	VAR = 0;\
}
#define DELETE2(VAR,M){\
	delete[] VAR[0];\
	delete[] VAR;\
}
tube::~tube(){
	// DELETE2(vertex,2*N+1);
	// DELETE2(normal,N);
	// DELETE2(face,N+1);
}
#undef DELETE
#undef DELETE2

void tube::setdata(double R,double L){
	N=200;
	for(int j=0;j<N;++j){
		vertex[j  ][0] =-L/2.0;
		vertex[j  ][1] = R*cos((2.0*PI*(double)j)/(double)N);
		vertex[j  ][2] = R*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+N][0] = L/2.0;
		vertex[j+N][1] = vertex[j][1];
		vertex[j+N][2] = vertex[j][2];
	}
	for(int j=0;j<N-1;++j){
		face[j][0] = j    ;
		face[j][1] = j+N  ;
		face[j][2] = j+N+1;
		face[j][3] = j  +1;
	}
	face[N-1][0] =   N-1;
	face[N-1][1] = 2*N-1;
	face[N-1][2] =     N;
	face[N-1][3] =     0;
	for(int j=0;j<N;++j){
		normal[j][0] = 0.0;
		normal[j][1] = cos((2.0*PI*(double)j)/(double)N);
		normal[j][2] = sin((2.0*PI*(double)j)/(double)N);
	}
	normlid[0][0] =-1.0;
	normlid[0][1] = 0.0;
	normlid[0][2] = 0.0;
	normlid[1][0] = 1.0;
	normlid[1][1] = 0.0;
	normlid[1][2] = 0.0;
}

void tube::show(){
	glBegin(GL_QUADS);
	for(int j=0;j<N;++j){
		glNormal3dv(normal[j]);
		for(int i=0;i<4;++i){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
	/* Lid of Tube */
	glBegin(GL_TRIANGLE_FAN);
	glNormal3dv(normlid[0]);
	for(int j=0;j<N;++j)
		glVertex3d(vertex[j][0],vertex[j][1],vertex[j][2]);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glNormal3dv(normlid[1]);
	for(int j=N;j<2*N;++j)
		glVertex3d(vertex[j][0],vertex[j][2],vertex[j][1]);
	glEnd();
}

