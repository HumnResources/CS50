#include <cs50.h>
#include <stdio.h>



int get_positive(string askPrompt)
{
    int ret = 0;
    while (ret <= 0)
    {
        ret = get_int("%s", askPrompt);
    }
    return ret;
}

int main(void)
{
    int years = 0;
    int startNum = 0;
    int endNum = -1;

    // Prompt for start size
    do
    {
        startNum = get_positive("Start size: ");
    }
    while (startNum < 9);

    // Prompt for end size
    do
    {
        endNum = get_positive("End size: ");
    }
    while (endNum < startNum);


    // Calculate number of years until we reach threshold
    int currentNum = startNum;

    do
    {
        int born = currentNum / 3;
        int died = currentNum / 4;

        currentNum += born - died;

        years++;
    }
    while (currentNum < endNum);

    // Error, should have used a while loop instead.
    // This way it runs if the end num is the same
    // as the start num on first entry. Should be skipped.

    // Print number of years
    printf("Years: %i\n", years);
}