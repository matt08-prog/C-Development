#include <stdio.h>

#define MAX_IDS 12

int main(){
	int a_userIDs[MAX_IDS] = {0, 1, 2};

	// 170 in decimal
	a_userIDs[MAX_IDS - 1] = 0xaa;

	for (int i = 0; i < MAX_IDS; ++i)
	{
		printf("%d\n", a_userIDs[i]);
	}
	


	return 0;
}