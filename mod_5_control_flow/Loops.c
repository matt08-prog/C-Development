#include <stdio.h>
#include <string.h>

#define MAX_TEMP 40
#define MIN_TEMP 20

int main() {
	for (int i = 0; i < 5; ++i)
	{
		printf("%d: %d\n", i, i-1);
	}
	return 0;
}