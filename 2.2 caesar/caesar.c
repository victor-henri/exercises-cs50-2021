#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // Checks if it is a positive number.
        if (atoi(argv[1]) < 1)
        {
            printf("Usage: ./caesar key\n");
            return 0;
        }

        //Creates a dictionary from 'a' to 'z'.
        int dictionary[26];
        for (int i = 0; i <= 26; i++)
        {
            dictionary[i] = 97 + i;
        }

        string plain_text = get_string("plaintext: ");
        int cipher = atoi(argv[1]);
        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain_text); i <= n; i++)
        {
            int letter_value = (int) plain_text[i];
            int dict_position;

            // Goes through the dictionary to get the position.
            for (int j = 0; j <= 26; j++)
            {
                int value_upper = letter_value + 32; // 32 positions in ASCII
                if (letter_value == dictionary[j] || value_upper == dictionary[j])
                {
                    dict_position = j;
                }
            }

            // Formula to get the correspondent value in position of the dictionary.
            int position = (dict_position + cipher) % 26;
            int dictionary_letter = (int) dictionary[position];
            char letter_cipher;

            // Selection to print.
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
        return 1;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 0;
    }
}