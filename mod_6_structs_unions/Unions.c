#include <stdio.h>
#include <stdbool.h>

#define MAX_IDS 32
#define MAX_employees 1000

union u_MyUnion {
	int x;
	char c;
	short s;
};

int main() {
	union u_MyUnion u;
	u.x = 0x41424344;

	printf("%hx %hhx\n", u.s, u.c);
	return 0;
}