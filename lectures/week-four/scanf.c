#include <stdio.h>

int main(void)
{
    // int x;
    // printf("x: ");

    // Uses pointers in the function.
    // Scan int (%i), store at variable x (&x)
    // But scanf() has no type checking.

    // scanf("%i", &x);
    // printf("x: %i\n", x);


    // Here, *s needs to be allocated memory to store the string from the user.
    // char *s;

    // So we call malloc() but we MUST include free() call.
    // malloc(4);
    // We can also use standard array initialization for convenience

    char s[4];

    printf("s: ");

    scanf("%s", s);

    printf("%s\n", s);
}