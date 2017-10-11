/*
*	Keyboard Shortcuts Configurations 
*/

#include<vector>

#include<GRAPPA.h>
#include<Command.h>
#include<Object.h>
#include<AngleSetting.h>

using namespace std;

extern vector<cube> cubes; //defined in Objects.cpp
extern vector<tube> tubes; //defined in Objects.cpp

extern GRAPPA Grp;
extern Command Cmd;
extern ColorBar Clb;
extern manager Mng; //defined in Objects.cpp
extern AngleSetting Agl;

void KeyboardMode(void);
void KeyboardMode_SP(void);
void InputKey(unsigned char key, int x, int y);
void CommandArrowKey(int key, int x, int y);
void AngleArrowKey(int key, int x, int y);

void KeyboardShortcut(unsigned char key, int x, int y){

	if(!Grp.GFLAG){ // Object Mode
		switch(key){
			case 'n': // new object
				Mng.NewObject();
				break;
			case 'u': // remove object
				Mng.Remove();
				break;
			case 'c': // change object color
				Mng.ColorMode();
				break;
			case 'm': // motion
				Mng.Motion();
				break;
			case 'r': // rotation
				Mng.Rotation();
				break;
			case 's': // stop
				Mng.Stop();
				break;
			case 'g': // GRAPPA
				Grp.SetGFLAG();
				break;
			case 'z': // zoom
				Agl.Zoom();
				break;
			case 'Z': // unzoom
				Agl.UnZoom();
				break;
			case ' ': // jump
				Agl.Jump();
				break;
			case ':': // command line
				Cmd.SetFlag();
				KeyboardMode();
				KeyboardMode_SP();
				break;
			case '_': // angle reset
				Agl.Reset();
				break;
			default:
				break;
		}
	}

	else{ // GRAPPA Mode
		switch(key){
			case 'u': /* Undo */
				Grp.Undo();
				break;
			case 'r': /* Reset */
				Grp.Reset();
				break;
			// case 'e': #<{(| Erase |)}>#
			// 	Grp.EraseLine();
			// 	break;
			// case 'p': #<{(| Pixel Mode |)}>#
			// 	Grp.PixelMode();
			// 	break;
			// case 's': // status
			// 	Grp.Status();
			// 	break;
			case 'g': // GRAPPA
				Grp.SetGFLAG();
				break;
			case ':': // command line
				Cmd.SetFlag();
				KeyboardMode();
				KeyboardMode_SP();
				break;
			default:
				break;
		}
	}
}


void KeyboardMode(){
	if(Cmd.GetFlag()) glutKeyboardFunc(InputKey);
	else glutKeyboardFunc(KeyboardShortcut);
}

void KeyboardMode_SP(){
	if(Cmd.GetFlag()) glutSpecialFunc(CommandArrowKey);
	else glutSpecialFunc(AngleArrowKey);
}

/* arrow key */
void CommandArrowKey(int key, int x, int y){
	if(key==GLUT_KEY_UP||key==GLUT_KEY_DOWN)
		Cmd.CommandHistory(key);
	if(key==GLUT_KEY_RIGHT||key==GLUT_KEY_LEFT)
		Cmd.CommandCursor(key);
}

void AngleArrowKey(int key, int x, int y){
	Agl.Move(key);
	// switch (key) {
	// 	case GLUT_KEY_UP:
	// 		// Agl.Zoom();
	// 		break;
	// 	case GLUT_KEY_DOWN:
	// 		// Agl.UnZoom();
	// 		break;
	// 	case GLUT_KEY_RIGHT:
	// 		// Mng.IncID();
	// 		break;
	// 	case GLUT_KEY_LEFT:
	// 		// Mng.DecID();
	// 		break;
	// 	default:
	// 		break;
	// }
}


