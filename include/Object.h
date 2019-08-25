#ifndef Object_h_
#define Object_h_
/*******************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#ifdef __APPLE__
#include<GLUT/glut.h>
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
#define OBJPIPE 6

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
		int Ncube,Ntube,Npipe;
		MaterialStruct obj_color;
		bool MoveFlag;
	public:
		manager();
		~manager();
		void Resize(int wx, int wy);
		int  GetMode();
		void SetMode(int MODE);
		void NewObject();
		void NewObject(int MODE);
		void Reset();
		void Remove();
		void Copy();
		void Copy(int N);
		void Copy(double x, double y, double z);
		void Move();
		void Move(double x, double y, double z);
		void Rotation();
		void Motion();
		void Stop();
		void ColorMode();
		bool ColorCB(int x);
		void ColorRGB(double R, double G, double B);
		void StoreColor(MaterialStruct ms_color);
		void ChangeParameters();
		void Draw(bool GFLAG);
		void IncID();
		void DecID();
		Position GetPos();
		void UnsetFlags();
};

class utilobj{
	protected:
		int windowW,windowH;    // window size
		double size;            // object size
		Position tmp;           // center of object(temporary)
		double angle;           // angle of object
		double rx,ry,rz;        // rotation angle
		double Mradius;         // motion radius
		double Mtheta,Mphi;     // motion angle 
		double Mtspeed,Mpspeed; // motion speed
		int Mdir;               // motion direction
	public:
		MaterialStruct color;   // object color
		Position pos;           // object position
		bool Mflag;             // motion flag
		bool Rflag;             // rotaion flag
		utilobj();
		utilobj(double size, Position p);
		utilobj(double size, Position p, double ang);
		utilobj(double size, double x, double y, double z);
		utilobj(double size, double x, double y, double z, double ang);
		~utilobj(){};
		void init(double sz, double x, double y, double z, double ang);
		void changeparameters();
		void draw();
		void resize(int WX, int WY);
		void locate(Position p);
		void locate(double x, double y, double z);
		void move(double dx, double dy, double dz);
		void roll(int AXIS, double dr);
		void colorRGB(double R, double G, double B);
		void colorCB(int x);
		void colorMS(MaterialStruct ms_color);
		void motion();
		void rotation();
		void stop();
		virtual void show(){};
}; 

class cube : public utilobj{
	private:
		GLdouble vertex[8][3];
		GLdouble normal[6][3];
		int edge[12][2];
		int face[6][4];
	public:
		cube();
		cube(double size, Position p);
		cube(double size, Position p, double angle);
		cube(double size, double x, double y, double z);
		cube(double size, double x, double y, double z, double angle);
		~cube(){};
		void setdata();
		void show();
}; 


class tube : public utilobj{
	private:
		int N;
		GLdouble vertex[400][3];
		GLdouble normal[200][3];
		int face[200][4];
		// GLdouble **vertex;
		// GLdouble **normal;
		// int      **face;
		GLdouble normlid[2][3];
	public:
		tube();
		tube(double r, double l, Position p);
		tube(double r, double l, Position p, double ang);
		tube(double r, double l, double x, double y, double z);
		tube(double r, double l, double x, double y, double z, double ang);
		~tube();
		void setdata(double R, double L);
		void show();
}; 


class pipe : public utilobj{
	private:
		int N;
		GLdouble vertex[800][3];
		GLdouble normal1[200][3];
		GLdouble normal2[200][3];
		int face1[200][4];
		int face2[200][4];
		int face3[200][4];
		int face4[200][4];
		GLdouble normlid[2][3];
		// GLdouble **vertex;
		// GLdouble **normal;
		// int **face;
	public:
		pipe();
		pipe(double r, double d, double l, Position p);
		pipe(double r, double d, double l, Position p, double ang);
		pipe(double r, double d, double l, double x, double y, double z);
		pipe(double r, double d, double l, double x, double y, double z, double ang);
		~pipe();
		void setdata(double r, double d, double l);
		void show();
}; 

/*******************************/
#endif // Object_h_
