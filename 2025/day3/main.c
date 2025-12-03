#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "../../tester.h"

char *largest(char *batteries)
{
    char *battery = batteries;

    while (*batteries++)
    {
        if (*batteries > *battery)
            battery = batteries;
    }

    return battery;
}

int drain(char *batteries, int number)
{
    char *b1 = largest(batteries);
    int j1 = *b1 - 48;
    *b1 = 0;

    char *b2 = largest(batteries);
    int j2 = *b2 - 48;

    char *b3 = largest(b1+1);
    int j3 = *b3 - 48;

    int option1 = j2 * 10 + j1;
    int option2 = j1 * 10 + j3;

    return option1 > option2 ? option1 : option2;
}

int solution(FILE *input, int number)
{
    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    int sum = 0;

    while ((n = getline(&buf, &len, input)) != -1)
    {
        int j = drain(buf, number);
        sum += j;
    }
    return sum;
}

void test1()
{
    FILE *input = fopen("sample1", "r");
    int sum = solution(input, 2);
    ok(sum == 357);
    fclose(input);

    input = fopen("input", "r");
    sum = solution(input, 2);
    ok(sum == 17445);
    fclose(input);
}

int main(int argc, char *argv[])
{
    run("solution 1", test1);
    results();
}
