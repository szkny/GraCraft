/*
 *	utility object class
 */

#include<Object.h>


utilobj::utilobj(){
	init(10.,0.,0.,0.,0.);
}

utilobj::utilobj(double sz, double x, double y, double z){
	init(sz,x,y,z,0.);
}
utilobj::utilobj(double sz, double x, double y, double z, double ang){
	init(sz,x,y,z,ang);
}

utilobj::utilobj(double sz, Position p){
	init(sz,p.x,p.y,p.z,0.);
}

utilobj::utilobj(double sz, Position p, double ang){
	init(sz,p.x,p.y,p.z,ang);
}

void utilobj::init(double sz, double x, double y, double z, double ang){
	windowW = 500; windowH = 500;
	size = sz;
	colorMS(ms_white_plastic);
	pos.x=x; pos.y=y; pos.z=z;
	angle=ang*180/PI;
	rx=0;ry=0;rz=0;
	Mflag=false; Mradius=0.;
	Mtheta=0.; Mphi=0.;
	Mtspeed = 0.;
	Mpspeed = 0.;
	Rflag = false;
}

void utilobj::resize(int WX, int WY){
	windowW = WX;
	windowH = WY;
}

void utilobj::changeparameters(){
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
}

void utilobj::draw(){
	// if(Mflag){
	// 	Mtheta += Mdir*PI/Mtspeed;
	// 	Mphi   += Mdir*PI/Mpspeed;
	// 	locate(tmp.x+Mradius*cos(Mtheta)*sin(Mphi),
	// 		   tmp.y+Mradius*sin(Mtheta)*sin(Mphi),
	// 		   tmp.z+Mradius*cos(Mphi));
	// }
	// if(Rflag){
	// 	roll(XAXIS,1.);
	// 	roll(YAXIS,1.);
	// 	roll(ZAXIS,1.);
	// }
	glMaterialColor(color);
	glPushMatrix();
	glTranslated(pos.x,pos.y,pos.z);
	glRotated(rx,1,0,0);
	glRotated(ry,0,1,0);
	glRotated(rz,0,0,1);
	glRotated(angle,0,1,0);
	this->show();
	glPopMatrix();
}

void utilobj::move(double dx, double dy, double dz){
	pos.x += dx;
	pos.y += dy;
	pos.z += dz;
	if(pos.y<size/2.) pos.y = size/2.;
}

void utilobj::locate(Position p){
	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	if(pos.y<size/2.) pos.y = size/2.;
}

void utilobj::locate(double x, double y, double z){
	pos.x = x;
	pos.y = y;
	pos.z = z;
	if(pos.y<size/2.) pos.y = size/2.;
}

void utilobj::roll(int AXIS, double dr){
	if(AXIS==XAXIS) rx += dr;
	if(AXIS==YAXIS) ry += dr;
	if(AXIS==ZAXIS) rz += dr;
}

void utilobj::colorRGB(double R, double G, double B){
	color.diffuse[0] = 0.50*R;
	color.diffuse[1] = 0.50*G;
	color.diffuse[2] = 0.50*B;
	color.ambient[0] = 0.25*R;
	color.ambient[1] = 0.25*G;
	color.ambient[2] = 0.25*B;
}

void utilobj::colorCB(int x){
	hue2rgb C(x,windowW);
	color.diffuse[0] = 0.50*C.R();
	color.diffuse[1] = 0.50*C.G();
	color.diffuse[2] = 0.50*C.B();
	color.ambient[0] = 0.25*C.R();
	color.ambient[1] = 0.25*C.G();
	color.ambient[2] = 0.25*C.B();
	printf("\r\tR:%f\tG:%f\tB:%f",C.R(),C.G(),C.B());
	fflush(stdout);
}

void utilobj::colorMS(MaterialStruct ms_color){
	for(int i=0;i<4;++i){
		color.diffuse[i]  = ms_color.diffuse[i];
		color.ambient[i]  = ms_color.ambient[i];
		color.specular[i] = ms_color.specular[i];
	} 
	color.shininess[0] = ms_color.shininess[0];
}

void utilobj::motion(){
	Mflag = true;
	tmp.x = pos.x;
	tmp.y = pos.y;
	tmp.z = pos.z;
	Mdir = randpm();
	Mtspeed = 20+80*randf();
	Mpspeed = 20+80*randf();
	Mradius = size/2.*(1+randf());
}

void utilobj::rotation(){
	Rflag = true;
	rx = randf()*360;
	ry = randf()*360;
	rz = randf()*360;
}

void utilobj::stop(){
	Mflag = false;
	Rflag = false;
}


