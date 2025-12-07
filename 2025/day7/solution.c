#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

uint64_t solution1(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;
    
    uint64_t sum = 0;

    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    rewind(input);

    char *diagram = malloc(size);
    
    size_t read = fread(diagram, 1, size, input);

    int columns = 0;
    int S = 0;
    while (diagram[columns] != '\n') {
        if (diagram[columns] == 'S') {
            S = columns;
            diagram[S] = '|';
        }
        columns++;
    }

    columns++;
    int rows = read/columns;

    int b_s = S;
    int b_e = S;
    int splits = 0;
    for (int k = 1; k < rows; k++) {
        for (int j = b_s; j <= b_e; j++) {
            char m0 = diagram[(k-1)*columns + j];
            char m1 = diagram[k*columns + j];
            if (m0 == '|' && m1 == '^') {
                diagram[k*columns + j + 1] = '|';
                diagram[k*columns + j - 1] = '|';
                b_s = min(b_s, j - 1);
                b_e = max(b_e, j + 1);
                splits++;
            } else if (m0 == '|') {
                diagram[k*columns + j] = '|';
            }
        }
    }

	return splits;
}

uint64_t propegate(char *manifold, int x0, int y0, int width, int height, uint64_t *cache)
{
    if (x0 < 0 || x0 >= width) return 0;

    int index = y0 * width + x0;
    if (cache[index] != -1)
        return cache[index];

    for (int y = y0; y < height; y++)
    {
        char m = manifold[y*width + x0];

        if (m == '^') {
            uint64_t right = propegate(manifold, x0+1, y, width, height, cache);
            uint64_t left = propegate(manifold, x0-1, y, width, height, cache);
            uint64_t paths = right + left;
            cache[index] = paths;
            return paths;
        }
    }

    cache[index] = 1;
    return 1;
}

uint64_t solution2(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (!input)
		return -1;
    
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    rewind(input);

    char *diagram = malloc(size);
    
    size_t read = fread(diagram, 1, size, input);

    int columns = 0;
    int S = 0;
    while (diagram[columns] != '\n') {
        if (diagram[columns] == 'S') {
            S = columns;
        }
        columns++;
    }

    columns++;
    int rows = read/columns;

    uint64_t *cache = malloc(rows*columns*sizeof(uint64_t));
    memset(cache, -1, rows*columns*sizeof(uint64_t));
    return propegate(diagram, S, 1, columns, rows, cache);
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample"), 21);
	test("solution 1, input", solution1("input"), 1646);
	test("solution 2, sample", solution2("sample"), 40);
	test("solution 2, input", solution2("input"), 32451134474991);
}
