#include <stdio.h>
#include <cs50.h>
#include <math.h>

int total_coins(int value);

int main(void)
{
    // Repete se não for um valor positivo.
    double dollar, cents;
    float value;
    int coins;

    do
    {
        value = get_float("Value: ");
    }
    while (value <= 0.00);

    // Checa se tem apenas centavos ou não.
    cents = modf(value, &dollar);
    cents = round(cents * 100);

    // Trata (ou não) os centavos se não tiver dolares.
    if (dollar <= 0)
    {
        int total_cents = (int) cents;
        coins = total_coins(total_cents);
        printf("%i\n", coins);
    }
    else
    {
        int total_cents = (int) dollar * 100;
        total_cents = total_cents + cents;
        coins = total_coins(total_cents);
        printf("%i\n", coins);
    }
}

int total_coins(int value)
{
    int coins = 0;
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int pennie = 1;

    // Compara os valores para saber
    // quantas moedas serão necessárias.
    while (value > 0)
    {
        if (value >= quarter)
        {
            coins += 1;
            value -= quarter;
        }
        else if (value >= dime)
        {
            coins += 1;
            value -= dime;
        }
        else if (value >= nickel)
        {
            coins += 1;
            value -= nickel;
        }
        else
        {
            coins += 1;
            value -= pennie;
        }
    }

    return coins;
}