#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

// Matriz de candidatos
candidate candidates[MAX];

// Número de candidatos
int candidate_count;

// Protótipos de funções
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Checa uso indevido
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Popula a matriz de candidatos.
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Percorre todos os eleitores.
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Checa voto inválido.
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// Atualiza o total de votos dado um novo voto.
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Printa o vencedor (ou vencedores) da eleição.
void print_winner(void)
{
    int votes = candidates[0].votes;

    // Obtém o maior valor dos votos.
    for (int i = 0; i < candidate_count; i++)
    {
        if (votes < candidates[i].votes)
        {
            votes = candidates[i].votes;
        }
    }

    // Compara os votos de cada candidato.
    for (int j = 0; j < candidate_count; j++)
    {
        if (votes == candidates[j].votes)
        {
            printf("%s\n", candidates[j].name);
        }
    }
}