#include <stdio.h>
#include <File.h>
#include <Parse.h>
/*
gcc -o parse.o -I"$(pwd)"/include src/Parse.c -c;
gcc -o main.o -I"$(pwd)"/include src/Main.c -c;
gcc -o file.o -I"$(pwd)"/include src/File.c -c;
gcc *.o -o bin/newout;
bin/newout my-db.db;

outputs:
Num Employees: 255
*/

int main(int argc, char *argv[1]) {

	int fd, num_employees;

	if (argc != 2) {
		printf("Usage: %s <Filename>\n", argv[0]);
		return 0;
	}

	// octal-644 (0644) gives me R/W gives other people in my group read permission
	fd = open_rw_file(argv[1]);
	if (fd == -1) {
		return -1;
	}

	if (parseFileHeader(fd, &num_employees)) {
		return -1;
	}
	
	printf("Num Employees: %d\n", num_employees);

	return 0;
}