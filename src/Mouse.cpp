/*
*	Mouse Configurations 
*/

#include<vector>
#include<Object.h>
#include<GRAPPA.h>
#include<AngleSetting.h>

using namespace std;

bool MFLAG = false; //mouse flag
extern GRAPPA Grp;
extern ColorBar Clb;
extern manager Mng; //defined in Objects.cpp
extern AngleSetting Agl; //defined in Declaration.h
extern vector<cube> cubes; //defined in Objects.cpp
extern vector<tube> tubes; //defined in Objects.cpp
extern vector<pipe> pipes; //defined in Objects.cpp

/* mouse click */
void MouseClick(int button, int state, int x, int y){
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_DOWN){
				if(Grp.GetGFLAG()){
					Grp.NewFreeHand();
					Grp.SetCoordinate(x,y);
				}
				else if(Clb.Flag()){ // change color
					if(Mng.ColorCB(x)) Clb.Set(x);
				}
			}
			if(state==GLUT_UP){
				MFLAG = false;
				if(Grp.GetGFLAG()){
					Grp.SetDrawMode(MFREEHAND);
				}
				else if(Clb.Flag())
					Clb.Off();
			}
			break;
		default:
			break;
	}
}


/* mouse motion */
void MouseMotion(int x, int y){
	static int xmouse;
	static int ymouse;
	if(MFLAG){
		if(Grp.GetGFLAG()) // Grp GRAPPA Mode
			Grp.SetCoordinate(x,y);
		else{
			if(Clb.Flag()){ // Change Object Color
				if(Mng.ColorCB(x)) Clb.Set(x);
			}
			else
				Agl.Rotate(xmouse-x,ymouse-y);
		}
	}
	xmouse = x;
	ymouse = y;
	MFLAG  = true;
}


