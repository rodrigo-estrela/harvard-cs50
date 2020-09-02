#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

bool is_jpeg_Start(BYTE header[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //TODO: Open memory card
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    bool isFirst = true;
    bool alreadyFound = false;
    int counter = 0;
    char *filename = malloc(8 * sizeof(char));
    FILE *outptr;
    int readNumber;

    do
    {
        readNumber = fread(&buffer, BLOCK_SIZE * sizeof(BYTE), 1, inptr);
        if (readNumber == 0)
        {
            break;
        }

        if (is_jpeg_Start(buffer))
        {
            if (isFirst)
            {
                // open a new outptr
                sprintf(filename, "%03i.jpg", counter++);
                outptr = fopen(filename, "w");
                
                // write buffer to outptr
                fwrite(&buffer, BLOCK_SIZE * sizeof(BYTE), 1, outptr);
                
                isFirst = false;
                alreadyFound = true;
            }
            else
            {
                // close previous outptr
                fclose(outptr);
                
                // open new file
                sprintf(filename, "%03i.jpg", counter++);
                outptr = fopen(filename, "w");
                
                // write buffer to file
                fwrite(&buffer, BLOCK_SIZE * sizeof(BYTE), 1, outptr);
            }
        }
        else if (alreadyFound)
        {
            fwrite(&buffer, BLOCK_SIZE * sizeof(BYTE), 1, outptr);
        }
    }
    while (true);

    fclose(inptr);
    fclose(outptr);
    free(filename);
}

bool is_jpeg_Start(BYTE header[BLOCK_SIZE])
{
    if (header[0] == 0xff && header[1] == 0xd8 && header[2] == 0xff && (header[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}
