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

    while((n = getline(&buf, &len, input)) != -1)
    {
        rot = atoi(&buf[1]);

        if(buf[0] == 'L')
        {
            dial -= rot;
        }

        if(buf[0] == 'R')
        {
            dial += rot;
        }

        count += dial / 100;

        dial %= 100;

        if (dial == 0)
        {
            count++;
        }
    }
    printf("count: %d\n", count);
}
