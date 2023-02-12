#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Quantidade máxima de eleitores e candidatos.
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] é a jth preferência do eleitor i.
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidatos possuem nome, contador de votos, e status de eliminado.
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// matriz de candidatos.
candidate candidates[MAX_CANDIDATES];

// Contadores de votos e candidatos.
int voter_count;
int candidate_count;

// Protótipos de função.
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Checa uso indevido.
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Popula a matriz de candidatos.
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Continue consultando os votos.
    for (int i = 0; i < voter_count; i++)
    {

        // Consulta para cada classificação.
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Registra o voto, a menos que seja inválido.
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Continua segurando runoffs até que o vencedor exista.
    while (true)
    {
        // Cancula os votos dados aos candidatos restantes.
        tabulate();

        // Verifica se a eleição foi vencida.
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Elimina o candidato no último lugar.
        int min = find_min();
        bool tie = is_tie(min);

        // Se empatar, todos ganham.
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Elimina qualquer um com número mínimo de votos.
        eliminate(min);

        // Redefine a contagem de votos de volta a zero.
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Registra a preferência se o voto é válido.
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabela votos para candidatos não eliminados.
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }
}

// Printa o vencedor da eleição, se houver.
bool print_winner(void)
{
    int votes_to_win = round((voter_count / 2)) + 1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == votes_to_win)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Retorna o número mínimo de votos que qualquer candidato restante possui.
int find_min(void)
{
    int min_votes;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            min_votes = candidates[i].votes;
            break;
        }
    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (!candidates[j].eliminated)
        {
            if (min_votes > candidates[j].votes)
            {
                min_votes = candidates[j].votes;
            }
        }
    }
    return min_votes;
}

// Retorna verdadeiro se a leição estiver empatada entre todos os candidatos,
// falso caso contrário.
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            continue;
        }
        else if (min < candidates[i].votes)
        {
            return false;
        }
    }
    return true;
}

// Elimina o candidato (ou candidatos) em último lugar.
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
}
