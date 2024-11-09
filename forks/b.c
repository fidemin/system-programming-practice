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
		const char *text = "parent\n";
		ssize_t bytes_written = write(fd, text, 7);
		printf("bytes written in main: %ld\n", bytes_written);
		wait(NULL);
		
		close(fd);
	} else {
		// child process
		const char *text = "child\n";
		ssize_t bytes_written = write(fd, text, 6);
		printf("bytes written in child: %ld\n", bytes_written);
	}
}
