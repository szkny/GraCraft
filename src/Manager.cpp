/*
 *	object manager class
 */

#include<Object.h>
#include<Background.h>
#include<AngleSetting.h>

extern vector<cube> cubes; //defined in Objects.cpp
extern vector<tube> tubes; //defined in Objects.cpp
extern Background Bkg;
extern ColorBar Clb;
extern AngleSetting Agl;

manager::manager(){
	windowW = 500;
	windowH = 500;
	ID = 0;
	Ncube = 0;
	Ntube = 0;
	mode.reserve(100);
	mode.push_back(OBJCUBE);
	pos.reserve(100);
	Position pos0 = {0,0,0};
	pos.push_back(pos0);
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
		pos.push_back(cubes[cubes.size()-1].GetPos());
		++Ncube;
	}
	if(MODE==OBJTUBE && 0<tubes.size()){
		pos.push_back(tubes[tubes.size()-1].GetPos());
		++Ntube;
	}
	Agl.SetCamera();
}

void manager::NewObject(int MODE){
	mode.push_back(MODE);
	ID = mode.size()-1;
	if(MODE==OBJCUBE){
		cubes.push_back(cube(10,Agl.GetPos().x,Agl.GetPos().y,Agl.GetPos().z));
		pos.push_back(cubes[cubes.size()-1].GetPos());
		++Ncube;
	}
	if(MODE==OBJTUBE){
		tubes.push_back(tube(5,10,Agl.GetPos().x,Agl.GetPos().y,Agl.GetPos().z));
		pos.push_back(tubes[tubes.size()-1].GetPos());
		++Ntube;
	}
	Agl.SetCamera();
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
	if(flag){
		if(GetMode()==OBJCUBE) --Ncube;
		if(GetMode()==OBJTUBE) --Ntube;
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
  			if(cubes[cubes.size()-1].getMflag())
  				cubes[cubes.size()-1].motion();
  		}
  	}
  	else if(GetMode()==OBJTUBE){
  		if(0<Ntube && 0<tubes.size()){
  			tubes.push_back(tubes.back());
  			SetMode(OBJTUBE);
  			if(tubes[tubes.size()-1].getMflag())
  				tubes[tubes.size()-1].motion();
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
  			if(cubes[cubes.size()-1].getMflag())
  				cubes[cubes.size()-1].motion();
  		}
  	}
  	else if(mode[ID]==OBJTUBE){
  		if(0<Ntube && 0<tubes.size()){
  			tubes.push_back(tubes.back());
  			SetMode(OBJTUBE);
			Move(x,y,z);
  			if(tubes[tubes.size()-1].getMflag())
  				tubes[tubes.size()-1].motion();
  		}
  	}
	Agl.SetCamera();
}

void manager::Move(double x, double y, double z){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size()){
		cubes[cubes.size()-1].locate(x,y,z);
		pos[ID].x = cubes[cubes.size()-1].GetPos().x;
		pos[ID].y = cubes[cubes.size()-1].GetPos().y;
		pos[ID].z = cubes[cubes.size()-1].GetPos().z;
	}
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size()){
		tubes[tubes.size()-1].locate(x,y,z);
		pos[ID].x = tubes[tubes.size()-1].GetPos().x;
		pos[ID].y = tubes[tubes.size()-1].GetPos().y;
		pos[ID].z = tubes[tubes.size()-1].GetPos().z;
	}
	Agl.SetCamera();
}

void manager::Rotation(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size())
		cubes[cubes.size()-1].rotation();
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size())
		tubes[tubes.size()-1].rotation();
}

void manager::Motion(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size())
		cubes[cubes.size()-1].motion();
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size())
		tubes[tubes.size()-1].motion();
}

void manager::Stop(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size())
		cubes[cubes.size()-1].stop();
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size())
		tubes[tubes.size()-1].stop();
}

void manager::Color(){
	if(GetMode()==OBJCUBE && 0<Ncube && 0<cubes.size()){
		if(Clb.Flag()) Clb.Off();
		else Clb.On();
	}
	if(GetMode()==OBJTUBE && 0<Ntube && 0<tubes.size()){
		if(Clb.Flag()) Clb.Off();
		else Clb.On();
	}
}

void manager::Draw(bool GFLAG){
	for(unsigned int i=cubes.size()-Ncube;i<cubes.size();++i)
		cubes[i].draw();
	for(unsigned int i=tubes.size()-Ntube;i<tubes.size();++i)
		tubes[i].draw();
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

Position manager::GetPos(){
	return pos[ID];
}

void manager::IncID(){
	if(ID<(int)mode.size()-1) ++ID;
	Agl.SetCamera();
}

void manager::DecID(){
	if(0<ID) --ID;
	Agl.SetCamera();
}

