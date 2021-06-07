#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXTENSION "jpg"
#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int check_signature(BYTE sig[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    FILE *output = NULL;
    char *filename = NULL;
    BYTE buffer[BLOCK_SIZE];

    if (argc <= 1)
    {
        printf("Please provide a file path!\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Only one command argument is valid!\n");
    }

    // Open the file in read-only mode
    input = fopen(argv[1], "r");

    // Check's to make sure it's a valid file
    if (input == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }

    // Read in first block of data
    fread(&buffer, BLOCK_SIZE, 1, input);

    // Loop over each block of memory
    // Using i as the jpg file number/name
    int i = 0;
    while (!feof(input))
    {
        // If this passesm the signature of this block does not contains JPG information
        if (check_signature(buffer) != 0)
        {
            fread(&buffer, BLOCK_SIZE, 1, input);
            continue;
        }

        // Ensures we have only the space needed to fit the filename
        // The ternary just makes sure we aren't allocating 0 bytes
        filename = malloc(sizeof(char) * (i == 0 ? 1 : i));

        // Create a filename progmatically - ###.jpg
        sprintf(filename, "%03i.%s", i, EXTENSION);
        i++;

        // Create the file locally
        output = fopen(filename, "w");

        do
        {
            // Write from buffer into file
            fwrite(&buffer, BLOCK_SIZE, 1, output);

            // Read memory block into buffer
            fread(&buffer, BLOCK_SIZE, 1, input);

            // Check for start of another jpeg
            // Stop writing when we find a signature or hit EOF
        }
        while (!(feof(input) || check_signature(buffer) == 0));

        // Clear the buffer for the output file
        fflush(output);

        // Free memory used from the filename for reallocation
        free(filename);
    }
}

int check_signature(BYTE block[BLOCK_SIZE])
{
    // The firs three bytes conisist of: 0xFF 0xD8 0xFF respectively
    // Using bitwise OR operation to compare bit values
    // First four bits of the fourth BYTE are 1110 - Left to Right
    //
    // This checks each bit individually
    // But we AND 0xF0 to ensure the three are all flipped instead
    //     block[3] & (1<<7)) == 1 &&
    //     block[3] & (1<<6)) == 1 &&
    //     block[3] & (1<<5)) == 1 &&
    //     block[3] & (1<<4)) == 0
    if (block[0] == 0xFF && block[1] == 0xD8 && block[2] == 0xFF && (block[3] & 0xF0) == 0xE0)
    {
        return 0;
    }
    return 1;
}