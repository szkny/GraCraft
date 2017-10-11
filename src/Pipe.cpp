#include<Object.h>


pipe::pipe():utilobj(){
	setdata(size/2,size/4,size);
}

pipe::pipe(double r, double d, double l, Position p):utilobj(l,p){
	setdata(r,d,l);
}

pipe::pipe(double r, double d, double l, Position p, double ang):utilobj(l,p,ang){
	setdata(r,d,l);
}

pipe::pipe(double r, double d, double l, double x, double y, double z):utilobj(l,x,y,z){
	setdata(r,d,l);
}

pipe::pipe(double r, double d, double l, double x, double y, double z, double ang):utilobj(l,x,y,z,ang){
	setdata(r,d,l);
}

pipe::~pipe(){
}


void pipe::setdata(double r, double d, double l){
	N = 200;
	for(int j=0;j<N;++j){
		vertex[j    ][0] =-l/2.0;
		vertex[j    ][1] = r*cos((2.0*PI*(double)j)/(double)N);
		vertex[j    ][2] = r*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+  N][0] = l/2.0;
		vertex[j+  N][1] = vertex[j][1];
		vertex[j+  N][2] = vertex[j][2];
		vertex[j+2*N][0] =-l/2.0;
		vertex[j+2*N][1] = (r-d)*cos((2.0*PI*(double)j)/(double)N);
		vertex[j+2*N][2] = (r-d)*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+3*N][0] = l/2.0;
		vertex[j+3*N][1] = vertex[j+2*N][1];
		vertex[j+3*N][2] = vertex[j+2*N][2];
	}
	for(int j=0;j<N-1;++j){
		face1[j][0] = j    ;
		face1[j][1] = j+N  ;
		face1[j][2] = j+N+1;
		face1[j][3] = j  +1;
	}
	face1[N-1][0] =   N-1;
	face1[N-1][1] = 2*N-1;
	face1[N-1][2] =   N+1;
	face1[N-1][3] =     1;
	for(int j=0;j<N-1;++j){
		face2[j][0] = j+2*N;
		face2[j][1] = j+2*N+1;
		face2[j][2] = j+3*N+1;
		face2[j][3] = j+3*N;
	}
	face2[N-1][0] = 3*N-1;
	face2[N-1][1] = 2*N+1;
	face2[N-1][2] = 3*N+1;
	face2[N-1][3] = 4*N-1;
	for(int j=0;j<N-1;++j){
		face3[j][0] = j;
		face3[j][1] = j+1;
		face3[j][2] = j+2*N+1;
		face3[j][3] = j+2*N;
	}
	face3[N-1][0] =   N-1;
	face3[N-1][1] =     0;
	face3[N-1][2] =   2*N;
	face3[N-1][3] = 3*N-1;
	for(int j=0;j<N-1;++j){
		face4[j][0] = j+N;
		face4[j][1] = j+3*N;
		face4[j][2] = j+3*N+1;
		face4[j][3] = j+N+1;
	}
	face4[N-1][0] = 2*N-1;
	face4[N-1][1] = 4*N-1;
	face4[N-1][2] =   3*N;
	face4[N-1][3] =     N;
	for(int j=0;j<N;++j){
		normal1[j][0] = 0.0;
		normal1[j][1] = cos((2.0*PI*(double)j)/(double)N);
		normal1[j][2] = sin((2.0*PI*(double)j)/(double)N);
	}
	for(int j=0;j<N;++j){
		normal2[j][0] =-0.0;
		normal2[j][1] =-cos((2.0*PI*(double)j)/(double)N);
		normal2[j][2] =-sin((2.0*PI*(double)j)/(double)N);
	}
}


void pipe::show(){
	glBegin(GL_QUADS);
	for(int j=0;j<N;++j){
		glNormal3dv(normal1[j]);
		for(int i=0;i<4;++i){
			glVertex3dv(vertex[face1[j][i]]);
		}
		glNormal3dv(normal2[j]);
		for(int i=0;i<4;++i){
			glVertex3dv(vertex[face2[j][i]]);
		}
		glNormal3d(-1,0,0);
		for(int i=0;i<4;++i){
			glVertex3dv(vertex[face3[j][i]]);
		}
		glNormal3d( 1,0,0);
		for(int i=0;i<4;++i){
			glVertex3dv(vertex[face4[j][i]]);
		}
	}
	glEnd();
}

