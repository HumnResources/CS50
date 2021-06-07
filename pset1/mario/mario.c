#include <stdio.h>
#include <cs50.h>

int get_positive_height(void)
{
    // Checks input range between 1-8, inclusive
    int ret = 0;
    while (ret <= 0 || ret > 8)
    {
        ret = get_int("Height: ");
    }
    return ret;
}

int main(void)
{
    int height = get_positive_height();
    int tilesPlaced;

    // height * 2 + 2 : We multiply by 2 to mirror the tiles, and add 2 to space them.
    #define LENGTH (height * 2 + 2)
    #define CENTER_R (LENGTH / 2)
    #define CENTER_L (CENTER_R - 1)
    char level[LENGTH];

    // Set the center of the row to a space
    // Does not get updated.
    level[CENTER_L] = ' ';
    level[CENTER_R] = ' ';

    // Start at 1 to print the top first. - Inclusive
    for (int i = 1; i <= height; i++)
    {
        // Set a counter to check against tiles placed for floor(i)
        tilesPlaced = 0;

        // Starting at 1 to index out from the middle. - Inclusive
        // Adding a wall piece until we reach the same number as floor we are on. 1:1 ratio.
        for (int j = 1; j <= CENTER_L; j++)
        {
            // Sets the char after the wall pieces to a terminating char.
            level[CENTER_R + j + 1] = '\0';

            // Sets initial piece to a space for alignment.
            level[CENTER_L - j] = ' ';

            // If we have more tiles to place, set them offset from center left.
            if (tilesPlaced != i)
            {
                level[CENTER_L - j] = '#';
                level[CENTER_R + j] = '#';
                tilesPlaced++;
            }
        }
        printf("%s\n", level);
    }
}