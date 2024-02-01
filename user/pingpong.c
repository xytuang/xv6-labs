
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

int main(int argc, char* argv[]){
	int ping[2];
	int pong[2];
	pipe(ping);
	pipe(pong);
	char buf[512];
	int pid = fork();
	if (pid == 0){
		read(ping[1], buf, 1);
		printf("Child %d:received ping\n", getpid());	
		write(pong[0], buf, 1);
		exit(0);
	}
	else {	
		write(ping[0], buf, 1);
		wait(NULL);
		read(pong[1], buf, 1);
		printf("Parent %d:received pong\n", getpid());	
		exit(0);
	}
	exit(0);
}
