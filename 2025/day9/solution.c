#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

uint64_t y_min = UINT64_MAX;
uint64_t x_min = UINT64_MAX;
uint64_t y_max = 0;
uint64_t x_max = 0;

typedef struct {
	uint64_t x, y;
} point;

uint64_t solution1(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;

	char *line;
	size_t length = 0;
	ssize_t bytes;

	uint32_t rows = 0;
	while ((bytes = getline(&line, &length, input)) > 0)
		rows++;

	rewind(input);

	point *points = malloc(rows * sizeof(point));

	for (int r = 0; r < rows; r++) {
		getline(&line, &length, input);
		sscanf(line, "%lu,%lu", &points[r].x, &points[r].y);
	}

	uint64_t max = 0;
	for (int i = 0; i < rows; i++) {
		point pi = points[i];

		for (int j = 0; j < rows; j++) {

			point pj = points[j];

			uint64_t dx = labs(pi.x - pj.x) + 1;
			uint64_t dy = labs(pi.y - pj.y) + 1;

			uint64_t size = dx * dy;
			//printf("%ld,%ld - %ld,%ld, %ld*%ld = %ld\n", pi.x, pi.y, pj.x, pj.y, dx, dy, size);

			max = size > max ? size : max;
		}
	}

	return max;
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 50);
	test("solution 1, input", solution1("input"), 4781546175);
	//test("solution 2, sample", solution2("sample"), 24);
	//test("solution 2, input", solution2("input"), 24);
}
