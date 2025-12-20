#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

typedef struct {
	char label[4];
} device;

int find_reactor(bool *connections, uint32_t n, uint32_t start, uint32_t end)
{

	int routes = 0;
	for (int j = 0; j < n; j++) {
		if (connections[start * n + j]) {
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
			connection[c + 3] = 0;

			uint32_t dest = 0;
			for (int d = 0; d < rows; d++) {
				if (strcmp(connection + c, devices[d].label) == 0) {
					dest = d;
					break;
				}
			}

			connections[i * rows + dest] = true;
		}
	}

	return find_reactor(connections, rows, you, out);
}

uint64_t solution2(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;

	char *line = NULL;
	size_t length = 0;
	ssize_t bytes;

	uint32_t rows = 0;
	while ((bytes = getline(&line, &length, input)) > 0)
		rows++;

	rewind(input);

	rows++;
	device *devices = malloc(rows * sizeof(device));

	devices[rows - 1].label[0] = 'o';
	devices[rows - 1].label[1] = 'u';
	devices[rows - 1].label[2] = 't';
	devices[rows - 1].label[3] = '\0';

	uint32_t svr = 0;
	uint32_t out = rows - 1;
	uint32_t dac = 0;
	uint32_t fft = 0;

	for (uint32_t i = 0; i < rows - 1; i++) {
		getline(&line, &length, input);
		for (int c = 0; c < 3; c++)
			devices[i].label[c] = line[c];

		devices[i].label[3] = 0;

		if (strcmp("svr", devices[i].label) == 0)
			svr = i;

		if (strcmp("out", devices[i].label) == 0)
			out = i;

		if (strcmp("dac", devices[i].label) == 0)
			dac = i;

		if (strcmp("fft", devices[i].label) == 0)
			fft = i;
	}

	rewind(input);

	bool *connections = calloc(rows * rows, sizeof(bool));

	for (int i = 0; i < rows - 1; i++) {
		getline(&line, &length, input);
		char *connection = line + 5;

		for (int c = 0; connection[c] != '\n' && connection[c] != 0; c += 4) {
			connection[c + 3] = 0;

			uint32_t dest = 0;
			for (int d = 0; d < rows; d++) {
				if (strcmp(connection + c, devices[d].label) == 0) {
					dest = d;
					break;
				}
			}

			connections[i * rows + dest] = true;
		}
	}

	uint64_t ***dp = malloc(rows * sizeof(uint64_t **));
	for (int i = 0; i < rows; i++) {
		dp[i] = malloc(2 * sizeof(uint64_t *));
		for (int j = 0; j < 2; j++) {
			dp[i][j] = calloc(2, sizeof(uint64_t));
		}
	}

	dp[out][1][1] = 1;

	bool changed = true;
	while (changed) {
		changed = false;

		for (int node = 0; node < rows; node++) {
			if (node == out)
				continue;

			for (int dac_flag = 0; dac_flag <= 1; dac_flag++) {
				for (int fft_flag = 0; fft_flag <= 1; fft_flag++) {
					uint64_t old_value = dp[node][dac_flag][fft_flag];
					uint64_t new_value = 0;

					bool cur_dac = dac_flag || (node == dac);
					bool cur_fft = fft_flag || (node == fft);

					for (int j = 0; j < rows; j++) {
						if (connections[node * rows + j]) {
							new_value += dp[j][cur_dac][cur_fft];
						}
					}

					if (new_value != old_value) {
						dp[node][dac_flag][fft_flag] = new_value;
						changed = true;
					}
				}
			}
		}
	}

	return dp[svr][0][0];
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 5);
	test("solution 1, input", solution1("input"), 674);
	test("solution 2, sample2", solution2("sample2"), 2);
	test("solution 2, input", solution2("input"), 438314708837664);
}
