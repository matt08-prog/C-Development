#include <stdio.h>
#include <stdlib.h>
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
	char *add_string = NULL;
	char *remove_string = NULL;

	bool new_file = false;
	bool should_list_employees = false;
	int c = 0;

	int database_fd = -1;
	struct dbheader_t *dbhdr = NULL;
	struct employee_t *employees = NULL;

	// n is a boolean flag - new file
	// l is a boolean flag - list all employees
	// a is a String argument (:) - add employee <X>
	// r is a String argument (:) - remove employee <X>
	// f is a String argument (:) - REQUIRED, file path
	while((c=getopt(argc, argv, "na:f:r:l")) != -1) {
		switch(c) {
			case 'n':
				new_file = true;
				break;
			case 'f':
				file_path = optarg;
				break;
			case 'a':
				add_string = optarg;
				break;
			case 'l':
				should_list_employees = true;
				break;
			case 'r':
				remove_string = optarg;
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

		if(create_db_header(database_fd, &dbhdr) == STATUS_ERROR) {
			printf("Failed to create database file\n");
			return -1;
		}
	} else {
		database_fd = open_databse_file(file_path);
		if (database_fd == STATUS_ERROR) {
			printf("Could not open database file\n");
			return -1;
		}



		if (validate_db_header(database_fd, &dbhdr) == STATUS_ERROR) {
			printf("Failed to vaildate database file\n");
			return -1;
		}
	}

	if (read_employees(database_fd, dbhdr, &employees) != STATUS_SUCCESS) {
		printf("Failed to read employees\n");
		return 0;
	}

	if (remove_string) {
		if(remove_employee(dbhdr, employees, remove_string) != STATUS_SUCCESS) {
			printf("Failed to remove employee: %s\n", remove_string);
			return 0;
		}
		if (remove_employee_from_file(database_fd, dbhdr, dbhdr->count) != STATUS_SUCCESS) {
			printf("Failed to clear employees from file");
			return -1;
		}

		dbhdr->count--;
		printf("%d\n", dbhdr->count);
		employees = realloc(employees, dbhdr->count*(sizeof(struct employee_t)));
		// return 0;

	}

	if (add_string) {
		dbhdr->count++;
		employees = realloc(employees, dbhdr->count*(sizeof(struct employee_t)));

		if(add_employee(dbhdr, employees, add_string) != STATUS_SUCCESS) {
			printf("Failed to add employee: %s\n", add_string);
			return 0;
		}
	}

	if (should_list_employees) {
		list_employees(dbhdr, employees);
	}

	output_file(database_fd, dbhdr, employees);
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