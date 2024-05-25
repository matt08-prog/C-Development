#include <stdio.h>

int main() {

	// same size different format
	unsigned int x = 1 << 31;
	int sx = (int)x;
	printf("\nmax unsigned int: %u\n", x);
	printf("min signed int: %d\n\n", sx);

	// down casting to a short
	unsigned int bigx = 0xfffffefe;
	short kindabig = (short)bigx;
	printf("unsigned int 0xfffffefe: %u\n", bigx);
	printf("short 0xfffffefe: %hu\n\n", kindabig);

	// upcasting, with sign extension
	short short2 = -1;
	// since they are both signed, used_to_be_short
	//	will use sign extension, it will also become all 1s
	int used_to_be_short = (int)short2;
	printf("all 1s in signed short: %hi\n", short2);
	printf("all 1s in signed int: %d\n\n", used_to_be_short);


	// rounding to integer
	float f = 3.14;
	int _used_to_be_float = (int)f;
	printf("float 3.14: %f\n", f);
	printf("signed int 3.14: %d\n\n", _used_to_be_float);


	return 0;
}