#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "Parse.h"

void list_employees(struct dbheader_t *dbhdr, struct employee_t *employees){
	int i = 0;
	for (i = 0; i < dbhdr->count; i++)
	{
		printf("Employee %d\n", i);
		printf("\t Name: %s\n", employees[i].name);
		printf("\t Address: %s\n", employees[i].address);
		printf("\t Hours: %d\n", employees[i].hours);
	}
}


int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring) {
	printf("%s\n", addstring);

	char *name = strtok(addstring, ",");

	char *addr = strtok(NULL, ",");

	char *hours = strtok(NULL, ",");

	printf("%s %s %s\n", name, addr, hours);

	
	strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
	strncpy(employees[dbhdr->count-1].address, addr, sizeof(employees[dbhdr->count-1].address));

	employees[dbhdr->count-1].hours = atoi(hours);
	

	return STATUS_SUCCESS;
}

int remove_employee_from_file(int fd,struct dbheader_t *dbhdr, int previous_num_employees){
	// clear file since it shrunk after losing an employee
	ftruncate(fd, 0);

	return STATUS_SUCCESS;
}


int remove_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *removestring) {
	printf("%s\n", removestring);
	bool found_employee = false;
	// char *name = strtok(addstring, ",");

	// char *addr = strtok(NULL, ",");

	// char *hours = strtok(NULL, ",");

	// printf("%s %s %s\n", name, addr, hours);
	
	// strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
	// strncpy(employees[dbhdr->count-1].address, addr, sizeof(employees[dbhdr->count-1].address));

	// employees[dbhdr->count-1].hours = atoi(hours);
	
	for (int i = 0; i < dbhdr->count; i++)
	{
		printf("%s\n", employees[i].name);
		if(strcmp(employees[i].name, removestring) == 0) {
			found_employee = true;
			continue;
		}

		if (found_employee) {
			employees[i - 1] = employees [i];
		}
	}

	// employees[dbhdr->count - 1] = {};

	return found_employee ? STATUS_SUCCESS : STATUS_ERROR;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {
	if (fd < 0) {
		printf("Got a bad FD from the user\n");
		return STATUS_ERROR;
	}


	int count = dbhdr->count;

	struct employee_t *employees = calloc(count, sizeof(struct employee_t));
	if (employees == -1) {
		printf("Malloc failed\n");
		return STATUS_ERROR;
	}

	read(fd, employees, count*sizeof(struct employee_t));

	int i = 0;
	for (; i < count; i++) {
		employees[i].hours = ntohl(employees[i].hours);
	}

	*employeesOut = employees;
	return STATUS_SUCCESS;

}


int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees) {
	if (fd < 0) {
		printf("Got a bad FD from the user\n");
		return STATUS_ERROR;
	}

	int realcount = dbhdr->count;

	dbhdr->magic = htonl(dbhdr->magic);
	dbhdr->filesize = htonl(sizeof(struct dbheader_t) + (sizeof(struct employee_t) * realcount));
	dbhdr->count = htons(dbhdr->count);
	dbhdr->version = htons(dbhdr->version);
	printf("%d\n", realcount);
	lseek(fd, 0, SEEK_SET);

	write(fd, dbhdr, sizeof(struct dbheader_t));

	int i = 0;
	for (; i < realcount; i++) {
		employees[i].hours = htonl(employees[i].hours);
		printf("Writing Employee %d to database file\n", i);
		write(fd, &employees[i], sizeof(struct employee_t));
	}

	return STATUS_SUCCESS;

}	

int validate_db_header(int fd, struct dbheader_t **headerOut) {
	if (fd < 0) {
		printf("Got a bad FD from the user\n");
		return STATUS_ERROR;
	}

	struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
	if (header == -1) {
		printf("Malloc failed create a db header\n");
		return STATUS_ERROR;
	}

	if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)) {
		perror("read");
		free(header);
		return STATUS_ERROR;
	}

	header->version = ntohs(header->version);
	header->count = ntohs(header->count);
	header->magic = ntohl(header->magic);
	header->filesize = ntohl(header->filesize);

	if (header->magic != HEADER_MAGIC) {
		printf("Impromper header magic\n");
		free(header);
		return -1;
	}


	if (header->version != 1) {
		printf("Impromper header version\n");
		free(header);
		return -1;
	}

	struct stat dbstat = {0};
	fstat(fd, &dbstat);
	if (header->filesize != dbstat.st_size) {
		printf("Corrupted database; expected %d, got %ld\n", header->filesize, dbstat.st_size);
		free(header);
		return -1;
	}

	*headerOut = header;
}

int create_db_header(int fd, struct dbheader_t **headerOut) {
	struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
	if (header == -1) {
		printf("Malloc failed to create db header\n");
		return STATUS_ERROR;
	}

	header->version = 0x1;
	header->count = 0;
	header->magic = HEADER_MAGIC;
	header->filesize = sizeof(struct dbheader_t);

	*headerOut = header;

	return STATUS_SUCCESS;
}

