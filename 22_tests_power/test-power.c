#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);
void run_check (unsigned x, unsigned y, unsigned expected_ans) {
	if (power(x, y) != expected_ans) {
		printf("Test failed.\n");
		exit(EXIT_FAILURE);
		}
	else {
		return;
		}
	}

int main(void){
	run_check (2, 0, 1);
	run_check (1, 2, 1);
	run_check (-2, 0, 1);
//	run_check (1.1, 2, 1.21);
	run_check (0, 0, 1);
	run_check (0, 1, 0);
	run_check (-2, 1, -2);
	run_check (-2, -1, -0.5);
//	run_check (4, 0.5, 2);
//	run_check (4, -0.5, 0.5);
	run_check (2, -1, 0.5);	
	run_check (-1, 2, 1);
//	run_check (-1, 1, -1);
	run_check (-1, -1, -1);
	return EXIT_SUCCESS;
	}
