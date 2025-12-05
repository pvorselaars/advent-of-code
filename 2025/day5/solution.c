#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../../tester.h"

#define min(a,b) (((a) < (b)) ? (a) : (b));
#define max(a,b) (((a) > (b)) ? (a) : (b));

void solution1()
{
    FILE *input = fopen("input", "r");
    char *buf = NULL;
    size_t len = 0;
    ssize_t n;
    uint64_t ranges = 0;
    uint64_t sum = 0;

    while ((n = getline(&buf, &len, input)) != -1 && *buf != '\n')
        ranges++;

    rewind(input);

    uint64_t *fresh_ingredients = malloc(ranges*2*sizeof(uint64_t));

    for (int r = 0; r < ranges; r++)
    {
        getline(&buf, &len, input);
        fresh_ingredients[2*r] = strtoull(strtok(buf, "-"), NULL, 10);
        fresh_ingredients[2*r+1] = strtoull(strtok(NULL, "-"), NULL, 10);
    }

    getline(&buf, &len, input);
    while ((n = getline(&buf, &len, input)) != -1)
    {
        uint64_t product_id = strtoull(buf, NULL, 10);

        for (int r = 0; r < ranges; r++)
        {
            if (fresh_ingredients[2*r] <= product_id && product_id <= fresh_ingredients[2*r+1]){
                sum++;
                break;
            }
        }
    }
    ok(sum == 888);
}

void solution2()
{
    FILE *input = fopen("input", "r");
    char *buf = NULL;
    size_t len = 0;
    ssize_t n;
    uint64_t ranges = 0;
    uint64_t sum = 0;

    while ((n = getline(&buf, &len, input)) != -1 && *buf != '\n')
        ranges++;

    rewind(input);

    uint64_t *fresh_ingredients = calloc(ranges*2, sizeof(uint64_t));

    while ((n = getline(&buf, &len, input)) != -1 && *buf != '\n')
    {
        uint64_t r1_start = strtoull(strtok(buf, "-"), NULL, 10);
        uint64_t r1_end = strtoull(strtok(NULL, "-"), NULL, 10);
        bool overlap = false;

        for (int r = 0; r < ranges; r++)
        {
            uint64_t r2_start = fresh_ingredients[2*r];
            uint64_t r2_end = fresh_ingredients[2*r+1];

            if (r2_start == 0 && r2_end == 0)
                break;

            if (!(r1_end < r2_start || r1_start > r2_end))
            {
                overlap = true;
                fresh_ingredients[2*r] = min(r1_start, r2_start);
                fresh_ingredients[2*r+1] = max(r1_end, r2_end);
                break;
            }
        }

        if (!overlap)
        {
            for (int r = 0; r < ranges; r++)
            {
                if (fresh_ingredients[2*r] == 0 && fresh_ingredients[2*r+1] == 0) {
                    fresh_ingredients[2*r] = r1_start;
                    fresh_ingredients[2*r+1] = r1_end;
                    break;
                }
            }
        }
        
        bool merged = true;
        while (merged) {
            merged = false;
            for (int i = 0; i < ranges; i++)
                for (int j = 0; j < ranges; j++) {

                    if (i == j) continue;
                    if (fresh_ingredients[2*j] == 0 && fresh_ingredients[2*j+1] == 0) continue;

                    uint64_t s1 = fresh_ingredients[2*i];
                    uint64_t e1 = fresh_ingredients[2*i+1];
                    uint64_t s2 = fresh_ingredients[2*j];
                    uint64_t e2 = fresh_ingredients[2*j+1];

                    if (!(e1 < s2 || s1 > e2)) {
                        fresh_ingredients[2*i] = s1 < s2 ? s1 : s2;
                        fresh_ingredients[2*i+1] = e1 > e2 ? e1 : e2;
                        fresh_ingredients[2*j] = 0;
                        fresh_ingredients[2*j+1] = 0;
                        merged = true;
                    }
                }
        }
    }

    for (int r = 0; r < ranges; r++) {
        uint64_t s = fresh_ingredients[2*r];
        uint64_t e = fresh_ingredients[2*r+1];
        if (s == 0 && e == 0) continue;
        sum += e - s + 1;
    }

    ok(sum == 344378119285354);
}

int main(int argc, char *argv[])
{
    //run("solution 1", solution1);
    //run("solution 2", solution2);
    //results();
    solution2();
}
