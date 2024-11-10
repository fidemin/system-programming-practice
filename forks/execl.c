#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	printf("running: %d\n", (int) getpid());

	int fd = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744);

	int pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (pid > 0) {
		// main process
		wait(NULL);
	} else {
		// child process
		execl("/bin/ls", "ls", "-alrth", (char *) NULL);
        // If execl() fails, this will be printed
        perror("execl failed");
        return 1;
	}
}