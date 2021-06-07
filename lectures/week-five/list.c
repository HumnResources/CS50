#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // int list[3] = {1, 2, 3};


    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%i\n", list[i]);
    // }

    // Designates an 'array' in pointer arithmetic
    // returns a contiguous block of memory
    int *list = malloc(sizeof(int) * 3);
    if (list == NULL) return 1;

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // The same in pointer arithmetic
    // First memory location of ptr is equal to arr[0]
    *list = 1;
    // Arithmetic to index further from the first memory location
    *(list+1) = 2;
    *(list+2) = 3;

    // To reallocate memory you need to use a temp variable
    // Necessary to expand the size of the pointer
    // Example adding one more
    // int *tmp = malloc(sizeof(int) * 4);
    // Instead of the above use realloc(<addr of allocated mem>, <new size>)
    int *tmp = realloc(list, sizeof(int) * 4);
    if (tmp == NULL)
    {
        // Always free()
        free(list);
        return 1;
    }

    // Using realloc() instead does this step for you
    // Smart enough to reuse the same addr if there's space at the end of that
    // existing address' block
    // for (int i = 0; i < 9; i++)
    // {
    //     tmp[i] = list[i];
    // }

    // Adding the new value
    tmp[3] = 4;

    // Clear the current list
    free(list);

    // Redirect the list pointer to the new contiguous block
    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);
    // None of the above can provide insert at front
    // All are an insertion time of Big O(n)
    // Cannot dynamically modify easily with all the copying
}