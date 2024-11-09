#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	printf("running: %d\n", (int) getpid());
	int a = 100;

	int pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (pid > 0) {
		// main process
		wait(NULL);
		printf("a in main process: %d\n", a);
	} else {
		a = 102;
		printf("a in child process: %d\n", a);
	}
}
