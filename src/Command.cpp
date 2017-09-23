/*
 *	Commands Configurations 
 */

#include<vector>

#include<GRAPPA.h>
#include<Command.h>
#include<Object.h>

using namespace std;

extern vector<cube> cubes; //defined in Objects.cpp
extern vector<tube> tubes; //defined in Objects.cpp
extern bool MFLAG; //defined in Mouse.cpp
extern GRAPPA Grp;
extern Command Cmd;
extern ColorBar Clb;
extern manager Mng; //defined in Objects.cpp

void MouseDrawMode(void);
void KeyboardMode(void);
void KeyboardMode_SP(void);


void Commands(){
	double Arg1,Arg2,Arg3;

	if(Cmd.RunCommand("q","quit","exit"))
		exit(0);

	else if(Cmd.RunCommand("h","help"))
			Cmd.Help();

	else if(Cmd.RunCommand("g","grappa"))
		Grp.SetGFLAG();

	if(!Grp.GetGFLAG()){ // case of GRAPPA flag 'off' == 'Object Mode'

		if(Cmd.RunCommand("cube"))
			Mng.NewObject(OBJCUBE);

		else if(Cmd.RunCommand("tube"))
			Mng.NewObject(OBJTUBE);

		else if(Cmd.RunCommand("co","color"))
			Mng.Color();

		else if(Cmd.RunCommand("rm"))
			Mng.Remove();

		else if(Cmd.RunCommand("cp"))
			Mng.Copy();

		else if(Cmd.RunCommand("cp",&Arg1,&Arg2,&Arg3))
			Mng.Copy(Arg1,Arg2,Arg3);

		else if(Cmd.RunCommand("mv",&Arg1,&Arg2,&Arg3))
			Mng.Move(Arg1,Arg2,Arg3);

		else if(Cmd.RunCommand("ro","rotation"))
			Mng.Rotation();

		else if(Cmd.RunCommand("mo","motion"))
			Mng.Motion();

		else if(Cmd.RunCommand("st","stop"))
			Mng.Stop();
	}

	else{ // case of GRAPPA flag 'on'

		if(Cmd.RunCommand("undo"))
			Grp.Undo();

		else if(Cmd.RunCommand("redo"))
			Grp.Redo();

		else if(Cmd.RunCommand("status"))
			Grp.Status();

		else if(Cmd.RunCommand("reset"))
			Grp.Reset();

		else if(Cmd.RunCommand("mv"))
			Grp.SetDrawMode(MLINEMOVE);

		else if(Cmd.RunCommand("cp"))
			Grp.SetDrawMode(MLINECOPY);

		// else if(Cmd.RunCommand("rotate"))
		// 	Grp.SetDrawMode(MLINEROTATE);

		else if(Cmd.RunCommand("co"))
			Grp.SetDrawMode(MCOLORBARLINE);

		else if(Cmd.RunCommand("co",&Arg1,&Arg2,&Arg3))
			Grp.SetLineColor(Arg1,Arg2,Arg3);

		// else if(Cmd.RunCommand("cco"))
		// 	Grp.SetDrawMode(MCOLORBARCANVAS);
		//
		// else if(Cmd.RunCommand("cco",&Arg1,&Arg2,&Arg3))
		// 	Grp.SetCanvasColor(Arg1,Arg2,Arg3);
        //
		// else if(Cmd.RunCommand("dco",&Arg1,&Arg2,&Arg3))
		// 	Grp.SetDefaultLineColor(Arg1,Arg2,Arg3);

		else if(Cmd.RunCommand("cor"))
			Grp.SetLineColor(1.0,0.0,0.0);

		else if(Cmd.RunCommand("cog"))
			Grp.SetLineColor(0.0,1.0,0.0);

		else if(Cmd.RunCommand("cob"))
			Grp.SetLineColor(0.0,0.0,1.0);

		else if(Cmd.RunCommand("coy"))
			Grp.SetLineColor(1.0,1.0,0.0);

		else if(Cmd.RunCommand("lw","width",&Arg1))
			Grp.SetLineWidth(Arg1);

		else if(Cmd.RunCommand("dlw","defaultwidth",&Arg1))
			Grp.SetDefaultLineWidth(Arg1);

		// else if(Cmd.RunCommand("p","pixel"))
		// 	Grp.PixelMode();
		//
		// else if(Cmd.RunCommand("ps","pixelsize",&Arg1))
		// 	Grp.SetPixelSize(Arg1);
		//
		// else if(Cmd.RunCommand("eraser"))
		// 	Grp.PixelEraser();
		//
		else if(Cmd.RunCommand("circle"))
			Grp.SetDrawMode(MCIRCLE);

		else if(Cmd.RunCommand("square"))
			Grp.SetDrawMode(MSQUARE);

		else if(Cmd.RunCommand("polygon",&Arg1))
			Grp.SetDrawMode(MPOLYGON,Arg1);

		else if(Cmd.RunCommand("line"))
			Grp.SetDrawMode(MSTRAIGHTLINE);

		else if(Cmd.RunCommand("rand"))
			Grp.SetDrawMode(MRANDOM);

		else if(Cmd.RunCommand("kaleido"))
			Grp.SetDrawMode(MKALEIDO);
	}

}


void InputKey(unsigned char key, int x, int y){
	// printf("key = %d\n",key);
	if(key == 127){ //delete key
		int size = Cmd.CommandStore(key);
		if(size == 0){
			KeyboardMode();
			KeyboardMode_SP();
		}
	}
	else if(key == 13){ //return key
		Commands();
		Cmd.CommandStore(key);
		KeyboardMode();
		KeyboardMode_SP();
	}
	else if(key == 9){ //tab key
		Cmd.CommandStore(32);
	}
	else{
		Cmd.CommandStore(key);
	}
}



