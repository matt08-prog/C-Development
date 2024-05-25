#include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[1]) {
	/*
	In Linux, every program you run has three file descriptors open by default

	 0: stdin - a file that represents the input to your program from the command line
	 1: stdout - a file that represents the output of your program to the command line
	 2: stderr - a file that represents the output of your program, but containing only errors
	*/

	if (argc != 2) {
		printf("Usage: %s <Filename>\n", argv[0]);
		return 0;
	}

	// octal-644 (0644) gives me R/W gives other people in my group read permission
	int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	char *mydata = "This is another test\n";
	// fd is the file descriptor
	write(fd, mydata, strlen(mydata));

	close(fd);

	return 0;
}