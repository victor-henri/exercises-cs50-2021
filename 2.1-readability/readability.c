#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

// Índice Coleman-Liau
// indice = 0,0588 * L - 0,296 * S - 15,8
// L = Número médio de letras por 100 palavras.
// S = Número médio de frases por 100 palavras.

int main(void)
{
    string text = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;

    // Itera pelo texto, para contar
    // as variáveis usadas na fórmula.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        if (isspace(text[i]))
        {
            words += 1;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    words += 1;

    // Cálculo para obter o índice.
    float average_letters = (float) letters / words * 100;
    float average_sentences = (float) sentences / words * 100;
    float formula = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;
    int index = round(formula);

    // Seleção e print da grade.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}