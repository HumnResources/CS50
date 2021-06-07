#include <stdio.h>
#include <cs50.h>

// Prototype - Used to give inference to the compiler for functions declared after main.
void meow(void);

int main(void)
{
    for(int i = 0; i < 3; i++)
    {
        meow();
    }
}

void meow(void)
{
    printf("Meow\n");
}
void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Meow\n");
    }
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Positive Integer: ");
    }
    while(n < 1);

    return n;
}