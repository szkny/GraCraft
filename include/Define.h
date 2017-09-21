#ifndef Define_h_
#define Define_h_

/***************************/
#include <stdio.h>
#include <stdlib.h>

//uniformed random number (0~1)
inline double randf(void){
    rand();rand();rand();rand();rand();rand();
    return (double)rand()/RAND_MAX;
}

//random sign (±1)
inline int randpm(void){
	rand();rand();rand();rand();rand();rand();
	if(rand()<RAND_MAX/2)
		return 1;
	else
		return -1;
}

#define PI 3.14159265359

/***************************/

#endif //"Define_h_"
