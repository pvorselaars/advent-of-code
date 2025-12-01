#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *input = fopen("input", "r");

    char buf[256];

    int dial = 50;
    int rot = 0;
    int count = 0;
    int wraps = 0;

    while (fgets(buf, 256, input) != NULL)
    {
        int prev = dial;
        rot = atoi(&buf[1]);

        wraps += rot / 100;
        rot %= 100;

        dial += buf[0] == 'L' ? -rot : rot;

        if (prev != 0 && dial < 0 || dial >= 101 )
            wraps++;

        dial = ((dial % 100) + 100) % 100;

        if (dial == 0)
            count++;
    }

    printf("password 1: %d\npassword 2: %d\n", count, count + wraps);
}
