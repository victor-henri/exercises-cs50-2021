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

    // Cria linhas
    for (int i = 1; i <= rows; i++)
    {
        // Cria espaços em branco
        for (int j = rows; j > i; j--)
        {
            printf(" ");
        }

        // Cria colunas
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}