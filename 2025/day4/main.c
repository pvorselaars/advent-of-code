#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

int accessible(char *grid, uint64_t size, uint32_t x, uint32_t y)
{
    if (grid[y*size+x] != '@')
	    return 0;

    uint32_t c = 0;

    for (int i = -1; i <= 1; i++)
    {
    	for (int j = -1; j <= 1; j++)
        {
            if (x + i < 0 || x + i >= size || y + j < 0 || y + j >= size || (i == 0 && j == 0))
                continue;

            if(grid[(y+j)*size+(x+i)] == '@')
                c++;

        }
    }

    return c < 4 ? 1 : 0;
}

int accessible_rolls(char *grid, uint64_t width)
{
    uint64_t a = 0;

    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < width; x++)
        {
            a += accessible(grid, width, x, y);
        }
    }

    return a;
}

int remove_rolls(char *grid, uint64_t width, uint64_t *answer)
{
    uint64_t removed = 0;

    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if(accessible(grid, width, x, y))
            {
                grid[y*width+x] = '.';
                removed++;
            }
        }
    }

    *answer += removed;
    return removed;
}

uint64_t solution1(FILE *input)
{
    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    uint64_t width = getline(&buf, &len, input) - 1;
    uint64_t size = width*width;

    buf = malloc(size);
    char *grid = buf;
    rewind(input);

    while ((n = getline(&buf, &len, input)) != -1)
	    buf += n - 1;

    uint64_t answer = accessible_rolls(grid, width);

    free(grid);
    return answer;
}


uint64_t solution2(FILE *input)
{
    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    uint64_t width = getline(&buf, &len, input) - 1;
    uint64_t size = width*width;

    buf = malloc(size);
    char *grid = buf;
    rewind(input);

    while ((n = getline(&buf, &len, input)) != -1)
	    buf += n - 1;

    uint64_t answer = 0;
    while(remove_rolls(grid, width, &answer));

    free(grid);
    return answer;
}


void test1(){
    FILE *input = fopen("sample1", "r");
    uint64_t sum = solution1(input);
    ok(sum == 4);
}

void test2(){
    FILE *input = fopen("sample2", "r");
    uint64_t sum = solution1(input);
    ok(sum == 13);
}

void test3(){
    FILE *input = fopen("input", "r");
    uint64_t sum = solution1(input);
    ok(sum == 1626);
}

void test4(){
    FILE *input = fopen("input", "r");
    uint64_t sum = solution2(input);
    ok(sum == 9173);
}

int main(int argc, char *argv[])
{
    run("test 1", test1);
    run("test 2", test2);
    run("test 3", test3);
    run("test 4", test4);
    results();
}
