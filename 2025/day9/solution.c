#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

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

		for (int j = i + i; j < rows; j++) {

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

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool intersect(point pu, point pv, point *points, int n)
{

	for (int i = 0; i < n; i++) {

		point pi = points[i];
		point pj = points[(i + 1) % n];
		uint64_t edge_min_x = MIN(pi.x, pj.x);
		uint64_t edge_max_x = MAX(pi.x, pj.x);
		uint64_t edge_min_y = MIN(pi.y, pj.y);
		uint64_t edge_max_y = MAX(pi.y, pj.y);
		uint64_t min_x = MIN(pu.x, pv.x);
		uint64_t max_x = MAX(pu.x, pv.x);
		uint64_t min_y = MIN(pu.y, pv.y);
		uint64_t max_y = MAX(pu.y, pv.y);

		if (min_x < edge_max_x && max_x > edge_min_x &&
				min_y < edge_max_y && max_y > edge_min_y)
			return true;

	}

	return false;
}

uint64_t solution2(const char *filename)
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

		for (int j = i + 1; j < rows; j++) {

			point pj = points[j];

			uint64_t dx = labs(pi.x - pj.x) + 1;
			uint64_t dy = labs(pi.y - pj.y) + 1;

			uint64_t size = dx * dy;

			if (size > max) {
				if (!intersect(pi, pj, points, rows)) {
					max = size;
				}
			}
		}
	}

	return max;
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 50);
	test("solution 1, input", solution1("input"), 4781546175);
	test("solution 2, sample", solution2("sample"), 24);
	test("solution 2, input", solution2("input"), 1573359081);
}
