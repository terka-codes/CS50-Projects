#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // checks if user entred exactly 2 arguments, if not prints message and returns error
    if (argc != 2)
    {
        printf("Please enter only one command line argument in the terminal.\n Usage: ./recover IMAGE\n");
        return 1;
    }

    // opens a file with the name "f" for reading
    FILE *f = fopen(argv[1], "r");

    // checks if the file if valid, if not prints message and returns error
    if (f == NULL)
    {
        printf("Can't open the file. \n");
        return 1;
    }

    // declaring byte and size of the buffer
    const int BLOCK_SIZE = 512; //512 byte
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];

    // declaring count to keep track of how many images are already printed
    int JPG_count = 0;

    // makes a new file
    FILE *output_file = NULL;

    // makes a variable for the JPG name
    char JPG_file_name[8]; // because it's 000.jpg that's = 7, but you write: "sprintf(filename, "%03i.jpg", 2)" = 8

    // starting a while loop, which runs until there are BYTEs in the input file "f"
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        // checks if the first 4 bytes are declared like the name below, that means a start of a new JPG image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            // checks if this will be the first image written
            if (JPG_count == 0)
            {
                // generates a new file with the name according to JPG_count
                sprintf(JPG_file_name, "%03i.jpg", JPG_count);

                // opens the new file for writing
                output_file = fopen(JPG_file_name, "w");

                // writes the first 4 bytes to the file
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);

                // counts + 1 on the counter to keep track of the images
                JPG_count++;
            }
            // checks if 4 starting bytes aren't the first image, in not it has to close the previous file before starting a new one
            else if (JPG_count > 0)
            {
                // closes the writing file
                fclose(output_file);

                // generates a new file with the name according to JPG_count
                sprintf(JPG_file_name, "%03i.jpg", JPG_count);

                // opens the new file for writing
                output_file = fopen(JPG_file_name, "w");

                // writes the first 4 bytes to the file
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);

                // counts + 1 on the counter to keep track of the images
                JPG_count++;

            }
        }
        // if the first 4 bytes aren't beggining files continues to rewrite the datat to the new file
        else if (JPG_count > 0)
        {
            // writes the rest of the bytes to the file
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
        }
    }
    // closes the newly weritten file
    fclose(output_file);
    // closes the original file
    fclose(f);

}