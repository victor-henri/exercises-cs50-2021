#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask and check if this is a positive int.
    int rows;
    do
    {
        rows = get_int("Rows: ");
    }
    while (rows < 1 || rows > 8);

    for (int i = 1; i <= rows; i++)
    {
        // Create blank_spaces.
        for (int j = rows; j > i; j--)
        {
            printf(" ");
        }

        // Create left column.
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");

        //Create right column.
        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }

        printf("\n");
    }
}