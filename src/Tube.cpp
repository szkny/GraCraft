/*
 *	tube object class
 */

#include<Object.h>

tube::tube(){
	windowW = 500; windowH = 500;
	/* size of tube */
	R=5; L=10;
	/* default color */
	colorMS(ms_white_plastic);
	/* default position */
	pos.x=0; pos.y=0; pos.z=0;
	/* default angle */
	angle=0.0;
	rx=0;ry=0;rz=0;
	/* for motion */
	Mflag=false; Mradius=0.;
	Mtheta=0.; Mphi=0.;
	Mtspeed = 0.;
	Mpspeed = 0.;
	/* for rotation */
	Rflag = false;
	N = 200;
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

tube::tube(double r, double l, double x, double y, double z){
	windowW = 500; windowH = 500;
	/* size of tube */
	R=r; L=l;
	/* default color */
	colorMS(ms_white_plastic);
	/* default position */
	pos.x=x; pos.y=y; pos.z=z;
	/* default angle */
	angle=0.0;
	rx=0;ry=0;rz=0;
	/* for motion */
	Mflag=false; Mradius=0.;
	Mtheta=0.; Mphi=0.;
	Mtspeed = 0.;
	Mpspeed = 0.;
	/* for rotation */
	Rflag = false;
	N = 200;
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

tube::tube(double r, double l, double x, double y, double z, double ang){
	windowW = 500; windowH = 500;
	/* size of tube */
	R=r; L=l;
	/* default color */
	colorMS(ms_white_plastic);
	/* default position */
	pos.x=x; pos.y=y; pos.z=z;
	/* default angle */
	angle=ang*180/PI;
	rx=0;ry=0;rz=0;
	/* for motion */
	Mflag=false; Mradius=0.;
	Mtheta=0.; Mphi=0.;
	Mtspeed = 0.;
	Mpspeed = 0.;
	/* for rotation */
	Rflag = false;
	N = 200;
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

#define DELETE(VAR,M){\
	for(int i=0;i<M;++i){\
		delete[] VAR[i];\
		VAR[i] = 0;\
	}\
	delete[] VAR;\
	VAR = 0;\
}
tube::~tube(){
	// DELETE(vertex,2*N+1);
	// DELETE(normal,N);
	// DELETE(face,N+1);
}
#undef DELETE

void tube::resize(int WX, int WY){
	windowW = WX;
	windowH = WY;
}

void tube::draw(){
	if(Mflag){
		Mtheta += Mdir*PI/Mtspeed;
		Mphi   += Mdir*PI/Mpspeed;
		locate(tmp.x+Mradius*cos(Mtheta)*sin(Mphi),
			   tmp.y+Mradius*sin(Mtheta)*sin(Mphi),
			   tmp.z+Mradius*cos(Mphi));
	}
	if(Rflag){
		roll(XAXIS,1.);
		roll(YAXIS,1.);
		roll(ZAXIS,1.);
	}
	glMaterialColor(tube_color);
	glPushMatrix();
	glTranslated(pos.x,pos.y,pos.z);
	glRotated(rx,1,0,0);
	glRotated(ry,0,1,0);
	glRotated(rz,0,0,1);
	glRotated(angle,0,1,0);
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
	glPopMatrix();
}

void tube::move(double dx, double dy, double dz){
	pos.x += dx;
	pos.y += dy;
	pos.z += dz;
	if(pos.y<R) pos.y = R;
}

void tube::locate(double x, double y, double z){
	pos.x = x;
	pos.y = y;
	pos.z = z;
	if(pos.y<R) pos.y = R;
}

void tube::roll(int AXIS, double dr){
	if(AXIS==XAXIS) rx += dr;
	if(AXIS==YAXIS) ry += dr;
	if(AXIS==ZAXIS) rz += dr;
}

void tube::colorCB(int x){
	hue2rgb C(x,windowW);
	tube_color.diffuse[0] = 0.50*C.R();
	tube_color.diffuse[1] = 0.50*C.G();
	tube_color.diffuse[2] = 0.50*C.B();
	tube_color.ambient[0] = 0.25*C.R();
	tube_color.ambient[1] = 0.25*C.G();
	tube_color.ambient[2] = 0.25*C.B();
	printf("\r\tR:%f\tG:%f\tB:%f",C.R(),C.G(),C.B());
	fflush(stdout);
}

void tube::colorMS(MaterialStruct ms_color){
	for(int i=0;i<4;++i){
		tube_color.diffuse[i]  = ms_color.diffuse[i];
		tube_color.ambient[i]  = ms_color.ambient[i];
		tube_color.specular[i] = ms_color.specular[i];
	} 
	tube_color.shininess[0] = ms_color.shininess[0];
}

void tube::motion(){
	Mflag = true;
	tmp.x = pos.x;
	tmp.y = pos.y;
	tmp.z = pos.z;
	Mdir = randpm();
	Mtspeed = 20+80*randf();
	Mpspeed = 20+80*randf();
	Mradius = R*(1+randf());
}

void tube::rotation(){
	if(Rflag) Rflag = false;
	else Rflag = true;
}

void tube::stop(){
	if(Mflag) Mflag = false;
	if(Rflag) Rflag = false;
}

bool tube::getMflag(){
	return Mflag;
}

bool tube::getRflag(){
	return Rflag;
}

Position tube::GetPos(){
	return pos;
}

MaterialStruct tube::GetColor(){
	return tube_color;
}

