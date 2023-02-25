#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

// preferences[i][j] é o número de eleitores que preferem i sobre j.
int preferences[MAX][MAX];

// locked[i][j] significa que i está locked em cima de j.
bool locked[MAX][MAX];

// Cada par tem um vencedor e perdedor.
typedef struct
{
    int winner;
    int loser;
}
pair;

// Matriz de candidatos
string candidates[MAX];

pair pairs[MAX * (MAX - 1) / 2];
pair pairs_temp[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;

// Protótipos de funções.
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle(int initial, int principle);
int check_candidate(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Checa por uso indevido.
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Limpa o grafo de locked nos pares.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Consulta de votos
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] é a i-ésima preferência do eleitor.
        int ranks[candidate_count];

        // Consulta para cada classificação.
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Atualiza as classificações dado um novo voto.
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Atualiza as preferências dadas as classificações de um eleitor.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int candidate_more = ranks[i];
            int candidate_less = ranks[j];
            preferences[candidate_more][candidate_less] += 1;
        }
    }
}

// Registra pares de candidatos onde um é preferido sobre o outro.
void add_pairs(void)
{
    for (int x = 0; x < candidate_count; x++)
    {
        int high_preference = 0;
        int position_y;

        for (int y = 0; y < candidate_count; y++)
        {
            if (high_preference < preferences[x][y])
            {
                high_preference = preferences[x][y];
                position_y = y;
            }
        }

        if (preferences[x][position_y] > preferences[position_y][x])
        {
            pair_count += 1;
            pairs[x].winner = x;
            pairs[x].loser = position_y;
        }
        else if (preferences[x][position_y] < preferences[position_y][x])
        {
            pair_count += 1;
            pairs[x].winner = position_y;
            pairs[x].loser = x;
        }
    }
}

// Ordena os pares em ordem decrescente de força de vitória.
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int high_value = 0;
        int position_x;

        for (int j = 0; j < pair_count; j++)
        {
            int temp_x = pairs[j].winner;
            int temp_y = pairs[j].loser;

            if (high_value < preferences[temp_x][temp_y])
            {
                high_value = preferences[temp_x][temp_y];
                position_x = j;
            }
        }

        pairs_temp[i].winner = pairs[position_x].winner;
        pairs_temp[i].loser = pairs[position_x].loser;
        pairs[position_x].winner = 0;
        pairs[position_x].loser = 0;
    }

    for (int j = 0; j < pair_count; j++)
    {
        pairs[j].winner = pairs_temp[j].winner;
        pairs[j].loser = pairs_temp[j].loser;
    }
}

// Trava os pares de grafo do candidato em ordem, sem criar ciclos.
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        locked[winner][loser] = true;

        bool cycle_validation = cycle(loser, loser);

        if (cycle_validation == true)
        {
            locked[winner][loser] = false;
            break;
        }
        else
        {
            continue;
        }
    }
}

// Função recursiva para descobrir se há ciclo ou não.
bool cycle(int initial, int principle)
{
    bool check = false;
    int position_y;

    for (int y = 0; y < candidate_count; y++)
    {
        if (locked[initial][y] == true)
        {
            check = true;
            position_y = y;
            break;
        }
    }

    if (check == false)
    {
        return false;
    }
    else
    {
        if (position_y == principle)
        {
            return true;
        }
        else
        {
            if (cycle(position_y, principle))
            {
                return true;
            }
        }
    }
    return false;
}

// Printa o vencedor da eleição.
void print_winner(void)
{
    int candidate;
    bool winner = false;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if(locked[j][i])
            {
                break;
            }
            else
            {
                winner = true;
                candidate = i;
            }
        }
    }
    printf("%s\n", candidates[candidate]);
}