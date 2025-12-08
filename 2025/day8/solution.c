#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

typedef struct {
	uint64_t x, y, z;
} point;

typedef struct {
	uint64_t u, v, d;
} distance;

int compare_distance(const void *a, const void *b)
{
	distance *d1 = (distance *) a, *d2 = (distance *) b;

	if (d1->d > d2->d)
		return 1;
	if (d1->d < d2->d)
		return -1;
	return 0;
}

int compare_int(const void *a, const void *b)
{
	uint64_t u1 = *(uint64_t *) a, u2 = *(uint64_t *) b;

	if (u1 > u2)
		return -1;
	if (u1 < u2)
		return 1;
	return 0;
}

uint64_t find_parent(uint64_t parent[], uint64_t node)
{
	if (parent[node] == node)
		return parent[node];

	return parent[node] = find_parent(parent, parent[node]);
}

void union_set(uint64_t u, uint64_t v, uint64_t parent[], uint64_t rank[], uint64_t size[])
{
	u = find_parent(parent, u);
	v = find_parent(parent, v);

	if (rank[u] < rank[v]) {
		parent[u] = v;
		size[v] += size[u];
	} else if (rank[u] > rank[v]) {
		parent[v] = u;
		size[u] += size[v];
	} else {
		parent[v] = u;
		size[u] += size[v];
		rank[u]++;
	}
}

uint64_t solution1(const char *filename, int c)
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
	uint64_t pairs = rows * (rows - 1) / 2;
	distance *distances = malloc(pairs * sizeof(distance));
	memset(distances, 0, pairs * sizeof(distance));

	for (int r = 0; r < rows; r++) {
		getline(&line, &length, input);
		sscanf(line, "%lu,%lu,%lu", &points[r].x, &points[r].y, &points[r].z);
	}

	uint64_t p = 0;
	for (int i = 0; i < rows; i++) {
		point pi = points[i];

		for (int j = i + 1; j < rows; j++) {

			point pj = points[j];

			int64_t dx = pi.x - pj.x;
			int64_t dy = pi.y - pj.y;
			int64_t dz = pi.z - pj.z;

			uint64_t d = dx * dx + dy * dy + dz * dz;

			distances[p].u = i;
			distances[p].v = j;
			distances[p].d = d;
			p++;
		}
	}

	qsort(distances, pairs, sizeof(distance), compare_distance);

	uint64_t *parent = malloc(rows * sizeof(uint64_t));
	uint64_t *rank = malloc(rows * sizeof(uint64_t));
	uint64_t *size = malloc(rows * sizeof(uint64_t));

	for (int i = 0; i < rows; i++) {
		parent[i] = i;
		rank[i] = 0;
		size[i] = 1;
	}

	for (int i = 0; i < pairs && i < c; i++) {
		uint64_t u = distances[i].u;
		uint64_t v = distances[i].v;
		if (find_parent(parent, u) != find_parent(parent, v)) {
			union_set(u, v, parent, rank, size);
		}
	}

	uint64_t count = 0;
	uint64_t sizes[rows];
	for (int i = 0; i < rows; i++) {
		if (parent[i] == i)
			sizes[count++] = size[i];
	}

	qsort(sizes, count, sizeof(uint64_t), compare_int);

	return sizes[0] * sizes[1] * sizes[2];
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
	uint64_t pairs = rows * (rows - 1) / 2;
	distance *distances = malloc(pairs * sizeof(distance));
	memset(distances, 0, pairs * sizeof(distance));

	for (int r = 0; r < rows; r++) {
		getline(&line, &length, input);
		sscanf(line, "%lu,%lu,%lu", &points[r].x, &points[r].y, &points[r].z);
	}

	uint64_t p = 0;
	for (int i = 0; i < rows; i++) {
		point pi = points[i];

		for (int j = i + 1; j < rows; j++) {

			point pj = points[j];

			int64_t dx = pi.x - pj.x;
			int64_t dy = pi.y - pj.y;
			int64_t dz = pi.z - pj.z;

			uint64_t d = dx * dx + dy * dy + dz * dz;

			distances[p].u = i;
			distances[p].v = j;
			distances[p].d = d;
			p++;
		}
	}

	qsort(distances, pairs, sizeof(distance), compare_distance);

	uint64_t *parent = malloc(rows * sizeof(uint64_t));
	uint64_t *rank = malloc(rows * sizeof(uint64_t));
	uint64_t *size = malloc(rows * sizeof(uint64_t));

	for (int i = 0; i < rows; i++) {
		parent[i] = i;
		rank[i] = 0;
		size[i] = 1;
	}

	uint64_t circuits = rows;
	uint64_t result;

	for (int i = 0; i < pairs; i++) {
		uint64_t u = distances[i].u;
		uint64_t v = distances[i].v;
		if (find_parent(parent, u) != find_parent(parent, v)) {
			union_set(u, v, parent, rank, size);
			circuits--;

			if (circuits == 1) {
				return points[u].x * points[v].x;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	test("solution 1, sample", solution1("sample", 10), 40);
	test("solution 1, input", solution1("input", 1000), 69192);
	test("solution 2, sample", solution2("sample"), 25272);
	test("solution 2, input", solution2("input"), 7264308110);
}
