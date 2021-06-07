#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // fopen(string URI, string mode);
    FILE *fp = fopen("phonebook.csv", "a");

    // FILE type is pointer to file, can produce null
    if (fp == NULL)
        return 1;

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    // Saving to csv file
    fprintf(fp, "%s,%s\n", name, number);

    // Must close to save memory.
    fclose(fp);
}