#ifndef TESTER_H
#define TESTER_H

#include <stdio.h>
#include <time.h>

static unsigned int tests = 0;
static unsigned int fails = 0;

#define results() {\
	if(fails == 0) {\
		printf("TESTS PASSED (%d/%d)\n", tests, tests);\
	} else {\
		printf("TESTS FAILED (%d/%d)\n", tests-fails, tests);\
	}\
}

#define ok(test) {\
	tests++;\
	if(!(test)){\
		fails++;\
		printf("\t%s:%d error \n", __FILE__, __LINE__);\
	}\
}

#define run(name, test){\
	const unsigned int num_test = tests;\
	const unsigned int num_fail = fails;\
	const clock_t start = clock();\
	printf("\t%s:\n", name);\
	test();\
	printf("\t\tpass: %d\tfail: %d\ttime: %ld us\n",\
		(tests-num_test)-(fails-num_fail),fails-num_fail,\
	        (long)((clock() - start) * 1000000 / CLOCKS_PER_SEC));\
}

#endif
