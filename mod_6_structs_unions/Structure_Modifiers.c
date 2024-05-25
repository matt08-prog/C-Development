#include <stdio.h>
#include <stdbool.h>

struct s_UnpackedStructuresEmployee {
	int id;
	char firstname[64];
	char lastname[64];
	float income;
	bool ismanager;
};

__attribute__((__packed__)) struct s_PackedStructuresEmployee {
	int id;
	char firstname[64];
	char lastname[64];
	float income;
	bool ismanager;
};

int main() {
	struct s_UnpackedStructuresEmployee unpacked_employees[MAX_employees];
	struct s_PackedStructuresEmployee packed_employees[MAX_employees];

	// Get size of the unpacked struct
	printf("%ld\n", sizeof(unpacked_employees[0]));
	printf("%ld\n", sizeof(struct s_UnpackedStructuresEmployee));

	// Get size of the unpacked struct
	printf("%ld\n", sizeof(packed_employees[0]));
	printf("%ld\n", sizeof(struct s_PackedStructuresEmployee));


	return 0;
}