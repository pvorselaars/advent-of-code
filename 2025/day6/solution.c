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

uint64_t solution2(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;
    
    uint64_t sum = 0;

    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    rewind(input);

    char *buffer = malloc(size+1);
    
    size_t read = fread(buffer, 1, size, input);

    int columns = 0;
    while (buffer[columns] != '\n')
        columns++;

    columns++;
    int rows = read/columns;

    char *number = malloc(rows);
    number[rows-1] = 0;

    char current_op = ' ';
    uint64_t n = 0;
    for (int i = 0; i < columns - 1; i++) {
        int d = 0;
        for (int k = 0; k < rows - 1; k++) {
           char val = buffer[k * columns + i];
           if (val != ' ')
               number[d++] = val;
        }
        number[d] = 0;

        char op = buffer[(rows-1) * columns + i];
        
        if (op == '+' || op == '*') {
            current_op = op;
        } else if (*number == 0) {
            sum += n;
            n = 0;
            continue;
        }

        if (current_op == '+')
            n += strtoul(number, NULL, 10);

        if (current_op == '*') {
            if (n == 0) { 
                n = strtoul(number, NULL, 10);
            } else {
                n *= strtoul(number, NULL, 10);
            }
        }

    }
    sum += n;

	return sum;
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 4277556);
	test("solution 1, input", solution1("input"), 5346286649122);
	test("solution 2, sample", solution2("sample"), 3263827);
	test("solution 2, input", solution2("input"), 10389131401929);
}
