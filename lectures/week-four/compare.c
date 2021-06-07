#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    // if (s == t) is incorrect because the comparator is comparing the address', instead of the address' value.
    // Use strcmp() instead.
    // Comparator functions in c return 0 if equal, 1 if the second value is greater than first, -1 if second value is less than first.
    if (strcmp(s, t) == 0)
        printf("Same\n");
    else
        printf("Different\n");


}