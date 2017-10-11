/*
 *	object manager class
 */

#include<Object.h>
#include<Background.h>
#include<AngleSetting.h>

extern vector<cube> cubes; //defined in Objects.cpp
extern vector<tube> tubes; //defined in Objects.cpp
extern vector<pipe> pipes; //defined in Objects.cpp
extern Background Bkg;
extern ColorBar Clb;
extern AngleSetting Agl;

manager::manager(){
	windowW = 500;
	windowH = 500;
	ID = 0;
	Ncube = 0;
	Ntube = 0;
	Npipe = 0;
	mode.reserve(100);
	mode.push_back(OBJCUBE);
	pos.reserve(100);
	Position pos0 = {0,0,0};
	pos.push_back(pos0);
	StoreColor(ms_white_plastic);
	MoveFlag = false;
}

manager::~manager(){
}

void manager::Resize(int wx, int wy){
	windowW = wx;
	windowH = wy;
}

int manager::GetMode(){
	return mode[ID];
}

void manager::SetMode(int MODE){
	mode.push_back(MODE);
	ID = mode.size()-1;
	if(MODE==OBJCUBE && 0<cubes.size()){
		pos.push_back(cubes[cubes.size()-1].pos);
		++Ncube;
	}
	if(MODE==OBJTUBE && 0<tubes.size()){
		pos.push_back(tubes[tubes.size()-1].pos);
		++Ntube;
	}
	if(MODE==OBJPIPE && 0<pipes.size()){
		pos.push_back(pipes[pipes.size()-1].pos);
		++Npipe;
	}
	Agl.SetCamera();
}

void manager::NewObject(){
	if(GetMode()==OBJCUBE){
		cubes.push_back(cube(10,Agl.GetPos(),Agl.theta));
		cubes[cubes.size()-1].colorMS(obj_color);
		SetMode(OBJCUBE);
	}
	if(GetMode()==OBJTUBE){
		tubes.push_back(tube(5,10,Agl.GetPos(),Agl.theta));
		tubes[tubes.size()-1].colorMS(obj_color);
		SetMode(OBJTUBE);
	}
	if(GetMode()==OBJPIPE){
		pipes.push_back(pipe(5,1,10,Agl.GetPos(),Agl.theta));
		pipes[pipes.size()-1].colorMS(obj_color);
		SetMode(OBJPIPE);
	}
}

void manager::NewObject(int MODE){
	mode.push_back(MODE);
	ID = mode.size()-1;
	if(MODE==OBJCUBE){
		cubes.push_back(cube(10,Agl.GetPos(),Agl.theta));
		pos.push_back(cubes[cubes.size()-1].pos);
		cubes[cubes.size()-1].colorMS(obj_color);
		++Ncube;
	}
	if(MODE==OBJTUBE){
		tubes.push_back(tube(5,10,Agl.GetPos(),Agl.theta));
		pos.push_back(tubes[tubes.size()-1].pos);
		tubes[tubes.size()-1].colorMS(obj_color);
		++Ntube;
	}
	if(MODE==OBJPIPE){
		pipes.push_back(pipe(5,1,10,Agl.GetPos(),Agl.theta));
		pos.push_back(pipes[pipes.size()-1].pos);
		pipes[pipes.size()-1].colorMS(obj_color);
		++Npipe;
	}
	Agl.SetCamera();
}

void manager::Reset(){
	int tmpid = ID;
	for(int i=0;i<tmpid;++i){
		Remove();
	}
}

void manager::Remove(){
	bool flag = false;
	if(GetMode()==OBJCUBE){
		if(0<Ncube && 0<cubes.size()){
			cubes.pop_back();
			flag = true;
		}
	}
	else if(GetMode()==OBJTUBE){
		if(0<Ntube && 0<tubes.size()){
			tubes.pop_back();
			flag = true;
		}
	}
	else if(GetMode()==OBJPIPE){
		if(0<Npipe && 0<pipes.size()){
			pipes.pop_back();
			flag = true;
		}
	}
	if(flag){
		if(ID==1){
			mode[0] = GetMode(); 
			StoreColor(ms_white_plastic);
		}
		if(GetMode()==OBJCUBE) --Ncube;
		if(GetMode()==OBJTUBE) --Ntube;
		if(GetMode()==OBJPIPE) --Npipe;
		mode.pop_back();
		pos.pop_back();
		if(0<mode.size()) ID = mode.size()-1;
	}
	Agl.SetCamera();
}

void manager::Copy(){
	if(GetMode()==OBJCUBE){
		if(0<Ncube && 0<cubes.size()){
			cubes.push_back(cubes.back());
			SetMode(OBJCUBE);
			if(cubes[cubes.size()-1].Mflag)
				cubes[cubes.size()-1].motion();
			if(cubes[cubes.size()-1].Rflag)
				cubes[cubes.size()-1].rotation();
		}
	}
	else if(GetMode()==OBJTUBE){
		if(0<Ntube && 0<tubes.size()){
			tubes.push_back(tubes.back());
			SetMode(OBJTUBE);
			if(tubes[tubes.size()-1].Mflag)
				tubes[tubes.size()-1].motion();
			if(tubes[tubes.size()-1].Rflag)
				tubes[tubes.size()-1].rotation();
		}
	}
	else if(GetMode()==OBJPIPE){
		if(0<Npipe && 0<pipes.size()){
			pipes.push_back(pipes.back());
			SetMode(OBJPIPE);
			if(pipes[pipes.size()-1].Mflag)
				pipes[pipes.size()-1].motion();
			if(pipes[pipes.size()-1].Rflag)
				pipes[pipes.size()-1].rotation();
		}
	}
	Agl.SetCamera();
}

void manager::Copy(int N){
	for(int i=0;i<N;++i){
		if(GetMode()==OBJCUBE){
			if(0<Ncube && 0<cubes.size()){
				cubes.push_back(cubes.back());
				SetMode(OBJCUBE);
				if(cubes[cubes.size()-1].Mflag)
					cubes[cubes.size()-1].motion();
				if(cubes[cubes.size()-1].Rflag)
					cubes[cubes.size()-1].rotation();
			}
		}
		else if(GetMode()==OBJTUBE){
			if(0<Ntube && 0<tubes.size()){
				tubes.push_back(tubes.back());
				SetMode(OBJTUBE);
				if(tubes[tubes.size()-1].Mflag)
					tubes[tubes.size()-1].motion();
				if(tubes[tubes.size()-1].Rflag)
					tubes[tubes.size()-1].rotation();
			}
		}
		else if(GetMode()==OBJPIPE){
			if(0<Npipe && 0<pipes.size()){
				pipes.push_back(pipes.back());
				SetMode(OBJPIPE);
				if(pipes[pipes.size()-1].Mflag)
					pipes[pipes.size()-1].motion();
				if(pipes[pipes.size()-1].Rflag)
					pipes[pipes.size()-1].rotation();
			}
		}
	}
	Agl.SetCamera();
}

void manager::Copy(double x, double y, double z){
	if(GetMode()==OBJCUBE){
		if(0<Ncube && 0<cubes.size()){
			cubes.push_back(cubes.back());
			SetMode(OBJCUBE);
			Move(x,y,z);
			if(cubes[cubes.size()-1].Mflag)
				cubes[cubes.size()-1].motion();
			if(cubes[cubes.size()-1].Rflag)
				cubes[cubes.size()-1].rotation();
		}
	}
	else if(mode[ID]==OBJTUBE){
		if(0<Ntube && 0<tubes.size()){
			tubes.push_back(tubes.back());
			SetMode(OBJTUBE);
			Move(x,y,z);
			if(tubes[tubes.size()-1].Mflag)
				tubes[tubes.size()-1].motion();
			if(tubes[tubes.size()-1].Rflag)
				tubes[tubes.size()-1].rotation();
		}
	}
	else if(mode[ID]==OBJPIPE){
		if(0<Npipe && 0<pipes.size()){
			pipes.push_back(pipes.back());
			SetMode(OBJPIPE);
			Move(x,y,z);
			if(pipes[pipes.size()-1].Mflag)
				pipes[pipes.size()-1].motion();
			if(pipes[pipes.size()-1].Rflag)
				pipes[pipes.size()-1].rotation();
		}
	}
	Agl.SetCamera();
}

void manager::Move(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size()){
		cubes[cubes.size()-1].locate(Agl.GetPos());
		pos[ID].x = cubes[cubes.size()-1].pos.x;
		pos[ID].y = cubes[cubes.size()-1].pos.y;
		pos[ID].z = cubes[cubes.size()-1].pos.z;
	}
	else if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size()){
		tubes[tubes.size()-1].locate(Agl.GetPos());
		pos[ID].x = tubes[tubes.size()-1].pos.x;
		pos[ID].y = tubes[tubes.size()-1].pos.y;
		pos[ID].z = tubes[tubes.size()-1].pos.z;
	}
	else if(GetMode()==OBJPIPE && 0<Npipe && 0<pipes.size()){
		pipes[pipes.size()-1].locate(Agl.GetPos());
		pos[ID].x = pipes[pipes.size()-1].pos.x;
		pos[ID].y = pipes[pipes.size()-1].pos.y;
		pos[ID].z = pipes[pipes.size()-1].pos.z;
	}
	Agl.SetCamera();
}

void manager::Move(double x, double y, double z){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size()){
		cubes[cubes.size()-1].locate(x,y,z);
		pos[ID].x = cubes[cubes.size()-1].pos.x;
		pos[ID].y = cubes[cubes.size()-1].pos.y;
		pos[ID].z = cubes[cubes.size()-1].pos.z;
	}
	else if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size()){
		tubes[tubes.size()-1].locate(x,y,z);
		pos[ID].x = tubes[tubes.size()-1].pos.x;
		pos[ID].y = tubes[tubes.size()-1].pos.y;
		pos[ID].z = tubes[tubes.size()-1].pos.z;
	}
	else if(GetMode()==OBJPIPE && 0<Npipe && 0<tubes.size()){
		pipes[tubes.size()-1].locate(x,y,z);
		pos[ID].x = pipes[tubes.size()-1].pos.x;
		pos[ID].y = pipes[tubes.size()-1].pos.y;
		pos[ID].z = pipes[tubes.size()-1].pos.z;
	}
	Agl.SetCamera();
}

void manager::Rotation(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size())
		cubes[cubes.size()-1].rotation();
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size())
		tubes[tubes.size()-1].rotation();
	if(GetMode()==OBJPIPE && 0<Npipe && 0<pipes.size())
		pipes[pipes.size()-1].rotation();
}

void manager::Motion(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size())
		cubes[cubes.size()-1].motion();
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size())
		tubes[tubes.size()-1].motion();
	if(GetMode()==OBJPIPE && 0<Npipe && 0<pipes.size())
		pipes[pipes.size()-1].motion();
}

void manager::Stop(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size())
		cubes[cubes.size()-1].stop();
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size())
		tubes[tubes.size()-1].stop();
	if(GetMode()==OBJPIPE && 0<Npipe && 0<pipes.size())
		pipes[pipes.size()-1].stop();
}

#define COLORMODE(MODE,N,objs){\
	if(GetMode()==MODE && 0<N && 0<objs.size()){\
		if(Clb.Flag()) Clb.Off();\
		else Clb.On();\
	}\
}
void manager::ColorMode(){
	COLORMODE(OBJCUBE,Ncube,cubes);
	COLORMODE(OBJTUBE,Ntube,tubes);
	COLORMODE(OBJPIPE,Npipe,pipes);
}

#define COLOR(_func,_objs){\
	_objs[_objs.size()-1]._func;\
	StoreColor(_objs[_objs.size()-1].color);\
}
bool manager::ColorCB(int x){
	bool flag = true;
	switch(GetMode()){
		case OBJCUBE:
			COLOR(colorCB(x),cubes);
			break;
		case OBJTUBE:
			COLOR(colorCB(x),tubes);
			break;
		case OBJPIPE:
			COLOR(colorCB(x),pipes);
			break;
		default:
			flag = false;
			break;
	}
	return flag;
}

void manager::ColorRGB(double R, double G, double B){
	switch(GetMode()){
		case OBJCUBE:
			COLOR(colorRGB(R,G,B),cubes);
			break;
		case OBJTUBE:
			COLOR(colorRGB(R,G,B),tubes);
			break;
		case OBJPIPE:
			COLOR(colorRGB(R,G,B),pipes);
			break;
		default:
			break;
	}
}
#undef COLOR
#undef COLORMODE

void manager::StoreColor(MaterialStruct ms_color){
	for(int i=0;i<4;++i){
		obj_color.diffuse[i]  = ms_color.diffuse[i];
		obj_color.ambient[i]  = ms_color.ambient[i];
		obj_color.specular[i] = ms_color.specular[i];
	} 
	obj_color.shininess[0] = ms_color.shininess[0];
}

void manager::ChangeParameters(){
	for(unsigned int i=cubes.size()-Ncube;i<cubes.size();++i)
		cubes[i].changeparameters();
	for(unsigned int i=tubes.size()-Ntube;i<tubes.size();++i)
		tubes[i].changeparameters();
	for(unsigned int i=pipes.size()-Npipe;i<pipes.size();++i)
		pipes[i].changeparameters();
}

void manager::Draw(bool GFLAG){
	for(unsigned int i=cubes.size()-Ncube;i<cubes.size();++i)
		cubes[i].draw();
	for(unsigned int i=tubes.size()-Ntube;i<tubes.size();++i)
		tubes[i].draw();
	for(unsigned int i=pipes.size()-Npipe;i<pipes.size();++i)
		pipes[i].draw();
	if(!GFLAG){
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowW, windowH, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glColor3d(1,1,1);
		char s[128];
		if(GetMode()==OBJCUBE){
			sprintf(s,"[%d] CUBE",ID);
			glDrawString(s,15,30);
		}
		if(GetMode()==OBJTUBE){
			sprintf(s,"[%d] TUBE",ID);
			glDrawString(s,15,30);
		}
		sprintf(s,"(%+4.1f %+4.1f %+4.1f)",GetPos().x,GetPos().y,GetPos().z);
		glDrawString(s,15,45);

		sprintf(s,"cube : %d",Ncube);
		glDrawString(s,15,60);
		sprintf(s,"tube : %d",Ntube);
		glDrawString(s,15,75);
		sprintf(s,"pipe : %d",Npipe);
		glDrawString(s,15,90);

		int H =  Bkg.GetTime()/100*12;
		int M = (Bkg.GetTime()/100*12-H)*60;
		H += 7;
		sprintf(s,"%02d:%02d",H,M);
		glDrawString2(s,windowW-60,20);

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
	}
}

void manager::IncID(){
	if(ID<(int)mode.size()-1) ++ID;
	Agl.SetCamera();
}

void manager::DecID(){
	if(0<ID) --ID;
	Agl.SetCamera();
}

Position manager::GetPos(){
	return pos[ID];
}

void manager::UnsetFlags(){
	MoveFlag = false;
}


