// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Added a cast to account for integer values.
    float factor = (float) atof(argv[3]);

    // Create a buffer for header
    uint8_t header[HEADER_SIZE];

    // Read header file into buffer
    fread(&header, sizeof(uint8_t), HEADER_SIZE, input);

    // Write header file into output.wav
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

    // Create buffer for samples
    int16_t buffer;

    // fread() returns # of read items. Therefore if it's not 0, we have more information to read
    // Here we hard code 1 because we are only checking one sample at a time
    while (fread(&buffer, sizeof(uint16_t), 1, input) != 0)
    {
        // Adjust the volume according to the provided input
        buffer = buffer * factor;

        // Write to the output file
        fwrite(&buffer, sizeof(uint16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
