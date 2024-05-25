#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct s_Employee {
	int id;
	int income;
	bool staff;
};

// Shows why pointers are important
//	In this case, initialize_employee needs access to the 
//	scope Ralph is in
void initialize_employee(struct s_Employee *e){
	e->id = 0;
	e->income = 0;
	e->staff = false;

	return;
}

int main() {

	int n = 4;

	// Employees is now a pointer which can point to an infinite number of elements further along in memory
	//	With this we no longer rely on a set constant in our code 
	//	but could dynamically extend the array of employees 
	//	based on perhaps a database header 
	//	containing up to date information
	struct s_Employee *employees = malloc(sizeof(struct s_Employee) * n);
	if (employees == NULL) {
		// Ensure the Allocator actually found memory to spare
		printf("The allocator failed\n");
		return -1;
	}

	initialize_employee(&employees[0]);

	printf("Ralph's Income: %d\n", employees[0].income);

	free(employees);
	// make sure that employees is no longer available so
	//	we don't "use after free'd"
	employees = NULL;

	return 0;
}