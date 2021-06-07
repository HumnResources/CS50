#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}


// Recursive functino to accomplish a simpler pyramid.
void draw(int h)
{
    // Having this here will cause in infinite recursive call.
    // This causes the stack to overflow. corrected by adding the if 0 base case.
    // Still has the issue of a segfault when # is too large. Due to the memory cost from recursion (function calls) on the stack.
    if (h == 0) return;

    draw(h - 1);

    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}