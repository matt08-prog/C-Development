#include <stdio.h>
#include <string.h>

#define MAX_TEMP 40
#define MIN_TEMP 20


int main() {
	int temp;
	printf("What temp?: ");
	scanf("%d", &temp);

	int temp_code = 0;
	if (temp > MAX_TEMP || temp < MIN_TEMP){
		temp_code = 1;
	} else {
		temp_code = 0;
	}

	// temp should be between 21 and 39 inclusive
	temp_code == 0 ? printf("good temp\n") : printf("bad temp\n");

	return 0;
}