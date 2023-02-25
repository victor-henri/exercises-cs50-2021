#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Pergunta e checa se é um inteiro positivo.
    int rows;
    do
    {
        rows = get_int("Rows: ");
    }
    while (rows < 1 || rows > 8);

    for (int i = 1; i <= rows; i++)
    {
        // Cria espaços em branco.
        for (int j = rows; j > i; j--)
        {
            printf(" ");
        }

        // Cria as colunas a esquerda.
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");

        //Cria as colunas a direita.
        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }

        printf("\n");
    }
}