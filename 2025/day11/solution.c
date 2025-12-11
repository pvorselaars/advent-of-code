#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

typedef struct {
	char label[4];
} device;

int find_reactor(bool *connections, uint32_t n, uint32_t start, uint32_t end) {

		int routes = 0;
		for (int j = 0; j < n; j++) {
			if(connections[start * n + j]) {
				if (j == end) {
					routes++;
				} else {
					routes += find_reactor(connections, n, j, end);
				}
			}
		}

		return routes;
}

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

	device *devices = malloc(rows * sizeof(device));

	uint32_t you = 0;
	uint32_t out = 0;
	for (uint32_t i = 0; i < rows; i++) {
		getline(&line, &length, input);
		for (int c = 0; c < 3; c++)
			devices[i].label[c] = line[c];

		devices[i].label[4] = 0;

		if (strcmp("you", devices[i].label) == 0)
			you = i;

		if (strcmp("out", devices[i].label) == 0)
			out = i;
	}

	rewind(input);

	bool *connections = malloc(rows * rows * sizeof(bool));

	for (int i = 0; i < rows; i++) {
		getline(&line, &length, input);
		char *connection = line + 5;

		for (int c = 0; connection[c] != '\n' && connection[c] != 0; c += 4) {
			connection[c+3] = 0;

			uint32_t dest = 0;
			for (int d = 0; d < rows; d++) {
				if (strcmp(connection+c, devices[d].label) == 0) {
					dest = d;
					break;
				}
			}

			connections[i * rows + dest] = true;
		}
	}

	return find_reactor(connections, rows, you, out);
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 5);
	test("solution 1, input", solution1("input"), 674);
}
