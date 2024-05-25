#include <stdio.h>
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
int initialize_employee(struct s_Employee *e){
	// i_num_employees will increment whenever 
	//	this function is called
	static int i_num_employees = 0;
	i_num_employees++;

	e->id = i_num_employees;
	e->income = 0;
	e->staff = false;

	return i_num_employees;
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

	for (int i = 0; i < n; ++i)
	{
		int id = initialize_employee(&employees[i]);
		printf("This employee's ID is: %d\n", id);
	}

	free(employees);
	// make sure that employees is no longer available so
	//	we don't "use after free'd"
	employees = NULL;

	return 0;
}