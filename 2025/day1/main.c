#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *input = fopen("input", "r");

    char *buf = NULL;
    size_t len = 0;
    ssize_t n;

    int dial = 50;
    int rot = 0;
    int count = 0;

    while ((n = getline(&buf, &len, input)) != -1)
    {
        int prev = dial;
        rot = atoi(&buf[1]);
        printf("dial: %d ", dial);
        printf("rotate: %d ", rot);

        count += rot / 100;
        rot %= 100;

        if (buf[0] == 'L')
        {
            printf("L ");
            dial -= rot;
        }

        if (buf[0] == 'R')
        {
            printf("R ");
            dial += rot;
        }

        if (prev != 0 && dial < 0 || dial >= 101 )
            count++;

        dial = ((dial % 100) + 100) % 100;

        if (dial == 0)
            count++;

        printf("dial: %d\n", dial);
    }

    printf("count: %d\n", count);
}
