#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Ask for start size
    int initial_size;
    do
    {
        initial_size = get_int("Start size: ");
    }
    while (initial_size < 9);


    // Ask for final size
    int final_size;
    do
    {
        final_size = get_int("End size: ");
    }
    while (final_size < initial_size);

    // Calculates years
    int population = initial_size;
    int years = 0;
    while (population < final_size)
    {
        float births = round(population / 3);
        float deaths = round(population / 4);
        population += births - deaths;
        years += 1;
    }

    // Print the result in years
    printf("Years: %i\n", years);
}