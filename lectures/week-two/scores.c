#include <cs50.h>
#include <stdio.h>

const int TOTAL = 5;

float average(int length, int arr[]);

int main(void)
{
    int scores[TOTAL];

    for (int i = 0; i < TOTAL; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", average(TOTAL, scores));
}


float average(int length, int arr[])
{
    float sum = 0.0;
    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    return sum / length;
}