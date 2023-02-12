#include <stdio.h>
#include <cs50.h>
#include <math.h>

int validate_checksum(long credit_card);
int separate_digits(int value);
int validate_banner(long credit_card);

int main(void)
{
    // Pergunta pelo número do cartão de crédito.
    long credit_card;
    do
    {
        credit_card = get_long("Enter the credit card number: ");
    }
    while (credit_card <= 0);

    // Valida o checksum e a bandeira.
    bool validate = validate_checksum(credit_card);
    int banner = validate_banner(credit_card);

    // Validações finais booleanas.
    if (banner == 1 && validate == true)
    {
        printf("AMEX\n");
    }
    else if (banner == 2 && validate == true)
    {
        printf("MASTERCARD\n");
    }
    else if (banner == 3 && validate == true)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int validate_checksum(long credit_card)
{
    int total_sum = 0;
    int counter = 0;
    int sum_position_even = 0;
    int sum_position_odd = 0;

    while (credit_card > 0)
    {
        // Salva o último digito, remove o dígito do cartão de crédito
        // e guarda o contador para usar a posição do elemento.
        int last_digit = credit_card % 10;
        long digits = credit_card /= 10;
        counter += 1;

        int value;

        // Se a posição é par.
        if (counter % 2 == 0)
        {
            value = last_digit * 2;

            if (value > 9)
            {
                // Se o resultado tem dois elementos decimais,
                // guarda o último elemento, e subtrai o valor
                // anterior com o ultimo elemento.
                // Chama uma função com o valor já subtraído
                // para pegar o primeiro elemento decimal,
                // e soma os valores separados.
                int new_last = value % 10;
                int new_value = value - new_last;
                int value_return = separate_digits(new_value);
                sum_position_even += new_last + value_return;
            }
            else
            {
                sum_position_even += value;
            }
        }
        // Se a posição é impar.
        else
        {
            sum_position_odd += last_digit;
        }
        // Soma de todos os elementos
        // nas posições pares e ímpares.
        total_sum = sum_position_even + sum_position_odd;
    }

    // Checa e retorna se o último digito é 0.
    int verifying_digit = total_sum % 10;
    if (verifying_digit == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int separate_digits(int value)
{
    // Recebe um valor já subtraído
    // para extrair o primeiro elemento decimal.
    int new_value = 0;
    if (value % 10 == 0)
    {
        new_value = value /= 10;
    }
    return new_value;
}

int validate_banner(long credit_card)
{
    int counter = 0;
    int position_12 = 0;
    int position_13 = 0;
    int position_14 = 0;
    int position_15 = 0;
    int position_16 = 0;

    while (credit_card > 0)
    {
        // Processo de contagem do total
        // de elementos no cartão de crédito.
        int last_digit = credit_card % 10;
        long digits = credit_card /= 10;
        counter += 1;

        // Guarda a posição dos valores.
        if (counter == 12)
        {
            position_12 = last_digit;
        }
        else if (counter == 13)
        {
            position_13 = last_digit;
        }
        else if (counter == 14)
        {
            position_14 = last_digit;
        }
        else if (counter == 15)
        {
            position_15 = last_digit;
        }
        else if (counter == 16)
        {
            position_16 = last_digit;
        }
    }

    // Valida e retorna a bandeira.
    if ((position_15 == 3 && position_14 == 4) || (position_15 == 3 && position_14 == 7))
    {
        return 1;
    }
    else if (position_16 == 5 && (position_15 == 1 || position_15 == 2 || position_15 == 3 || position_15 == 4 || position_15 == 5))
    {
        return 2;
    }
    else if (position_13 == 4 || position_16 == 4)
    {
        return 3;
    }
    return 0;
}