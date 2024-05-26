#include <stdio.h>
#include <File.h>
#include <Parse.h>
#include <stdbool.h>
#include <getopt.h>
#include "common.h"

/*
gcc -o parse.o -I"$(pwd)"/include src/Parse.c -c;
gcc -o main.o -I"$(pwd)"/include src/Main.c -c;
gcc -o file.o -I"$(pwd)"/include src/File.c -c;
gcc *.o -o bin/newout;
bin/newout my-db.db;

outputs:
Num Employees: 255
*/

void print_usage(char *argv[]) {
	printf("Usage %s: -n -f <database file>\n", argv[0]);
	printf("\t -n - create new database file\n");
	printf("\t -f - (requierd) path to database file\n");
	return;
}

int main(int argc, char *argv[]) {

	char *file_path = NULL;
	bool new_file = false;
	int c = 0;

	int database_fd = -1;

	// n is a boolean flag
	// f is a file path argument (:)
	while((c=getopt(argc, argv, "nf:")) != -1) {
		switch(c) {
			case 'n':
				new_file = true;
				break;
			case 'f':
				file_path = optarg;
				break;
			case '?':
				printf("Unkown argument -%c\n", c);
				break;
			default:
				return -1;
				break;
		} 
	}

	if (file_path == NULL) {
		printf("file path is a required argument\n");
		print_usage(argv);

		return 0;
	}

	printf("new file bool: %d\n", new_file);
	printf("file path: %s\n", file_path);

	if (new_file) {
		database_fd = create_databse_file(file_path);
		if (database_fd == STATUS_ERROR) {
			printf("Could not create database file\n");
			return -1;
		}
	} else {
		database_fd = open_databse_file(file_path);
		if (database_fd == STATUS_ERROR) {
			printf("Could not open database file\n");
			return -1;
		}
	}



	// int fd, num_employees;

	// // if (argc != 2) {
	// // 	printf("Usage: %s <Filename>\n", argv[0]);
	// // 	return 0;
	// // }

	// // octal-644 (0644) gives me R/W gives other people in my group read permission
	// fd = open_rw_file(argv[1]);
	// if (fd == -1) {
	// 	return -1;
	// }

	// if (parseFileHeader(fd, &num_employees)) {
	// 	return -1;
	// }
	
	// printf("Num Employees: %d\n", num_employees);

	return 0;
}