#ifndef MyGLUT_h_
#define MyGLUT_h_

#include<Define.h>

/* Polygon Mode */
// bool PFLAG;    

/**************** Drawing Function ******************/

/* Drawing String Function (string,position x,position y) */
void glDrawString(const char *str, double x0, double y0);

/* Drawing Big String Function (string,position x,position y) */
void glDrawString2(const char *str, double x0, double y0);

/* Drawing Small String Function (string,position x,position y) */
void glDrawString3(const char *str, double x0, double y0);

/* Draw Rectangular Function (length1,length2,length3,position-xyz) */
void glRectangular(double lx, double ly, double lz, double x, double y, double z);

/* Draw Hexagonal Prism Function (radius,length,position—xyz) */
void glHexagon(double r, double l, double x, double y, double z);

/* Draw Cylinder Function (radius,length,position—xyz) */
void glCylinder(double r, double l, double x, double y, double z);

/* Draw Pipe Function (radius,thickness,length,position—xyz) */
void glPipe(double r,double d, double l, double x, double y, double z);

/* Draw N-Side Polygon Prism Function (N,radius,length,position—xyz) */
void glPrism(const int N, double r, double l, double x, double y, double z);

/* Draw Torus Function (radius,thickness,position—xyz) */
void glTorus(double r, double d, double x, double y, double z);

/* Draw Torus Function (radius,thickness,position—xyz) */
void glSphere(double r, double x, double y, double z);

/***************************/

#endif //"MyGLUT_h_"
