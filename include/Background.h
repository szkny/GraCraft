#ifndef BACKGROUND_H_
#define BACKGROUND_H_
/****************************/

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Hue2rgb.h>

class Background{
	private:
		int WX,WY;
		int Array;
		float *skyR;
		float *skyG;
		float *skyB;
		float time;
		float tmax;
	public:
		Background();
		~Background();
		void Resize(int windowW, int windowH);
		void Draw();
		float GetTime();
};

/****************************/
#endif //BACKGROUND_H_
