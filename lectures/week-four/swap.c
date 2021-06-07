#include <stdio.h>

void swap(int * a, int * b);

int main(void)
{
    int x = 1;
    int y = 2;


    printf("x is %i, y is %i\n", x, y);

    // swap(x, y); Does not work, swaps only local variables swap(int a, b)
    // We have to use pointers to accomplish this.
    swap(&x, &y);

    printf("x is %i, y is %i\n", x, y);
}

void swap(int *a, int *b)
{
    // Belovw code does not update input variables,
    // we need to use pointers to pass the address' of the variables
    // instead of the type value. Has memory overhead !
    // int tmp = a;
    // a = b;
    // b = tmp;

    // This code updates the correct values, and removes the used memory
    // from the stack after the function call is finished.
    int tmp = *a;
    *a = *b;
    *b = tmp;
}