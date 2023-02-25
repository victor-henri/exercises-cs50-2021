#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Checa se é um numero positivo.
        if (atoi(argv[1]) < 1)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // Cria um dicionário de 'a' até 'z'.
        int dictionary[26];

        for (int i = 0; i < 26; i++)
        {
            dictionary[i] = 97 + i;
        }

        string plain_text = get_string("plaintext: ");
        int cipher = atoi(argv[1]);
        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain_text); i < n; i++)
        {
            int letter_value = (int) plain_text[i];
            int dict_position;

            // Percorre o dicionário para obter a posição
            for (int j = 0; j < 26; j++)
            {
                int value_upper = letter_value + 32; // 32 posições in ASCII

                if (letter_value == dictionary[j] || value_upper == dictionary[j])
                {
                    dict_position = j;
                }
            }

            // Fórmula para obter o valor correspondente na posição do dicionário.
            int position = (dict_position + cipher) % 26;
            int dictionary_letter = (int) dictionary[position];
            char letter_cipher;

            // Seleção para printar.
            if (islower((char) plain_text[i]))
            {
                letter_cipher = tolower((char) dictionary_letter);
                printf("%c", letter_cipher);
            }
            else if (isupper((char) plain_text[i]))
            {
                letter_cipher = toupper((char) dictionary_letter);
                printf("%c", letter_cipher);
            }
            else
            {
                printf("%c", plain_text[i]);
            }
        }

        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}