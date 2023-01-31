#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int rows;
    do
    {
        rows = get_int("Rows: ");
    }
    while (rows < 1 || rows > 8);

    // Create rows
    for (int i = 1; i <= rows; i++)
    {
        // Create white spaces
        for (int j = rows; j > i; j--)
        {
            printf(" ");
        }

        // Create columns
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}