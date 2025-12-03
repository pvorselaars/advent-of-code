#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../../tester.h"

uint64_t drain(char *batteries, int number)
{
    int n = strlen(batteries);
    int r = n - number - 1;
    char *stack = (char*)calloc(number + 1, sizeof(char));
    int stack_top = 0;

    for (int i = 0; i < n; ++i)
    {
        while (stack_top > 0 && r > 0 && stack[stack_top - 1] < batteries[i])
        {
            stack_top--;
            r--;
        }
        if (stack_top < number) {
            stack[stack_top++] = batteries[i];
        } else {
            r--;
        }
    }

    stack[stack_top] = 0;
    uint64_t joltage = strtoull(stack, NULL, 10);
    free(stack);
    return joltage;
}

uint64_t solution(FILE *input, int number)
{
    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    uint64_t sum = 0;

    while ((n = getline(&buf, &len, input)) != -1)
    {
        uint64_t j = drain(buf, number);
        sum += j;
    }
    return sum;
}

int main(int argc, char *argv[])
{
    FILE *input = fopen("input", "r");
    uint64_t sum = solution(input, 12);
    ok(sum == 173229689350551);
}
