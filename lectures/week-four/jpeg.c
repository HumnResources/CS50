// Detects if a file is a JPEG - CS50

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    // Opens file in read-only mode
    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        return 1;
    }

    // Here we check the first three bytes of the file as they contain unique identifiers to determine file type.
    // This is applicable to multiple different file extensions such as wav/mpeg/etc...
    // Not a guaruntee, but is common

    // read first three bytes - a buffer of 3 bytes
    BYTE bytes[3];

    // Storing into the bytes variable, we take as much information as the size of one byte, three times, from the file pointer.
    fread(bytes, sizeof(BYTE), 3, fp);

    // Check first three bytes - Almost any JPEG must start with these three bytes.
    if (bytes[0] == 0xFF && bytes[1] == 0xD8 && bytes[2] == 0xFF)
    {
        printf("Maybe\n");
    }
    else
    {
        printf("No\n");
    }
}