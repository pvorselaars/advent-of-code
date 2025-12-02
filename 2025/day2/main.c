#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DIGITS 20


unsigned long int_pow10(int exp)
{
    unsigned long result = 1;
    while (exp--)
        result *= 10;

    return result;
}

int digits(unsigned long x)
{
    int d = 1;
    while (x >= 10)
    {
        x /= 10;
        d++;
    }
    return d;
}

unsigned long r_table[MAX_DIGITS][MAX_DIGITS];

void precompute_r()
{
    for (int d = 1; d <= MAX_DIGITS; d++)
    {
        for (int k = 2; k <= d; k++)
        {
            int m = d / k;
            if (m == 0) continue;
            r_table[d][k] = (int_pow10(m * k) - 1) / (int_pow10(m) - 1);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *input = fopen("input", "r");

    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    unsigned long sum = 0;
    precompute_r();

    while ((n = getdelim(&buf, &len, ',', input)) != -1)
    {
        unsigned long start = atol(strtok(buf, "-"));
        unsigned long end = atol(strtok(NULL, ","));

        for (unsigned long i = start; i <= end; i++)
        {
            int d = digits(i);

            for (int k = 2; k <= d; k++) 
            {
                int m = d / k;
                int r = r_table[d][k];

                if (i % r == 0 && digits(i/r) == m)
                {
                    sum += i;
                    break;
                }
            }
        }
    }

    printf("answer: %lu\n", sum);
}
