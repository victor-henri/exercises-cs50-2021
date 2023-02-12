#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int return_position(char letter, int dictionary[]);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int key_lenght = strlen(argv[1]);

        if (key_lenght == 26)
        {
            string key = argv[1];
            int dictionary[26];

            // Cria o dicionário e atualiza a chave para caracteres maiusculos.
            for (int h = 0; h < 26; h++)
            {
                dictionary[h] = 65 + h; // 65 = 'A' no ASCII.

                if (islower(key[h]) != 0) // Se for minusculo, atualiza para maiusculo.
                {
                    int value = (int) key[h];
                    key[h] = (char) value - 32;
                }
            }

            for (int i = 0; i < 26; i++)
            {
                char key_letter = (char) key[i];
                char dict_letter = (char) dictionary[i];

                // Verificações de chave.
                if (!isalpha(key_letter))
                {
                    printf("Incorrect key value -> %c\n", key_letter);
                    return 1;
                }
                else if (isspace(key_letter))
                {
                    printf("Incorrect key value.");
                    return 1;
                }
                else if (islower(key_letter))
                {
                    int key_value = (int) key[i] - 32;
                    key[i] = (int) key_value;
                }

                int matches = 0;

                for (int j = 0; j < 26; j++)
                {
                    char temp_key = (char) key[j];
                    if (dict_letter == temp_key)
                    {
                        matches += 1;

                        if (matches > 1)
                        {
                            printf("Duplicate characters in key.\n");
                            return 1;
                        }
                    }
                }
            }

            string plain_text = get_string("plaintext: ");
            printf("ciphertext: ");

            for (int k = 0, n = strlen(plain_text); k < n; k++)
            {
                // Obtém a respectiva posição do dicionário.
                char letter = (char) plain_text[k];
                int position = return_position(letter, dictionary);
                int key_character = (int) key[position];

                if (isupper(letter))
                {
                    printf("%c", key_character);
                }
                else if (islower(letter))
                {
                    key_character += 32;
                    printf("%c", key_character);
                }
                else
                {
                    printf("%c", plain_text[k]);
                }

            }
            printf("\n");
            return 0;
        }
        else if(key_lenght < 26 || key_lenght > 26)
        {
            printf("The key must have 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Use: ./ substitution key.\n");
        return 1;
    }
}

int return_position(char letter, int dictionary[])
{
    letter = toupper(letter);
    int value_letter = (int) letter;

    for (int i = 0; i < 26; i++)
    {
        int character = (int) dictionary[i];
        if (value_letter == character)
        {
            return i;
        }
    }
    return -1;
}