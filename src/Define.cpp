#include <stdio.h>
#include <stdlib.h>
#include <Define.h>

//uniformed random number (0~1)
double randf(void){
    rand();rand();rand();rand();rand();rand();
    return (double)rand()/RAND_MAX;
}

//random sign (±1)
int randpm(void){
	rand();rand();rand();rand();rand();rand();
	if(rand()<RAND_MAX/2)
		return 1;
	else
		return -1;
}

