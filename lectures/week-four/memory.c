#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // BUGGY CODE : Memory leak !

    // Not enough bytes to storethe contents below !
    char *s = malloc(4);
    s[0] = 'H';
    s[1] = 'i';
    s[2] = '!';
    // Invlaid write on the fourth entry.
    s[3] = '\0';

    // Invalid read because memory it doesn't own. (s[3])
    printf("%s\n", s);

    // free() was never called !
    free(s);
}