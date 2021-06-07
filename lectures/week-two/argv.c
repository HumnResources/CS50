#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Take int as input (argument count) and
// arr of strings (argument vector) from command line etc.
int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // printf("Hello, %s!", argv[1]);
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            printf("%c", argv[1][i]);
        }

        // Both above do the same thing,
        // Strings are just arrays of chars
    }
    else
    {
        printf("Hello, world!");
    }

    printf("\n");
}