#include "stdio.h"
#include "string.h"
int main(int argc, char *argv[]){
	
	int spans, distance;
	int result=0;
	spans=atoi(argv[1]);		//str to int
	distance=atoi(argv[2]);		//
	result=distance*(spans*(spans+1))/2;
	printf("%d\n",result);
	return 0;
}