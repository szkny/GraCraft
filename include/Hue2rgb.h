#ifndef HUE2RGB_h_
#define HUE2RGB_h_

/***************** Hue to RGB Class ****************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Colors.h>

class hue2rgb{
	private:
		double r,g,b;
	public:
		/* h:0~hmax */
		hue2rgb(double h, double hmax);
		inline double R();
		inline double G();
		inline double B();
};

inline hue2rgb::hue2rgb(double h, double hmax){
	if(hmax<=0){
		printf("error : usage [class hue2rgb] hue2rgb(double x, double xmax[>0]).\n");
		exit(1);
	}
	r = 1.0;
	g = 1.0;
	b = 1.0;
	double hue = h/hmax*360.0;
	if(hue<0)        while(hue<0)   hue += 360;
	else if(360<hue) while(360<hue) hue -= 360;
	if(0<=hue&&hue<60){
		r = 1.0;
		g = hue/60.0;
		b = 0.0;
	}
	else if(60<=hue&&hue<120){
		r = (120-hue)/60;
		g = 1.0;
		b = 0.0;
	}
	else if(120<=hue&&hue<180){
		r = 0.0;
		g = 1.0;
		b = (hue-120)/60;
	}
	else if(180<=hue&&hue<240){
		r = 0.0;
		g = (240-hue)/60;
		b = 1.0;
	}
	else if(240<=hue&&hue<300){
		r = (hue-240)/60;
		g = 0.0;
		b = 1.0;
	}
	else if(300<=hue&&hue<=360){
		r = 1.0;
		g = 0.0;
		b = (360-hue)/60;
	}
}

inline double hue2rgb::R(){
	return r;
}
inline double hue2rgb::G(){
	return g;
}
inline double hue2rgb::B(){
	return b;
}


/*********************************************/

class ColorBar{
	private:
		bool flag; // On-Off
		int WX,WY;
		const int ColorBarArray;
		float *ColorBarWidth;
		float DefaultWidth;
	public:
		ColorBar();
		~ColorBar();
		void Resize(int wx, int wy);
		void On();
		void Off();
		bool Flag();
		void Draw();
		void Set(int x);
};

inline ColorBar::ColorBar():ColorBarArray(500){
	flag = false;
	DefaultWidth = 20.0;
	ColorBarWidth = new float[ColorBarArray];
	for(int i=0;i<ColorBarArray;++i)
		ColorBarWidth[i] = DefaultWidth;
}

inline ColorBar::~ColorBar(){
	delete[] ColorBarWidth;
}

inline void ColorBar::Resize(int wx, int wy){
	WX = wx;
	WY = wy;
}

inline void ColorBar::On(){
	flag = true;
}

inline void ColorBar::Off(){
	flag = false;
	for(int i=0;i<ColorBarArray;++i)
		ColorBarWidth[i] = DefaultWidth;
	printf("\n");
}

inline bool ColorBar::Flag(){
	return flag;
}

inline void ColorBar::Draw(){
	if(flag){
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

		double hbin = (double)WX/ColorBarArray;
		int i = 0;
		glBegin(GL_QUADS);
		for(double h=0.0;h<WX;h+=hbin){
			hue2rgb C(h,WX);
			glColor3d(C.R(),C.G(),C.B());
			glVertex2d(h     ,WY-15-ColorBarWidth[i]);
			glVertex2d(h+hbin,WY-15-ColorBarWidth[i]);
			glVertex2d(h+hbin,WY-15);
			glVertex2d(h     ,WY-15);
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
	}
}

inline void ColorBar::Set(int x){
	int ch = (int)((double)x/WX*ColorBarArray);
	static double s = 15.0/WX*ColorBarArray;
	while(ch<0) ch += ColorBarArray;
	while(ColorBarArray<=ch) ch -= ColorBarArray;
	for(int i=0;i<ColorBarArray;++i)
		ColorBarWidth[i] = DefaultWidth+5*exp(-(i-ch)*(i-ch)/(2*s*s));
}

/**************************************************/

#endif //"HUE2RGB_h_"
