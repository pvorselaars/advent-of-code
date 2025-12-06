#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../tester.h"

uint64_t solution1(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;

	char *line;
    size_t length = 0;
    ssize_t bytes;
	uint64_t sum = 0;
	char *next, *prev;
	uint32_t number;

    getline(&line, &length, input);

	uint32_t columns = 0;
    next = line;
	while (*next != '\0' && *next != '\n') {
        columns++;
        while (*next != ' ' && *next != '\0' && *next != '\n') next++;
        while (*next == ' ') next++;
    }

	uint32_t rows = 0;
    while((bytes = getline(&line, &length, input)) > 0)
        rows++;

	uint32_t *matrix = malloc(rows * columns * sizeof(uint32_t));

    rewind(input);

    for (uint32_t j = 0; j < rows; j++) {
        getline(&line, &length, input);
        next = line;
        for (uint32_t i = 0; i < columns; i++) {
            matrix[j * columns + i] = strtoul(next, &next, 10);
        }
    }

    getline(&line, &length, input);
    next = line;
    for (uint32_t i = 0; i < columns; i++) {
        while (*next == ' ') next++;
		if (*next == '+') {
			uint64_t partial_sum = 0;
			for (int k = 0; k < rows; k++)
				partial_sum += matrix[k * columns + i];

			sum += partial_sum;
		} else if (*next == '*') {
			uint64_t product = 1;
			for (int k = 0; k < rows; k++)
				product *= matrix[k * columns + i];

			sum += product;
		}

		next++;
	}

	return sum;
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 4277556);
	test("solution 1, input", solution1("input"), 5346286649122);
}
