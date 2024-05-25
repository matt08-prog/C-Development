#include <stdio.h>
#include <string.h>

#define NUM_DAYS 7
#define LENGTH_OF_STRINGS

// Array of Strings
char *a_strings_of_the_day [NUM_DAYS] = {"test", "test1"};

// Return the string cooresponding to today's date
char *func_string_of_the_day(int i_date){
	return a_strings_of_the_day[i_date];
}

int main(int argc, char *argv[]) {

	// print today's string of the day
	int current_day = 1;
	char *s_todays_string = func_string_of_the_day(current_day);
	printf("%s\n", s_todays_string);
	
	return 0;
}