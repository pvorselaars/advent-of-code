#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

uint64_t solution1(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;

	uint32_t areas = 0;
	char *line;
	size_t length = 0;
	ssize_t bytes;

	uint32_t rows = 0;
	while ((bytes = getline(&line, &length, input)) > 0 && rows != 29)
		rows++;

	while ((bytes = getline(&line, &length, input)) > 0) {

		int i = 0;
		char *next = line;
		uint32_t x = strtoul(next, &next, 10);
		uint32_t y = strtoul(next+1, &next, 10);

		uint32_t area = x*y;

		uint32_t c = 0;
		next++;
		next++;

		uint32_t sum = 0;
		while(*next != '\n')
			sum += strtoul(next, &next, 10);

		if (area >= 9*sum)
			areas++;

	}

	return areas;
}

int main(int argc, char *argv[])
{
	test("solution 1, input", solution1("input"), 497);
}
