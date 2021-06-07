#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");

    // char *t = s; copies the address of s into *t. Which makes both pointers point to the same memory location.

    // malloc provides additional memory to the variable. With an argument of number of bytes.
    // Return the address it provides.
    // We add 1 to add a null character.
    char *t = malloc(strlen(s) + 1);

    // NULL is a pointer with no address, malloc() couldn't provide an address.
    if (t == NULL)
    {
        return 1;
    }

    // Inclusive - includes the null char.
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
        // *(s+i) = *(s+i) Alternative
    }


    // Does the same as the aboce, copies into a new pointer.
    // Inclusive of the terminating char
    char *s_2 = malloc(strlen(s) + 1);
    strcpy(s_2, s);

    // Check to see if t[0] is not null
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }


    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // ON EVERY USE OF MALLOC YOU MUST FREE THE MEMORY !!
    free(t);
    free(s_2);
}