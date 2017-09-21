#ifndef Object_h_
#define Object_h_
/*******************************/

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

#include<vector>
using namespace std;

#include<MyGLUT.h>
#include<Colors.h>
#include<Define.h>
#include<Hue2rgb.h>

#define NAXIS 0
#define XAXIS 1
#define YAXIS 2
#define ZAXIS 3

#define OBJCUBE 4
#define OBJTUBE 5

struct Position{
	double x;
	double y;
	double z;
};

class manager{
	private:
		int windowW,windowH;
		int ID;
		vector<int> mode;
		vector<Position> pos;
		int Ncube,Ntube;
	public:
		manager();
		~manager();
		void Resize(int wx, int wy);
		int  GetMode();
		void SetMode(int MODE);
		void NewObject(int MODE);
		void Remove();
		void Copy();
		void Copy(double x, double y, double z);
		void Move(double x, double y, double z);
		void Rotation();
		void Motion();
		void Stop();
		void Color();
		void Draw(bool GFLAG);
		Position GetPos();
		void IncID();
		void DecID();
};

class cube{
	private:
		int windowW,windowH;
		double size;
		MaterialStruct cube_color;
		GLdouble vertex[8][3];
		GLdouble normal[6][3];
		int edge[12][2];
		int face[6][4];
		Position pos;           // center of object
		double xt,yt,zt;        // center of object(temporary)
		double rx,ry,rz;        // rotation angle
		bool Mflag;             // motion flag
		double Mradius;         // motion radius
		double Mtheta,Mphi;     // motion angle 
		double Mtspeed,Mpspeed; // motion speed
		int Mdir;               // motion direction
		bool Rflag;             //rotaion flag
	public:
		cube(double size, double x, double y, double z);
		~cube();
		void resize(int WX, int WY);
		void draw();
		void locate(double x, double y, double z);
		void move(double dx, double dy, double dz);
		void roll(int AXIS, double dr);
		void colorCB(int x);
		void colorMS(MaterialStruct ms_color);
		void motion();
		void rotation();
		void stop();
		bool getMflag();
		bool getRflag();
		Position GetPos();
}; 


class tube{
	private:
		int windowW,windowH;
		double R,L;
		int N;
		MaterialStruct tube_color;
		GLdouble vertex[400][3];
		GLdouble normal[200][3];
		GLdouble normlid[2][3];
		int face[200][4];
		// GLdouble **vertex;
		// GLdouble **normal;
		// int **face;
		Position pos;           // center of object
		double xt,yt,zt;        // center of object(temporary)
		double rx,ry,rz;        // rotation angle
		bool Mflag;             // motion flag
		double Mradius;         // motion radius
		double Mtheta,Mphi;     // motion angle 
		double Mtspeed,Mpspeed; // motion speed
		int Mdir;               // motion direction
		bool Rflag;             //rotaion flag
	public:
		tube(double r, double l, double x, double y, double z);
		~tube();
		void resize(int WX, int WY);
		void draw();
		void locate(double x, double y, double z);
		void move(double dx, double dy, double dz);
		void roll(int AXIS, double dr);
		void colorCB(int x);
		void colorMS(MaterialStruct ms_color);
		void motion();
		void rotation();
		void stop();
		bool getMflag();
		bool getRflag();
		Position GetPos();
}; 

/*******************************/
#endif // Object_h_
