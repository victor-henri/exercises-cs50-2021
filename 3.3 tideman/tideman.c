#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair pairs_temp[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
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
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
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

// Update ranks given a new vote
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

// Update preferences given one voter's ranks
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

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Percorrer [x] e obter o maior valor.
    // Comparar [x][y] > [y][x] e adiciona pair_count +1
    // Se true então armazena em pair


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

// Sort pairs in decreasing order by strength of victory
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

// Lock pairs into the candidate graph in order, without creating cycles
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
            // return cycle(position_y, principle);
            if (cycle(position_y, principle))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
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


