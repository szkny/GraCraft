#ifndef Color_h_
#define Color_h_

/************ extern Material Color Structure ************/

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

struct MaterialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess[1];
};

/* 3D-Object Color Setting */
extern void glMaterialColor(struct MaterialStruct ms_X);

/********** by M.J.Kilgard & M.Yamamoto ***********/
extern MaterialStruct ms_ruby;
extern MaterialStruct ms_emerald;
extern MaterialStruct ms_jade;
extern MaterialStruct ms_obsidian ;
extern MaterialStruct ms_pearl ;
extern MaterialStruct ms_turquoise ;
extern MaterialStruct ms_brass ;
extern MaterialStruct ms_bronze ;
extern MaterialStruct ms_chrome ;
extern MaterialStruct ms_copper ;
extern MaterialStruct ms_gold ;
extern MaterialStruct ms_silver ;
extern MaterialStruct ms_black_plastic ;
extern MaterialStruct ms_cyan_plastic ;
extern MaterialStruct ms_green_plastic ;
extern MaterialStruct ms_red_plastic ;
extern MaterialStruct ms_white_plastic ;
extern MaterialStruct ms_yellow_plastic ;
extern MaterialStruct ms_black_rubber ;
extern MaterialStruct ms_cyan_rubber ;
extern MaterialStruct ms_red_rubber ;
extern MaterialStruct ms_green_rubber ;
extern MaterialStruct ms_blue_rubber ;
extern MaterialStruct ms_white_rubber ;
extern MaterialStruct ms_yellow_rubber ;

/********    My Products    ********/
/* something metal */
extern MaterialStruct ms_metal;
extern MaterialStruct ms_TUNA;
extern MaterialStruct ms_MAGRO;
extern MaterialStruct ms_betapla;
extern MaterialStruct ms_PMT;
extern MaterialStruct ms_duct;
extern MaterialStruct ms_moldsteel;
extern MaterialStruct ms_Aluminium;
extern MaterialStruct ms_Aluminium2;
extern MaterialStruct ms_Alframerid;
extern MaterialStruct ms_acryl;
extern MaterialStruct ms_kapton;
extern MaterialStruct ms_lead;
extern MaterialStruct ms_Qmagnet;
extern MaterialStruct ms_Qframe;
extern MaterialStruct ms_floor;
extern MaterialStruct ms_dewar;
extern MaterialStruct ms_paint;
extern MaterialStruct ms_Ge;
extern MaterialStruct ms_Gecap;
extern MaterialStruct ms_Liglass;
extern MaterialStruct ms_magshield;
extern MaterialStruct ms_Li;
extern MaterialStruct ms_HandSpinner;
extern MaterialStruct ms_Island;
extern MaterialStruct ms_Sea;
extern MaterialStruct ms_Sun;
/*******************************************/


#endif //"Color_h_"
