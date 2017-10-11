/*
 *	cube object class
 */

#include<Object.h>


cube::cube():utilobj(){
	setdata();
}

cube::cube(double sz, Position p):utilobj(sz,p){
	setdata();
}

cube::cube(double sz, Position p, double ang):utilobj(sz,p,ang){
	setdata();
}

cube::cube(double sz, double x, double y, double z):utilobj(sz,x,y,z){
	setdata();
}

cube::cube(double sz, double x, double y, double z, double ang):utilobj(sz,x,y,z,ang){
	setdata();
}


void cube::setdata(){
	/* vertex asign */
	for(int i=0;i<8;++i){
		vertex[i][0] = pow(-1,(i+2)/2)*size/2.0;
		vertex[i][1] = pow(-1,(i+3)/2)*size/2.0;
		vertex[i][2] = pow(-1,(i+4)/4)*size/2.0;
	}
	/* edge asign */
	int etmp[][2] = {
		{  0, 1 },{  1, 2 },{  2, 3 },{  3, 0 },
		{  4, 5 },{  5, 6 },{  6, 7 },{  7, 4 },
		{  0, 4 },{  1, 5 },{  2, 6 },{  3, 7 }
	};
	for(int i=0;i<12;++i){
		edge[i][0] = etmp[i][0];
		edge[i][1] = etmp[i][1];
	}
	/* face asign */
	int ftmp[][4] = {
		{  0, 3, 2, 1 },
		{  0, 1, 5, 4 },
		{  1, 2, 6, 5 },
		{  2, 3, 7, 6 },
		{  0, 4, 7, 3 },
		{  4, 5, 6, 7 }
	};
	for(int i=0;i<6;++i){
		face[i][0] = ftmp[i][0];
		face[i][1] = ftmp[i][1];
		face[i][2] = ftmp[i][2];
		face[i][3] = ftmp[i][3];
	}
	/* normal vector asign (for shadow) */
	GLdouble ntmp[][3] = {
		{ 0.0, 0.0,-1.0 },
		{-1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0,-1.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
	};
	for(int i=0;i<6;++i){
		normal[i][0] = ntmp[i][0];
		normal[i][1] = ntmp[i][1];
		normal[i][2] = ntmp[i][2];
	}
}


void cube::show(){
	glBegin(GL_QUADS);
		for(int j=0;j<6;++j){
			glNormal3dv(normal[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face[j][i]]);
			}
		}
	glEnd();
}


