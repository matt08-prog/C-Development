#include <stdio.h>
#include <fcntl.h>
// #include <unistd.h>

int open_rw_file(char *path){
	int fd;

	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
	}

	return fd;
}
