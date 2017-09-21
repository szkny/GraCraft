/* main.cpp
*
*	main source for GraCraft  
*		(c) S.Suzuki 2017.9.1
*/

#include<Declaration.h>

/* main function */
int main(int argc, char *argv[]){
	srand((unsigned) time(NULL));
	glutInit(&argc, argv);
	WindowCanvas();
	PopUpMenu();
	Controler();
	glutMainLoop();
	return 0;
}

/******** Functions *********/

void Init(void){
	glClearColor(0.1,0.1,0.1,1.0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glLightInit();
	ObjectsInit();
}

void WindowCanvas(void){
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("GraCraft");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	Init();
}

void Controler(void){
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotion);
	KeyboardMode();
	KeyboardMode_SP();
}

void Display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Bkg.Draw();
	glLightSetting();

	ObjectsDraw();
	Agl.Draw(Grp.GetGFLAG());
	Clb.Draw();
	Grp.Draw();
	Cmd.Draw();
	
	glutIdleFunc(glutPostRedisplay);
	glutSwapBuffers();
}

void Resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w/(double)h, 1.0, 10000.0);
	Agl.SetCamera();
	Grp.Resize(w,h);
	Cmd.Resize(w,h);
	Clb.Resize(w,h);
	Agl.Resize(w,h);
	Bkg.Resize(w,h);
	ObjectsResize(w,h);
}


