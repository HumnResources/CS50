#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get divisible numbers from user
    int x = get_int("x: ");
    int y = get_int("y: ");
    
    // Get the answer
    float z = (float) x / (float) y;
    
    // Display the result to the user
    printf("%d / %d = %f\n", x, y, z);
}
