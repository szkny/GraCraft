#ifndef ANGLESETTING_H_
#define ANGLESETTING_H_
/*****************************/

#include<stdio.h>
#include<math.h>

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Object.h>

class AngleSetting{
	private:
		double size;  // player size
		int    Ncube; // number of cube for player
		int    Ntube; // number of tube for player
		double windowW,windowH;
		double Rspeed; // Angle Rotate Speed
		double Tspeed; // Angle Translate Speed
		double dstnc;
	public:
		Position p;       // center of object
		Position v;       // velocity of object
		double theta,phi; // Camera Angle
		AngleSetting();
		~AngleSetting();
		void Init();
		void Resize(int WX, int WY);
		void SetCamera();
		void Reset();
		void Rotate(double dx, double dy);
		void Zoom();
		void UnZoom();
		void Move(int key);
		void Fall();
		void Jump();
		void Player();
		void Draw(bool GFLAG);
		Position GetPos();
};

/*****************************/
#endif //ANGLESETTING_H_
