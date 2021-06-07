#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
// Coleman-Lieu Index
// Formula: index = 0.0588 * L - 0.296 * S - 15.8
// Where L is the avg # of letters per 100 words,
// and S is the avg # of sentences per 100 words.
// *Given a provided text.

int get_sum(int);

int main(void)
{
    // Get text to grade from the user.
    string text = get_string("Text: ");

    int textLength = strlen(text);
    int nWords = 0;
    int nSentences = 0;
    int nLetters = 0;

    // Doing all the counting in one loop -- Needed the functions . . .
    // instead of separate functions
    // for time complexity.
    // Avoids reiterating the entire string
    // multiple times.
    for (int i = 0; i < textLength; i++)
    {
        // Check if character is a valid aA-zZ char.
        if (isalpha(text[i]))
        {
            nLetters += 1;
        }

        // Check for space to count number of words,
        // ensuring that we are at the end of a word.
        if (text[i] == ' ' && i != 0 && text[i - 1] != ' ')
        {
            nWords += 1;
        }

        // Check if we've reached the end of a sentence as per specification.
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            nSentences += 1;

            // Check that there is a word before the terminating char,
            // adding to count if necessary.
            if (text[i + 1] == '\0')
            {
                nWords += 1;
                break;
            }
        }
    }

    // L = avg # of letters per 100 words
    // S = avg # of sentences per 100 words.
    // Casting to float to preserve accuracy.
    float L = (float)nLetters / nWords * 100;
    float S = (float)nSentences / nWords * 100;

    // Coleman-Lieu Index - round() call rounds to nearest whole
    float index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int) round(index));
    }
}