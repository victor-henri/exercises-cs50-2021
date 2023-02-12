#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int DICTIONARY[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};

int compute_score(string word);
int return_position(char letter);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins !\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins !\n");
    }
}

int compute_score(string word)
{
    int total_points = 0;
    // Compute and return score for string.
    for (int i = 0, n = strlen(word); i <= n; i++)
    {
        char letter = (char) word[i];

        if (letter == '!' || letter == '?' || letter == ',')
        {
            total_points += 0;
        }
        else
        {
            int position = return_position(letter);
            total_points += (int) POINTS[position];
        }
    }
    return total_points;
}

// Return position from character alphabet.
int return_position(char letter)
{
    int position;
    letter = toupper(letter);
    int value_letter = (int) letter;

    for (int i = 0; i <= 26; i++)
    {
        int character = (int) DICTIONARY[i];
        if (value_letter == character)
        {
            position = i;
        }
    }
    return position;
}