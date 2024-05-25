#include <stdio.h>

#define MAX_PERSONS 12

#define DEBUG

int g_num_persons = 0;

void first_funtion(){
	int i_personID = 0;

	{
		// This is a different scope than outside 
		// 		the curly brackets
		int i_personID = 4;
		printf("%d\n", i_personID);
	}
	printf("%d\n", i_personID);
}

int add_person(){
	if (g_num_persons < MAX_PERSONS) {
		g_num_persons += 1;
		return 0;
	} else {
		return -1;
	}
}

int main() {
	int i_personID = 0;
	int i_personID_2 = i_personID + 1;
	first_funtion();

	// Can tell if DEBUG was defined above
	#ifdef DEBUG
	printf("Currently in debug mode: %s:%d\n", __FILE__, __LINE__);
	#endif

	// test if add_person ran correctly
	int i_error_code = add_person();
	return 0;
}