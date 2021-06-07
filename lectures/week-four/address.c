#include <stdio.h>

// Defines a char * as a string for ease of use
// As used in the cs50 library.
typedef char * string;

int main(void)
{
    // Use andpersand '&' to access address of variable
    // int n = 50;

    // Prints the address
    // Printf("%p\n", &n);

    // Prints the contents of the address (pointless, just prrint the variable in this instance)
    // Printf("%d\n", *&n);

    // This stores the address of 'n' in 'p' and prints it out (type 'int star')
    // int *p = &n;
    // Printf("%p\n", p);

    // To print 'n' with variable 'p' use the dereference keyword
    // Printf("%d\n", *p);


    // The same thing !!

    char *s = "Hi!";
    string s_2 = "Hi!";

    // Prints address of entire 'string' (pointer address itself)
    printf("%p\n", &s);
    // Prints the address' of the characters in the string
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);

    // Does the same as above using pointer arithmetic
    printf("%c\n", *s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
    printf("%i\n", *(s+30));
}
