#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    int jpg_counter = 0;
    char *filename = malloc(8);

    FILE *outfile;
    BYTE buffer[BUFFER];

    // feof(FILE *file);
    // Retorna um valor inteiro = 0 se ainda não chegou no final do arquivo.

    while (1)
    {
        int size_return = fread(buffer, sizeof(BYTE), BUFFER, file);

        if (feof(file))
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_counter == 0)
            {
                sprintf(filename, "%03i.jpg", jpg_counter);
                outfile = fopen(filename, "w");

                fwrite(&buffer, sizeof(BYTE), BUFFER, outfile);
                jpg_counter += 1;
            }
            else
            {
                fclose(outfile);
                sprintf(filename, "%03i.jpg", jpg_counter);
                outfile = fopen(filename, "w");

                fwrite(&buffer, sizeof(BYTE), BUFFER, outfile);
                jpg_counter += 1;
            }
        }
        else
        {
            if (size_return <= BUFFER)
            {
                if (jpg_counter == 0)
                {
                    continue;
                }
                else
                {
                    fwrite(&buffer, sizeof(BYTE), BUFFER, outfile);
                }
            }
        }
    }

    free(filename);
    fclose(file);
    fclose(outfile);
    return 0;
}