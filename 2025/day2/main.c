#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int digits(unsigned long number)
{
    if (number == 0) return 1;
    return (long)log10(number) +1;
}

int main(int argc, char *argv[])
{
    FILE *input = fopen("input", "r");

    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    unsigned long sum = 0;

    while ((n = getdelim(&buf, &len, ',', input)) != -1)
    {
        char *start = strtok(buf, "-");
        char *end = strtok(NULL, ",");

        for (unsigned long i = atol(start); i <= atol(end); i++)
        {
            int d = digits(i);

            for (int k = 2; k <= d; k++) 
            {
                int m = d / k;
                int r = (pow(10, m * k) - 1) / (pow(10, m) - 1);

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
