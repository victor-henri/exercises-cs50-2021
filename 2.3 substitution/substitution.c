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

            for (int i = 0; i <= 25; i++)
            {
                char key_letter = (char) key[i];

                // Key verifications.
                if(!isalpha(key_letter) && !isspace(key_letter))
                {
                    printf("Incorrect key value -> %c\n", key_letter);
                    return 1;
                }
                if (islower(key_letter))
                {
                    int key_value = (int) key[i] - 32;
                    key[i] = (int) key_value;
                }
                // Need to implement duplicate character validation.
            }

            int dictionary[key_lenght];

            // Creates a dictionary.
            for (int j = 0; j <= key_lenght; j++)
            {
                dictionary[j] = 65 + j; // 65 = A in ASCII.
            }

            string plain_text = get_string("plaintext: ");
            printf("ciphertext: ");

            for (int k = 0, n = strlen(plain_text); k <= n; k++)
            {
                // Gets the respective position from the dictionary.
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
    int position;
    letter = toupper(letter);
    int value_letter = (int) letter;

    for (int i = 0; i <= 26; i++)
    {
        int character = (int) dictionary[i];
        if (value_letter == character)
        {
            position = i;
        }
    }
    return position;
}