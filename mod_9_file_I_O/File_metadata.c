#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

__attribute__((__packed__)) struct s_DatabaseHeader {
	u_short version;
	u_short num_employees;
	u_int file_length;
};

int main(int argc, char *argv[1]) {

	struct s_DatabaseHeader my_database = {0};
	struct stat db_stat = {0};

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

	if (read(fd, &my_database, sizeof(struct s_DatabaseHeader)) != sizeof(struct s_DatabaseHeader)) {
		perror("read");
		close(fd);
		return -1;
	}

	printf("Version: %d\n", my_database.version);
	printf("Num Employees: %d\n", my_database.num_employees);
	printf("File Length: %d\n", my_database.file_length);

	if (fstat(fd, &db_stat) == -1) {
		perror("stat");
		close(fd);
		return -1;
	}

	printf("DB File Length, reported by stat(): %lu\n", db_stat.st_size);

	if (db_stat.st_size != my_database.file_length){
		printf("Incorrect file Size found using stat()\n");
		printf("Expected %u but stat() returned %lu\n", my_database.file_length, db_stat.st_size);
		return -1;
	}

	return 0;
}