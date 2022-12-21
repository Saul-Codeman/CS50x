#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2){
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // If the file cannot be opened for reading
    if (fopen(argv[1], "r") == NULL){
        printf("Error: cannot open %s\n", argv[1]);
        return 2;
    }
    // Number of bytes in a JPEG unit
    FILE *raw_file = fopen(argv[1], "r");
    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    FILE *new_file = NULL;
    char filename[8];
    while (fread(&buffer, BLOCK_SIZE, 1, raw_file) == 1){
        // Check if there is a new image header
        // First 4 blocks are header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            if (count != 0){
                fclose(new_file);
            }
            // Make a new image to work on using the convention of adding + 1 to 000 or the current count.
            sprintf(filename, "%03i.jpg", count);
            new_file = fopen(filename, "w");
            count++;
        }
        // Write the JPEG bytes onto the current image
        if (count != 0){
            fwrite(&buffer, BLOCK_SIZE, 1, new_file);
        }
    }
    fclose(raw_file);
    fclose(new_file);
    return 0;
}