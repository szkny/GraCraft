/*
*	PopupMenu Configurations
*/

#include<vector>

#include<GRAPPA.h>
#include<Command.h>
#include<Object.h>

using namespace std;

extern vector<cube> cubes; //defined in Objects.cpp
extern vector<tube> tubes; //defined in Objects.cpp
extern ColorBar Clb;
extern manager Mng; //defined in Objects.cpp

void Menu(int val);

void PopUpMenu(void){
	// Sub Menu
	int MenuID[2];
	MenuID[0] = glutCreateMenu(Menu);
    glutAddMenuEntry("Tube",7);
    glutAddMenuEntry("Cube",6);
    glutAddMenuEntry("Remove Current Object",2);
	MenuID[1] = glutCreateMenu(Menu);
    glutAddMenuEntry("Stop",5);
    glutAddMenuEntry("Rolling",4);
    glutAddMenuEntry("Moving",3);
	// Main Menu
	glutCreateMenu(Menu);
	glutAddSubMenu("New Object",MenuID[0]);
	glutAddSubMenu("Action",MenuID[1]);
    glutAddMenuEntry("Select Color",1);
	glutAddMenuEntry("Quit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
	switch(val){
		case 0: // Quit
			exit(0);
		case 1: // Select Color
			Mng.ColorMode();
			break;
		case 2: // Remove Object
			Mng.Remove();
			break;
		case 3: // Move Object
			Mng.Motion();
			break;
		case 4: // Rotate Object
			Mng.Rotation();
			break;
		case 5: // Stop Object
			Mng.Stop();
			break;
		case 6: // New Cube
			Mng.NewObject(OBJCUBE);
			break;
		case 7: // New Tube
			Mng.NewObject(OBJTUBE);
			break;
		default:
			break;
	}
}

