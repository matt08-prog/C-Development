#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

int open_rw_file(char *path){
	int fd;

	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
	}

	return fd;
}

int create_databse_file(char *file_name){
	int fd = open(file_name, O_RDONLY);

	// ensure file doesn't already exist
	if (fd != -1) {
		close(fd);
		printf("File already exists: %s\n", file_name);
		return STATUS_ERROR;
	}

	// create new file
	fd = open(file_name, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open");
		return STATUS_ERROR;
	}

	return fd;
}

int open_databse_file(char *file_name){
	int fd = open(file_name, O_RDONLY);

	// open file
	fd = open(file_name, O_RDWR, 0644);
	if (fd == -1) {
		perror("open");
		printf("File does not exist: %s\n", file_name);
		return STATUS_ERROR;
	}

	return fd;
}
