/*
 *	cube object class
 */

#include<Object.h>

cube::cube(double sz, double x, double y, double z){
	windowW = 500; windowH = 500;
	/* size of cube */
	size = sz;
	/* default color */
	for(int i=0;i<4;++i){
		cube_color.diffuse[i]  = ms_white_plastic.diffuse[i];
		cube_color.ambient[i]  = ms_white_plastic.ambient[i];
		cube_color.specular[i] = ms_white_plastic.specular[i];
	}
	cube_color.shininess[0] = ms_white_plastic.shininess[0];
	/* default position */
	pos.x=x; pos.y=y; pos.z=z;
	/* default angle of rotation */
	rx=0;ry=0;rz=0;
	/* for motion */
	Mflag=false; Mradius=0.;
	Mtheta=0.; Mphi=0.;
	Mtspeed = 0.;
	Mpspeed = 0.;
	/* for rotation */
	Rflag = false;
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
	// printf("create cube.\n");
}

cube::~cube(){
	// printf("delete cube.\n");
}

void cube::resize(int WX, int WY){
	windowW = WX;
	windowH = WY;
}

void cube::draw(){
	if(Mflag){
		Mtheta += Mdir*PI/Mtspeed;
		Mphi   += Mdir*PI/Mpspeed;
		locate(xt+Mradius*cos(Mtheta)*sin(Mphi),
			   yt+Mradius*sin(Mtheta)*sin(Mphi),
			   zt+Mradius*cos(Mphi));
	}
	if(Rflag){
		roll(XAXIS,1.);
		roll(YAXIS,1.);
		roll(ZAXIS,1.);
	}
	glMaterialColor(cube_color);
	glPushMatrix();
	glTranslated(pos.x,pos.y,pos.z);
	glRotated(rx,1,0,0);
	glRotated(ry,0,1,0);
	glRotated(rz,0,0,1);
	// glScaled(1,1,2);
	glBegin(GL_QUADS);
		for(int j=0;j<6;++j){
			glNormal3dv(normal[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face[j][i]]);
			}
		}
	glEnd();
	glPopMatrix();
}

void cube::move(double dx, double dy, double dz){
	pos.x += dx;
	pos.y += dy;
	pos.z += dz;
	if(pos.y<size/2.) pos.y = size/2.;
}

void cube::locate(double x, double y, double z){
	pos.x = x;
	pos.y = y;
	pos.z = z;
	if(pos.y<size/2.) pos.y = size/2.;
}

void cube::roll(int AXIS, double dr){
	if(AXIS==XAXIS) rx += dr;
	if(AXIS==YAXIS) ry += dr;
	if(AXIS==ZAXIS) rz += dr;
}

void cube::colorCB(int x){
	hue2rgb C(x,windowW);
	cube_color.diffuse[0] = 0.50*C.R();
	cube_color.diffuse[1] = 0.50*C.G();
	cube_color.diffuse[2] = 0.50*C.B();
	cube_color.ambient[0] = 0.25*C.R();
	cube_color.ambient[1] = 0.25*C.G();
	cube_color.ambient[2] = 0.25*C.B();
	printf("\r\tR:%f\tG:%f\tB:%f",C.R(),C.G(),C.B());
	fflush(stdout);
}

void cube::colorMS(MaterialStruct ms_color){
	for(int i=0;i<4;++i){
		cube_color.diffuse[i]  = ms_color.diffuse[i];
		cube_color.ambient[i]  = ms_color.ambient[i];
		cube_color.specular[i] = ms_color.specular[i];
	} 
	cube_color.shininess[0] = ms_color.shininess[0];
}

void cube::motion(){
	Mflag = true;
	xt = pos.x;
	yt = pos.y;
	zt = pos.z;
	Mdir = randpm();
	Mtspeed = 20+80*randf();
	Mpspeed = 20+80*randf();
	Mradius = size/2.*(1+randf());
}

void cube::rotation(){
	if(Rflag) Rflag = false;
	else Rflag = true;
}

void cube::stop(){
	if(Mflag) Mflag = false;
	if(Rflag) Rflag = false;
}

bool cube::getMflag(){
	return Mflag;
}

bool cube::getRflag(){
	return Rflag;
}

Position cube::GetPos(){
	return pos;
}

