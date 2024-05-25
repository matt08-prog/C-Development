#include <stdio.h>
#include <stdbool.h>

#define MAX_IDS 32
#define MAX_employees 1000


struct StructuresEmployee {
	int id;
	char firstname[64];
	char lastname[64];
	float income;
	bool ismanager;
};

int main() {
	struct StructuresEmployee employees[MAX_employees];

	for (int i = 0; i < MAX_employees; ++i)
	{
		employees[i].income = 0;
		employees[i].ismanager = false;
	}
	printf("%f\n", employees[0].income);
	return 0;
}