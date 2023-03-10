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

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE]; // sets the size of the header
    fread(header, HEADER_SIZE, 1, input); // copies header from original to the new file
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; // sets the buffer

    // loops through the file, until there is still some information, when not end the loop
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor; // multiplies the buffer by the factor to increase or decrease the volume
        fwrite(&buffer, sizeof(buffer), 1, output); // prints the new buffer information to the new file
    }

    // Close files
    fclose(input);
    fclose(output);
}
