#include "stdio.h"
#include "string.h"
int main(int argc, char *argv[]){
	
	int stairs=0;
	int steps=0;
	int answer=0;
	for(int i=0;i<strlen(argv[1]);i++){
		stairs=stairs*10 +argv[1][i]-'0';	//converting number of stairs to int
	}
	for(int i=0;i<strlen(argv[2]);i++){
		steps=steps*10 +argv[2][i]-'0';		//converting number of steps over to int
	}
	answer = stairs%(++steps)!=0 ? ( stairs/(steps) +1 ) : (stairs/steps );
	printf("%d\n",answer);
	return 0;
}