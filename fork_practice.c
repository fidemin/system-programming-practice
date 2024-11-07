#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	printf("running: %d\n", (int) getpid());
	int a = 100;

	int fd = open("tempfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0744);

	int pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (pid > 0) {
		// main process
		const char *text = "parent\n";
		ssize_t bytes_written = write(fd, text, 7);

		usleep(1000);
		printf("Good Bye\n");
		printf("AFTER main: a = %d\n", a);
		close(fd);
	} else {
		// child process
		const char *text = "child\n";
		ssize_t bytes_written = write(fd, text, 6);

		printf("Hello\n");

		printf("BEFORE child: a = %d\n", a);
		a = 101;
		printf("AFTER child: a = %d\n", a);


		execl("/bin/ls", "ls", "-l", (char *) NULL);
        // If execl() fails, this will be printed
        perror("execl failed");
        return 1;
	}
}
