#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// Substitution Cypher

bool validate_key(string);

// Use CLI to obtain cypher key.
int main(int argc, string argv[])
{
    // Check to make sure we have the correct # of arguments.
    if (argc == 1)
    {
        printf("Please provide a subtitution cypher key.\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Too many arguments provided!\n");
        return 1;
    }

    string cypherKey = argv[1];

    // Ensures key meets specification.
    if (!validate_key(cypherKey))
    {
        printf("You must provide a valid cypher text!\n");
        return 1;
    }

    // Get the text to cypher from the user.
    string text = get_string("plaintext: ");
    int l = strlen(text);

    char cypherText[l + 1];
    cypherText[l + 1] = '\0';

    for (int i = 0; i <= l; i++)
    {
        // Skips over anything that's
        // not a number, preserving its position.
        if (!isalpha(text[i]))
        {
            cypherText[i] = text[i];
            continue;
        }

        // Subtract the starting index from the ASCII
        // chart in order to get index # of current letter.
        // a = 97 | A = 65
        // Ie; C is ASCII code 67.
        // 67 - 65 = 2. Therefore my index for C is 2.
        int index;
        if (islower(text[i]))
        {
            index = text[i] - 97;
            cypherText[i] = tolower(cypherKey[index]);
        }
        else
        {
            index = text[i] - 65;
            cypherText[i] = toupper(cypherKey[index]);
        }
    }

    printf("ciphertext: %s\n", cypherText);
}

// Make sure the cyper key contains
// only alphabetical characters, all
// 26 unique letters.
bool validate_key(string key)
{
    // Get the size of the key, must be exactly 26
    // for correct letter substitution.
    int l = strlen(key);

    if (l != 26)
    {
        printf("The cypher key must be 26 unique letters.\n");
        return false;
    }

    char usedLetters[l + 1];
    usedLetters[l + 1] = '\0';

    // Loop through all the caracters, checking against
    // specification. Breaking and returning false when needed.
    for (int i = 0; i < l; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Only letters allowed.\n");
            return false;
        }

        // Compare each letter to entire array of used letters.
        // Only checking up to the current number of letters in the array.
        for (int j = 0; j < i; j++)
        {
            if (key[i] == usedLetters[j])
            {
                printf("No duplacate letter(s) allowed.\n");
                return false;
            }
        }

        // Save the letter into new string for duplicate comparison.
        usedLetters[i] = key[i];
    }

    // Criteria passed
    return true;
}