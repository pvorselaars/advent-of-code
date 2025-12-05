#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../tester.h"

int compare(const void* a, const void* b) {
    uint64_t u1 = *(uint64_t *)a, u2 = *(uint64_t *)b;

    if (u1 > u2) return 1;
    if (u1 < u2) return -1;
    return 0;
}

uint64_t solution1(const char* filename) {
	FILE *input = fopen(filename, "r");
    if (!input)
        return -1;
    
	char line[256];
    uint64_t lines = 0;
	while (fgets(line, 256, input))
        lines++;
    
    rewind(input);

    uint64_t *l1 = malloc(lines*sizeof(uint64_t));
    uint64_t *l2 = malloc(lines*sizeof(uint64_t));

    char *next;
	for (int l = 0; l < lines; l++) {
        fgets(line, 256, input);
        l1[l] = strtoull(line, &next, 10);
        l2[l] = strtoull(next, NULL, 10);
    }

    qsort(l1, lines, sizeof(uint64_t), compare);
    qsort(l2, lines, sizeof(uint64_t), compare);

    uint64_t sum = 0;
	for (int i = 0; i < lines; i++)
        sum += labs((int64_t)(l2[i] - l1[i]));

    return sum;
}

uint64_t solution2(const char* filename) {
	FILE *input = fopen(filename, "r");
    if (!input)
        return -1;
    
	char line[256];
    uint64_t lines = 0;
	while (fgets(line, 256, input))
        lines++;
    
    rewind(input);

    uint64_t *l1 = malloc(lines*sizeof(uint64_t));
    uint64_t *l2 = malloc(lines*sizeof(uint64_t));

    char *next;
	for (int l = 0; l < lines; l++) {
        fgets(line, 256, input);
        l1[l] = strtoull(line, &next, 10);
        l2[l] = strtoull(next, NULL, 10);
    }

    qsort(l1, lines, sizeof(uint64_t), compare);
    qsort(l2, lines, sizeof(uint64_t), compare);

    uint64_t sum = 0;
	for (int i = 0; i < lines; i++) {
        uint64_t c = 0;
        for (int j = 0; j < lines; j++) {
            if (l1[i] == l2[j])
                c++;
        }

        sum += l1[i]*c;
    }

    return sum;
}


int main(int argc, char *argv[])
{
    test("solution 1, sample", solution1("sample"), 11);
    test("solution 1, input", solution1("input"), 3714264);
    test("solution 2, sample", solution2("sample"), 31);
    test("solution 2, input", solution2("input"), 18805872);
}
