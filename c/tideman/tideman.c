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

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool higher(int i, int j, int ranks[]);
bool makes_circle(int cycle_start, int loser);

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
    // loop over all candidates
    for(int i = 0; i < candidate_count; i++)
    {
        // see if the name enterd is correct
        if(strcmp(name, candidates[i]) == 0)
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
    // looping over every candidate coparison
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(higher(i, j, ranks))
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// checks if i or j comes first in ranks determining if they are higher up the list
bool higher(int i, int j, int ranks[])
{
    if(i == j)
    {
        return false;
    }
    for(int la = 0; la < candidate_count; la++)
    {
        if(i == ranks[la])
        {
            return true;
        }
        if(j == ranks[la])
        {
            return false;
        }
    }
    return false;
}

// Record pairs of candidates where one is preferred over the other
// [x 1 2]
// [1 x 3]
// [2 3 x]
void add_pairs(void)
{
    // iterate through the upper triangular part of the array
    // starting at one to avoid the same value pairs in the middle
    pair_count = 0;
    for (int i = 1; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if(preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // populate an array with the differences in each pair
    int strength_list[pair_count];
    for (int la = 0; la < pair_count; la++)
    {
        int i = pairs[la].winner;
        int j = pairs[la].loser;

        strength_list[la] = preferences[i][j] - preferences[j][i];
    }

    // bubble sorting strenght list on basis of strength list
    for (int step = 0; step < pair_count - 1; step++)
    {
        for (int i = 0; i < pair_count - step - 1; i++)
        {
        // compare two adjacent elements sort decreasingly
        if (strength_list[i] < strength_list[i + 1]) {

            // swapping in strength list
            int temp = strength_list[i];
            strength_list[i] = strength_list[i + 1];
            strength_list[i + 1] = temp;

            // swapping actuall list
            pair pair_temp = pairs[i];
            pairs[i] = pairs[i + 1];
            pairs[i + 1] = pair_temp;
        }
    }
  }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        if(!makes_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool makes_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        // If the current loser is the cycle start the entry makes a circle
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makes_circle(cycle_start, i))
            {
                // Forward progress through the circle
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int counter;
    for (int i = 0; i < candidate_count; i ++)
    {
        counter = 0;
            for (int j = 0; j < candidate_count; j++)
            {
                if (!locked[j][i])
                counter++;
            }
            if (counter == candidate_count)
            {
                printf("%s\n", candidates[i]);
                return;
            }
        }
}