#include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

int main() {
	/*
	In Linux, every program you run has three file descriptors open by default

	 0: stdin - a file that represents the input to your program from the command line
	 1: stdout - a file that represents the output of your program to the command line
	 2: stderr - a file that represents the output of your program, but containing only errors
	*/

	int fd = open("./test_file.txt", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}
	return 0;
}