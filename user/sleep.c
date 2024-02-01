

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
	if(argc != 2){
		fprintf(2, "usage: sleep seconds\n");
		exit(1);
	}
	int seconds;
	if((seconds = atoi(argv[1])) == 0){
		fprintf(2, "seconds must be a number\n");
		exit(1);
	}
	sleep(seconds);
	printf("Sleep was a success after %d seconds!\n", seconds);	
	exit(0);
}
