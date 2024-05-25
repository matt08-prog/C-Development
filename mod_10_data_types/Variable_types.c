#include <stdio.h>

int main() {

	// int size can vary based on system
	int i_x; // 4 bytes (32 bits)
	char c_y; // 1 byte (8 bits);
	short s_z; // 2 bytes (16 bits)
	long long int l_a; // 8 bytes (64 bits)

	// signed int by default
	int s_x = -4;
	// shouldn't put a negative value in an unsigned int
	unsigned int us_x = -4;

	float f_b = 123.4567; // 7 decimal places
	double d_c = 1234567.89012345; // 15 decimal places


	printf("%.4f\n", f_b);
	// decimal precision needs to be specified or else 6 points will be assumed
	printf("%7.8f\n", d_c);

	return 0;
}