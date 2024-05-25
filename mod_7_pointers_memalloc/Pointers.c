#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct s_Employee {
	int id;
	int income;
	bool staff;
};

// Show why pointers are important
//	In this case, initialize_employee needs access to the 
//	scope Ralph is in
void initialize_employee(struct s_Employee *e){
	e->id = 0;
	e->income = 0;
	e->staff = false;

	return;
}

int main() {

	int x = 3;

	int *pX = &x;

	// Pointer value
	printf("x's Address: %p\n", pX);

	// dereference pointer
	printf("x's Value: %d\n", *pX);
	

	// Another pointer example
	struct s_Employee Ralph;

	initialize_employee(&Ralph);

	printf("Ralph's Income: %d\n", Ralph.income);

	return 0;
}