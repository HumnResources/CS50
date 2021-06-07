#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Simple compare to see who has the higher score.
    // Where p_winner : 1 = player 1, 2 = player 2, 0 = tie.
    int p_winner;
    if (score1 > score2)
    {
        p_winner = 1;
    }
    else if (score2 > score1)
    {
        p_winner = 2;
    }
    else
    {
        // If no winner found default to tie.
        p_winner = 0;
    }

    // Display game results
    if (p_winner != 0)
    {
        printf("Player %i wins!\n", p_winner);
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;

    // Interate through the characters
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Do initial convert tp lowercase for comparison.
        char c = tolower(word[i]);
        int char_value = 0;

        // Check if the character is valid (alphabet chars only)
        // islower(char) returns 0 if false, nonzero if the char is lowercase.
        if (islower(c) == 0)
        {
            // skip this character, has no value.
            continue;
        }

        // Lowercase ascii code for alphabetical characters start at 97.
        // With this, we simply deduct that amount from the value of the
        // current char. To get our index for the corresponding POINTS array to get the value.
        char_value = POINTS[c - 97];

        // Add the value of the current char to the total.
        score += POINTS[char_value];
    }

    return score;
}